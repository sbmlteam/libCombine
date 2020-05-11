import sys
import os
_PATH = os.path.abspath("./")
sys.path.append(_PATH)
sys.path.append(os.path.join(_PATH, 'libcombine'))
import libcombine


def test_import():
    test_file = os.path.join(_PATH, '/src/test/test-data/'
                                    'Smith_2004.omex')
    assert os.path.exists(petab_dir)
    
    ca = libcombine.CombineArchive()
    ca.initializeFromArchive(test_file, False)
