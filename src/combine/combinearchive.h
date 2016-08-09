#ifndef LIBCOMBINE_COMBINEARCHIVE_H
#define LIBCOMBINE_COMBINEARCHIVE_H

#include <string>
#include <list>
#include <map>
#include <fstream>

#include <omex/common/extern.h>

#include <combine/omexdescription.h>

#ifdef __cplusplus

namespace  zipper {
  class Zipper;
  class Unzipper;
}

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaOmexManifest;

class LIBCOMBINE_EXTERN CombineArchive
{
public:

  CombineArchive(const std::string& baseDir = "");
  ~CombineArchive();

  bool addFile(const std::string& fileName,
               const std::string& targetName,
               const std::string& format,
               bool isMaster = false);

  void addMetadata(const std::string& targetName,
                   const OmexDescription& description);

  bool extractEntry(const std::string& name, const std::string& destination = std::string());
  bool extractEntryToStream(const std::string& name, std::ostream& stream);
  bool extractEntryToMemory(const std::string& name, std::vector<unsigned char>& vec);

  bool extractTo(const std::string& directory);

  bool initializeFromDirectory(const std::string& directory);

  bool initializeFromArchive(
      const std::string& archiveFile,
      const std::string& baseDir="");

  std::string getBaseDir() const;

  void setBaseDir(const std::string &baseDir);

  CaOmexManifest *getManifest() const;

  void setManifest(CaOmexManifest *value);

  bool cleanUp();

  bool writeToFile(const std::string& fileName);

protected:
  std::string mBaseDir;
  std::string mArchiveFile;
  CaOmexManifest* mpManifest;
  std::map<std::string, std::string> mMap;
  std::map<std::string, OmexDescription> mMetadataMap;

  zipper::Unzipper* mpUnzipper;

};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif  /* LIBCOMBINE_COMBINEARCHIVE_H */
