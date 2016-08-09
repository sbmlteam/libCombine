#include "catch.hpp"

#include <zipper/zipper.h>
#include <zipper/unzipper.h>
#include <zipper/tools.h>

#include <combine/combinearchive.h>
#include <omex/CaOmexManifest.h>

#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

SCENARIO("creating a new combine archive", "[combine]")
{
  GIVEN("a user creates a new archive")
  {
    CombineArchive archive;
    REQUIRE(!archive.getBaseDir().empty());
    REQUIRE(archive.getManifest() == NULL);

    WHEN("a document is added")
    {
      archive.addFile("E:\\Users\\fbergmann\\Documents\\SBML Models\\BorisEJB.xml",
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

        AND_WHEN("the archive is saved")
        {
          // ensure that the file is not already present, and if so remove it
          if (checkFileExists("out.omex"))
            std::remove("out.omex");

          archive.writeToFile("out.omex");

          CombineArchive second;
          second.initializeFromArchive("out.omex");

          THEN("it can be loaded and the files are present.")
          {
            REQUIRE(second.getManifest() != NULL);
            REQUIRE(second.getManifest()->getNumContents() == 1);
            entry = second.getManifest()->getContent(0);
            REQUIRE(entry != NULL);
            REQUIRE(entry->getLocation() == "./model/BorisEJB.xml");
            REQUIRE(entry->getFormat() == "http://identifiers.org/combine.specifications/sbml");
          }
        }
      }
    }
  }
}
