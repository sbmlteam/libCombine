#ifndef LIBCOMBINE_UTIL_H
#define LIBCOMBINE_UTIL_H

#include <omex/common/extern.h>
#include <omex/common/libcombine-namespace.h>

#ifdef __cplusplus

#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN Util
{
public:

  /**
   * @return the temp path or "." if the temp path could not be located
   */
  static std::string getTempPath();

  /**
   * constructs a new temp file name using the current milliseconds.
   *
   * The format of the temp file will be:
   *
   *   temp_path + "/" + prefix + milliseconds + ext
   *
   * @param prefix optional prefix to be used (will be "temp" otherwise)
   * @param ext optional extension to be used (will be ".tmp" otherwise)
   *
   * @return the temp filename
   */
  static std::string getTempFilename(const std::string &prefix="temp",
                                     const std::string &ext = ".tmp");

  /**
   * @return current milliseconds since 1970 on this system
   */
  static unsigned long getCurrentMilliseconds();

  /**
   * copies the source file to the destination
   *
   * @param source source file name
   * @param destination destination file name
   */
  static void copyFile(const std::string& source, const std::string& destination);

  /**
   * copies in to out
   *
   * @param in input stream
   * @param out output stream
   */
  static void copyStream(std::istream& in, std::ostream& out);

  /**
   * returns the extension of the given filename (not including the dot)
   *
   * @param fileName the filename
   *
   * @return the extension if found, otherwise an empty string.
   */
  static std::string getExtension(const std::string& fileName);

  /**
   * Removes the specified file or folder. If it is a folder
   * its contents will be removed recursively. 
   */
  static bool removeFileOrFolder(const std::string& path);


private:

  /**
   * goes through the string and returns the index where the
   * extension begins
   *
   * @param fileName the filename to look through
   *
   * @return the position where the extension begins.
   */
  static size_t getExtensionIndex(const char *fileName);


};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif /* LIBCOMBINE_UTIL_H */
