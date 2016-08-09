#ifndef LIBCOMBINE_OMEXDESCRIPTION_H
#define LIBCOMBINE_OMEXDESCRIPTION_H

#include <omex/common/extern.h>
#include <omex/common/libcombine-namespace.h>

#include <combine/vcard.h>

#include <sbml/common/libsbml-namespace.h>
#include <sbml/annotation/Date.h>

#ifdef __cplusplus

#include <vector>
#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN OmexDescription
{

public:

  OmexDescription();

  OmexDescription(XMLInputStream& stream);


  static const std::string& getRdfNS();

  static const std::string&  getDcNS();

  static std::vector<OmexDescription> parseFile(const std::string& fileName);

  static std::vector<OmexDescription> parseString(const std::string& xml);

  static std::vector<OmexDescription> readFrom(XMLInputStream& stream);

  bool isEmpty() const;

  std::string getDescription() const;
  void setDescription(const std::string &description);

  std::string getAbout() const;
  void setAbout(const std::string &about);

  std::vector<VCard> getCreators() const;
  size_t getNumCreators() const;
  void setCreators(const std::vector<VCard> &creators);
  void addCreator(const VCard& creator);

  LIBSBML_CPP_NAMESPACE_QUALIFIER Date getCreated() const;
  void setCreated(const LIBSBML_CPP_NAMESPACE_QUALIFIER Date &created);

  std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date> getModified() const;
  size_t getNumModified() const;
  void setModified(const std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date> &modified);
  void addModification(const LIBSBML_CPP_NAMESPACE_QUALIFIER Date& date);

  void readDescription(XMLInputStream &stream, const XMLToken &token);
  LIBSBML_CPP_NAMESPACE_QUALIFIER Date readDate(XMLInputStream &stream);

  void writeToFile(const std::string& fileName);

  std::string toXML(bool omitDeclaration = false);

protected:
  std::string mDescription;
  std::string mAbout;
  std::vector<VCard> mCreators;
  LIBSBML_CPP_NAMESPACE_QUALIFIER Date mCreated;
  std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date> mModified;
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif /* LIBCOMBINE_OMEXDESCRIPTION_H */
