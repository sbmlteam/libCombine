#include <combine/vcard.h>
#include <combine/omexdescription.h>

#include <sbml/xml/XMLInputStream.h>

bool VCard::isEmpty() const
{
  return mFamilyName.empty() || mGivenName.empty();
}

std::string VCard::toXML() const
{
  if (isEmpty()) return "";


  std::stringstream str;
  str << "    <dcterms:creator rdf:parseType='Resource'>" << std::endl
      << "      <vCard:hasName rdf:parseType='Resource'>" << std::endl
      << "        <vCard:family-name>" << mFamilyName << "</vCard:family-name>" << std::endl
      << "        <vCard:given-name>" << mGivenName << "</vCard:given-name>" << std::endl
      << "      </vCard:hasName>" << std::endl
      << "      <vCard:hasEmail rdf:resource='"<< mEmail << "' />" << std::endl
      << "      <vCard:organization-name>" << mOrganization << "</vCard:organization-name>" << std::endl
      << "    </dcterms:creator>";

  // <vCard:hasURL rdf:resource='http://orcid.org/0000-0002-6309-7327'/>

  return str.str();
}
std::string VCard::getFamilyName() const
{
  return mFamilyName;
}

void VCard::setFamilyName(const std::string &familyName)
{
  mFamilyName = familyName;
}
std::string VCard::getGivenName() const
{
  return mGivenName;
}

void VCard::setGivenName(const std::string &givenName)
{
  mGivenName = givenName;
}
std::string VCard::getEmail() const
{
  return mEmail;
}

void VCard::setEmail(const std::string &email)
{
  mEmail = email;
}
std::string VCard::getOrganization() const
{
  return mOrganization;
}

void VCard::setOrganization(const std::string &organization)
{
  mOrganization = organization;
}


VCard::VCard()
 : mFamilyName()
 , mGivenName()
 , mEmail()
 , mOrganization()
{
}

VCard::VCard(const VCard &other)
  : mFamilyName(other.mFamilyName)
  , mGivenName(other.mGivenName)
  , mEmail(other.mEmail)
  , mOrganization(other.mOrganization)
{

}

VCard::VCard(XMLInputStream &stream)
  : mFamilyName()
  , mGivenName()
  , mEmail()
  , mOrganization()
{
  while (stream.isGood())
  {
    stream.skipText();
    XMLToken next = stream.next();

    if (!next.isStart()) continue;

    if (next.getName() == "family-name") 
    {
      mFamilyName = stream.next().getCharacters();
    }
    else if (next.getName() == "given-name")
    {
      mGivenName = stream.next().getCharacters();
    }
    else if (next.getName() == "organization-name")
    {
      mOrganization = stream.next().getCharacters();
    }
    else if (next.getName() == "hasEmail")
    {
      mEmail = next.getAttrValue("resource", OmexDescription::getRdfNS());
    }
  }
}
