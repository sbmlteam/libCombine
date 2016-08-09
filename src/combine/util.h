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
  static std::string getTempPath();
  static void copyFile(const std::string& source, const std::string& destination);
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif /* LIBCOMBINE_UTIL_H */
