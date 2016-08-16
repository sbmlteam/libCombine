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

  /**
   * @return the family name
   */
  std::string getFamilyName() const;

  /**
   * sets the family name
   *
   * @param familyName the name
   */
  void setFamilyName(const std::string &familyName);

  /**
   * @return the first name
   */
  std::string getGivenName() const;

  /**
   * sets the first name
   *
   * @param givenName the name
   */
  void setGivenName(const std::string &givenName);

  /**
   * @return the email
   */
  std::string getEmail() const;

  /**
   * sets the email address
   *
   * @param email the email address
   */
  void setEmail(const std::string &email);

  /**
   * @return the organization
   */
  std::string getOrganization() const;

  /**
   * sets the organization
   *
   * @param organization the organization
   */
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
