import sys
import os
_PATH = os.path.abspath(".")
sys.path.append(_PATH)
sys.path.append(os.path.join(_PATH, 'libcombine'))
import libcombine


def test_import():
    test_file = os.path.join(_PATH, 'src/test/test-data/'
                                    'Smith_2004.omex')
    assert os.path.exists(test_file)
    
    ca = libcombine.CombineArchive()
    ca.initializeFromArchive(test_file, False)


def test_dates():
    _PATH = os.path.abspath(".")
    test_file = os.path.join(_PATH, 'src/test/test-data/'
                                    'issue_33.omex')
    assert os.path.exists(test_file)
    
    ca = libcombine.CombineArchive()
    ca.initializeFromArchive(test_file, False)
    location = ca.getAllLocations()[0]
    metadata = ca.getMetadataForLocation(location)
    num_modified = metadata.getNumModified()
    for modified in metadata.getModified(): 
      assert modified.getDateAsString()
    date = libcombine.Date()
    date.setDateAsString('...')
    metadata.getModified().append(date)
    assert num_modified < metadata.getNumModified()
