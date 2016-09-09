import sys

from libcombine import *

def createArchiveExample(fileName):
  
  archive = CombineArchive();
  archive.addFile(
    fileName, # filename
    "./models/model.xml", # target file name
    KnownFormats.lookupFormat("sbml"), # look up identifier for SBML models
    True # mark file as master
    );
  
  description = OmexDescription();
  description.setAbout("."); # about the archive itself
  description.setDescription("Simple test archive including one SBML model");
  description.setCreated(OmexDescription.getCurrentDateAndTime());
  
  creator = VCard();
  creator.setFamilyName("Bergmann");
  creator.setGivenName("Frank");
  creator.setEmail("fbergman@caltech.edu");
  creator.setOrganization("Caltech");
  
  description.addCreator(creator);
  
  archive.addMetadata(".", description);
  
  archive.writeToFile("out.omex");


if __name__ == "__main__":
  if len(sys.argv) < 2:
    print ("usage createArchiveExample sbml-file")
    sys.exit(1)
    
  createArchiveExample(sys.argv[1])

