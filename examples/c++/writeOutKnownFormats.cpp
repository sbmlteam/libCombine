#include <combine/knownformats.cpp>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[])
{
  stringstream str;
  
  std::map<std::string, std::vector<std::string> >& map = KnownFormats::getKnownFormats();

  std::map<std::string, std::vector<std::string> >::iterator it = map.begin();
  for (; it != map.end(); ++it)
  {
    str << "  {\n"
        << "    std::string temp[] = {\n";
    std::vector<std::string>& current = it->second;
    std::vector<std::string>::iterator iter = current.begin();
    for (; iter != current.end(); ++iter)
    {
      str << "      \"" << *iter << "\",\n";
    }
    str << "    };\n";
    str << "    result[\"" << it->first << "\"] = std::vector<std::string>(temp, temp+" << current.size() << ");\n";
    str << "  }\n\n";
  }

  std::cout << str.str();
  return 0;
}
