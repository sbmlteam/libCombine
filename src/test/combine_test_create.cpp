#include "catch.hpp"

#include <zipper/zipper.h>
#include <zipper/unzipper.h>
#include <zipper/tools.h>

#include <combine/combinearchive.h>
#include <combine/knownformats.h>
#include <omex/CaOmexManifest.h>

#include <vector>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>

LIBCOMBINE_CPP_NAMESPACE_USE
using namespace zipper;

/**
 * Tries to find the test file in the srcdir environment variable.
 *
 * @param fileName the filename relative to this tests srcdir
 *        environment variable.
 *
 * If the filename cannot be found, the test from which this function
 * is called will fail.
 *
 * @return the full path to the test file
 */
std::string getTestFile(const std::string& fileName)
{
  std::stringstream str;
  char* srcDir = getenv("srcdir");
  
  if (srcDir != NULL) str << srcDir;
  else str << ".";

  str << "/" << fileName;
  std::string fullName = str.str();

  if (!checkFileExists(fullName))
  {
    FAIL("The test file '" << fileName << "' could not be found. please specify the 'srcdir' environment variable. The full path tried was: " << fullName);
  }

  return fullName;
}



SCENARIO("creating a new combine archive", "[combine]")
{
  GIVEN("a user creates a new archive")
  {
    CombineArchive archive;
    REQUIRE(archive.getManifest() == NULL);

    WHEN("a document is added")
    {
      archive.addFile(getTestFile("test-data/BorisEJB.xml"),
                      "./model/BorisEJB.xml",
                      "http://identifiers.org/combine.specifications/sbml");

      THEN("the file can be found in the archive")
      {
        REQUIRE(archive.getManifest() != NULL);
        REQUIRE(archive.getManifest()->getNumContents() == 1);
        CaContent* entry = archive.getManifest()->getContent(0);
        REQUIRE(entry != NULL);
        REQUIRE(entry->getLocation() == "./model/BorisEJB.xml");
        REQUIRE(entry->getFormat() == "http://identifiers.org/combine.specifications/sbml");
        REQUIRE(entry->isFormat("sbml"));
        REQUIRE(entry->getNumCrossRefs() == 0);

        CaCrossRef* ref = entry->createCrossRef();
        ref->setLocation("foo.xml");

        REQUIRE(entry->getNumCrossRefs() == 1);
        REQUIRE(entry->getCrossRef(0) != NULL);
        REQUIRE(entry->getCrossRef(0)->getLocation() == "foo.xml");

        delete entry->removeCrossRef(0);

        std::string modelContent = archive.extractEntryToString("./model/BorisEJB.xml");
        REQUIRE(!modelContent.empty());

        AND_WHEN("metadata is added")
        {
          VCard creator;
          creator.setEmail("fbergman@caltech.edu");
          creator.setFamilyName("Bergmann");
          creator.setGivenName("Frank");
          creator.setOrganization("Caltech");

          Date current = OmexDescription::getCurrentDateAndTime();

          OmexDescription desc;
          desc.setAbout(".");
          desc.setDescription("great archive");
          desc.setCreated(current);
          desc.addModification(current);
          desc.addCreator(creator);

          REQUIRE(!archive.hasMetadataForLocation("."));
          archive.addMetadata(".", desc);

          THEN("the metadata is accessible")
          {

            OmexDescription desc2 = archive.getMetadataForLocation(".");
            REQUIRE(!desc2.isEmpty());
            REQUIRE(desc2.getAbout() ==".");
            REQUIRE(desc2.getDescription() == "great archive");
            REQUIRE(desc2.getCreated().getDateAsString() == current.getDateAsString());
            REQUIRE(desc2.getNumCreators() == 1);
            REQUIRE(!desc2.getCreator(0).isEmpty());


            AND_WHEN("the archive is saved")
            {
              // ensure that the file is not already present, and if so remove it
              if (checkFileExists("out.omex"))
                std::remove("out.omex");

              int numContent = archive.getManifest()->getNumContents();
              archive.writeToFile("out.omex");
              REQUIRE(numContent == archive.getManifest()->getNumContents());

              CombineArchive second;
              second.initializeFromArchive("out.omex");

              THEN("it can be loaded and the files are present.")
              {
                REQUIRE(second.getManifest() != NULL);
                REQUIRE(second.getManifest()->getNumContents() == 1);

                OmexDescription desc3 = archive.getMetadataForLocation(".");
                REQUIRE(!desc3.isEmpty());
                REQUIRE(desc3.getAbout() == ".");
                REQUIRE(desc3.getDescription() == "great archive");
                REQUIRE(desc3.getCreated().getDateAsString() == current.getDateAsString());
                REQUIRE(desc3.getNumCreators() == 1);
                REQUIRE(!desc3.getCreator(0).isEmpty());

                entry = second.getManifest()->getContent(0);
                REQUIRE(entry != NULL);
                REQUIRE(entry->getLocation() == "./model/BorisEJB.xml");
                REQUIRE(entry->getFormat() == "http://identifiers.org/combine.specifications/sbml");

                std::string modelContent = second.extractEntryToString("./model/BorisEJB.xml");
                REQUIRE(!modelContent.empty());

              }

              AND_WHEN("the archive is saved again")
              {
                if (checkFileExists("out2.omex"))
                  std::remove("out2.omex");
                REQUIRE(archive.writeToFile("out2.omex"));
                REQUIRE(checkFileExists("out2.omex"));
                REQUIRE(second.cleanUp());
                REQUIRE(archive.writeToFile("out2.omex"));

                REQUIRE(second.initializeFromArchive("out2.omex"));

                THEN("the numbers of entries are the same")
                {
                  REQUIRE(second.getManifest() != NULL);
                  REQUIRE(second.getManifest()->getNumContents() == 1);
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO("reading an existing archive", "[combine]")
{
  GIVEN("a user loads a file with unexpected metadata")
  {
    CombineArchive archive;
    REQUIRE(archive.getManifest() == NULL);
    REQUIRE(archive.initializeFromArchive(getTestFile("test-data/Smith_2004.omex")) == true);
    
    // try and extract the unrecognized data
    std::string annotation = archive.extractEntryToString("./model/smith_2004.rdf");
    REQUIRE(annotation.find("semsim:") != std::string::npos);
    
  }
}

SCENARIO("creating a combine archive", "[combine]")
{
  CombineArchive archive;
  REQUIRE(archive.getManifest() == NULL);
 
  GIVEN("user adds invalid omex data")
  {
    OmexDescription desc;
    REQUIRE(desc.getAbout().empty());
    REQUIRE(desc.getDescription().empty());
    REQUIRE(desc.getCreators().size() == 0);

    THEN("it can not be added to the archive")
      {
        REQUIRE(archive.addMetadata("file", desc) == LIBCOMBINE_OPERATION_FAILED);
      }

    AND_WHEN("a description and created date is added it can be added")
    {
      desc.setDescription("some description");
      desc.setCreated(OmexDescription::getCurrentDateAndTime());
      REQUIRE(archive.addMetadata("file", desc) == LIBCOMBINE_OPERATION_SUCCESS);
    }
       
  }
}

TEST_CASE("known format starts with purl", "[combine]")
{
  std::string copasiFormat = KnownFormats::lookupFormat("copasi");
  REQUIRE(copasiFormat.find("http://purl.org/NET/mediatypes/") != std::string::npos);
  REQUIRE(KnownFormats::isFormat("copasi", "application/x-copasi"));
  REQUIRE(KnownFormats::isFormat("copasi", KnownFormats::PURL_MEDIATYPES_URL + "application/x-copasi"));
}

TEST_CASE("don't trip over https", "[combine]")
{
  REQUIRE(KnownFormats::isFormat("copasi", "https://purl.org/NET/mediatypes/application/x-copasi"));
  REQUIRE(KnownFormats::isFormat("sbml", "https://identifiers.org/combine.specifications/sbml.level-2.version-1"));
}
