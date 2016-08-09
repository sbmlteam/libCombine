#include <combine/util.h>

#include <cstdio>
#include <cstdlib>

#include <fstream>

std::string Util::getTempPath()
{
  char *tmpDir = getenv("TMP");
  if (tmpDir != NULL) return tmpDir;
  tmpDir = getenv("TEMP");
  if (tmpDir != NULL) return tmpDir;
  return ".";
}


void Util::copyFile(const std::string &source, const std::string &destination)
{
  std::ifstream in(source.c_str(), std::ios::in | std::ios::binary);
  std::ofstream out(destination.c_str(), std::ios::out | std::ios::binary);
  char buffer[512];

  std::streamsize size;

  while(in.good())
  {
    size = in.readsome(buffer, 512);
    out.write(buffer, size);
  }
}
