#!/usr/bin/env python
"""
Example of creating / adding to a manifest 

"""
from __future__ import print_function
import sys
import os

import libcombine 


if __name__ == "__main__":

    num_args = len(sys.argv)

    if num_args < 2: 
        print("usage: add_to_manifest <manifest_file> [ location format master]")
        sys.exit(1)
    
    manifest_file = sys.argv[1]

    if os.path.exists(manifest_file): 
        manifest = libcombine.readOMEXFromFile(manifest_file)
        if manifest.getNumErrors(libcombine.LIBSBML_SEV_ERROR) > 0:
            print('invalid manifest file:')
            print(manifest.getErrorLog().toString())
            sys.exit(1)
    else:
        print('creating new manifest')
        manifest = libcombine.CaOmexManifest()

    pos = 2
    while pos + 2  < num_args:
        location = sys.argv[pos]
        format = sys.argv[pos + 1]
        master = sys.argv[pos + 2].lower() == 'true'

        # add new entry to manifest with location, format and master attribute
        content = manifest.createContent()
        assert(isinstance(content, libcombine.CaContent))
        content.setLocation(location)
        content.setFormat(format)
        content.setMaster(master)

        pos = pos + 2

    # write to file
    libcombine.writeOMEXToFile(manifest, manifest_file)
