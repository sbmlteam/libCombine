#include <combine/combinearchive.h>
#include <combine/util.h>

#include <omex/CaOmexManifest.h>
#include <omex/CaContent.h>
#include <omex/CaReader.h>
#include <omex/CaWriter.h>

#include <zipper/zipper.h>
#include <zipper/tools.h>
#include <zipper/unzipper.h>

#include <fstream>

using namespace zipper;

CombineArchive::CombineArchive(const std::string &baseDir)
  : mBaseDir(baseDir)
  , mArchiveFile()
  , mpManifest(NULL)
  , mMap()
  , mMetadataMap()
  , mpUnzipper(NULL)
{
  if (baseDir.empty())
    mBaseDir = Util::getTempPath();
}

CombineArchive::~CombineArchive()
{
  cleanUp();
  // TODO: delete files if we extrated things somewhere
}

bool
CombineArchive::extractTo(const std::string &directory)
{
  mBaseDir = directory;
  return true;
}

bool CombineArchive::initializeFromDirectory(const std::string &directory)
{
  return true;
}

bool
CombineArchive::initializeFromArchive(
    const std::string &archiveFile,
    const std::string &baseDir)
{
  cleanUp();

  mArchiveFile = archiveFile;

  if (baseDir.empty())
    mBaseDir = Util::getTempPath();
  else
    mBaseDir = baseDir;  

  mpUnzipper = new Unzipper(archiveFile);


  // now build the map of all files in the archive
  std::vector<zipper::ZipEntry> entries = mpUnzipper->entries();
  for (auto it = entries.begin(); it != entries.end(); ++it)
  {
    mMap[(*it).name] = "unzipper://" + (*it).name;
  }

  if (mMap.find("manifest.xml") == mMap.end())
  {
    // invalid COMBINE archive, it should always have a manifest
    cleanUp();
    return false;
  }

  // read manifest
  std::ostringstream manifest;
  mpUnzipper->extractEntryToStream("manifest.xml", manifest);
  mpManifest = readOMEXFromString(manifest.str().c_str());

  // remove the actual manifest entry from the manifest
  for (unsigned int i = 0; i < mpManifest->getNumContents(); ++i)
  {
    CaContent* current = mpManifest->getContent(i);
    if (current->getLocation() != ".")
      continue;
      
    mpManifest->removeContent(i);
    break;
  }
  mMap.erase("manifest.xml");


  return true;
}

std::string CombineArchive::getBaseDir() const
{
  return mBaseDir;
}

void CombineArchive::setBaseDir(const std::string &baseDir)
{
  mBaseDir = baseDir;
}

bool CombineArchive::cleanUp()
{
  mMap.clear();
  mMetadataMap.clear();

  if (mpUnzipper != NULL)
  {
    delete mpUnzipper;
    mpUnzipper = NULL;
  }

  if (mpManifest != NULL)
  {
    delete mpManifest;
    mpManifest = NULL;
  }

  return true;
}

bool CombineArchive::writeToFile(const std::string &fileName)
{
  Zipper zipper(fileName);
  zipper.open();

  bool foundIdentity = false;

  // add all files
  for(unsigned int i = 0; i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* entry = mpManifest->getContent(i);
    std::string targetName = entry->getLocation();
    if (targetName == ".")
    {
      // skip manifest for now (will be generated below)
      foundIdentity = true;
      continue;
    }

    const std::string& sourceFile = mMap[targetName];
    std::string directory = parentDirectory(targetName);
    std::string name = fileNameFromPath(targetName);

    if (targetName.find("./") == 0)
      targetName = targetName.substr(2);

    if (targetName.find("/") == 0)
      targetName = targetName.substr(1);

    std::ifstream in(sourceFile, std::ios::in | std::ios::binary);
    zipper.add(in, targetName);
    in.close();
  }

  if (!foundIdentity)
  {
    CaContent* manifest = mpManifest->createContent();
    manifest->setLocation(".");
    manifest->setFormat("http://identifiers.org/combine.specifications/omex");
  }

  // add manifest
  std::stringstream str; str << writeOMEXToStdString(mpManifest);
  zipper.add(str, "manifest.xml");

  zipper.close();
  return true;
}

CaOmexManifest *CombineArchive::getManifest() const
{
  return mpManifest;
}

void CombineArchive::setManifest(CaOmexManifest *value)
{
  cleanUp();

  mpManifest = value;
}

bool CombineArchive::addFile(const std::string &fileName,
                             const std::string &targetName,
                             const std::string &format,
                             bool isMaster)
{
  if (mpManifest == NULL)
  {
    mpManifest = new CaOmexManifest();
  }

  CaContent* content = mpManifest->createContent();
  content->setLocation(targetName);
  content->setFormat(format);
  content->setMaster(isMaster);

  mMap[targetName] = fileName;

  return true;
}

void
CombineArchive::addMetadata(const std::string &targetName,
                            const OmexDescription &description)
{
  mMetadataMap[targetName] = description;
}

bool
CombineArchive::extractEntry(const std::string &name, const std::string &destination)
{
  return true;
}

bool
CombineArchive::extractEntryToStream(const std::string &name, std::ostream &stream)
{
  return true;
}

bool CombineArchive::extractEntryToMemory(const std::string &name, std::vector<unsigned char> &vec)
{
  return true;
}

