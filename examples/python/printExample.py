import sys

from libcombine import *

def printMetaDataFor(archive, location):
  desc = archive.getMetadataForLocation(location);
  if desc.isEmpty():
  {
    print("  no metadata for '{0}'".format(location));
    return;

  print("  metadata for '{0}':".format(location));
  print("     Created : {0}".format(desc.getCreated().getDateAsString()));
  for i in range(desc.getNumModified()):
    print("     Modified : {0}".format(desc.getModified(i).getDateAsString()));

  print("     # Creators: {0}".format(desc.getNumCreators()));
  for i in range(desc.getNumCreators()):
    creator = desc.getCreator(i);
    print("       {0} {1}".format(creator.getGivenName(), creator.getFamilyName()));

def printArchive(fileName):
  
  archive = CombineArchive();
  if !archive.initializeFromArchive(fileName):
  {
    System.out.println("Invalid Combine Archive");
    return;
  }
  
  printMetaDataFor(archive, ".");
  
  print("Num Entries: {0}".format(archive.getNumEntries()));
  
  for i in range (archive.getNumEntries()):
    entry = archive.getEntry(i);
    
    print(" {0}: location: {1} format: {2}".format(i, entry.getLocation(), entry.getFormat()));
    printMetaDataFor(archive, entry.getLocation());
  
    # the entry could now be extracted via 
    # archive.extractEntry(entry.getLocation(), <filename or folder>)
  
    # or used as string
    # content = archive.extractEntryToString(entry.getLocation());
  
  
  archive.cleanUp();

if __name__ == "__main__":
  if len(sys.argv) < 2:
    print ("usage printArchive archive-file")
    sys.exit(1)
    
  printArchive(sys.argv[1])

