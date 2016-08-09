#ifndef LIBCOMBINE_VCARD_H
#define LIBCOMBINE_VCARD_H

#include <string>
#include <sstream>

#include <omex/common/extern.h>

#include <sbml/xml/XMLNode.h>

#ifdef __cplusplus

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN VCard
{
public:

  /**
   * @brief VCard
   */
  VCard();

  /**
   * @brief VCard
   * @param other
   */
  VCard(const VCard& other);

  /**
   * @brief VCard
   * @param stream
   */
  VCard(XMLInputStream& stream);

  /**
   * @return true if empty(no names specified)
   */
  bool isEmpty() const;

  /**
   * @return an xml representation of this class
   */
  std::string toXML() const;

  std::string getFamilyName() const;
  void setFamilyName(const std::string &familyName);

  std::string getGivenName() const;
  void setGivenName(const std::string &givenName);

  std::string getEmail() const;
  void setEmail(const std::string &email);

  std::string getOrganization() const;
  void setOrganization(const std::string &organization);

private:
  std::string mFamilyName;
  std::string mGivenName;
  std::string mEmail;
  std::string mOrganization;

};


LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* LIBCOMBINE_VCARD_H */
