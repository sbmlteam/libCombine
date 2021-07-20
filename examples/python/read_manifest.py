#!/usr/bin/env python
"""
Example of accessing the metadata file directly

"""
from __future__ import print_function
import sys

import libcombine 

def print_manifest(filename):
    manifest = libcombine.readOMEXFromFile(filename)
    assert(isinstance(manifest, libcombine.CaOmexManifest))

    if manifest.getNumErrors(libcombine.LIBSBML_SEV_ERROR) > 0:
        print('Errors occured while reading the manifest:')
        print(manifest.getErrorLog().toString())
        return

    print('The manifest has: {0} entries'.format(manifest.getNumContents()))

    for entry in manifest.getListOfContents():
        assert(isinstance(entry, libcombine.CaContent))
        print('\t Location: {0}, Format: {1}, Master: {2}'.format(
            entry.getLocation(), entry.getFormat(), entry.getMaster()))


if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args != 2: 
        print("usage: read_manifest <manifest_file>")
        sys.exit(1)
    
    print_manifest(sys.argv[1])