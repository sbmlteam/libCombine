# LibCombine
LibCombine implements a C++ API library providing support for the [Combine Archive](http://co.mbine.org/documents/archive). The library is written after the likeness of libSBML (and in fact some classes have been generated using DEVISER). Thus even thought he core is written in C++, the classes can be accessed via SWIG from .NET, Java and Python. 

## Dependencies
This library requires libSBML to be present, as its XML parsing layer will be used. for that either expat, xerces-c or libXML2 needs to be available. Additionally you will need zlib as well as the zipper library that can be obtained from: 

* <https://github.com/fbergmann/zipper>

The zipper library supports three backends for the filesystem API: 

* the C++17 filesystem STL (afaik only supported by MSVC right now)
* boost filesystem api (requiring both boost system and boost filesystem)
* QtCore

Whatever has been chosen for the compilation of the zipper library has to be chosen for libCOMBINE as well. Thus the same three options are available: 

* C++17 API: (default, nothing to specify)
* BOOST API: `-DWITH_BOOST_FILESYSTEM=ON`, the actual libraries can be specified with the variables: `BOOST_SYSTEM_LIBRARY`, `BOOST_FILESYSTEM_LIBRARY` and `BOOST_INCLUDE_DIR`. 
* Qt API: `-DWITH_QT_FILESYSTEM=ON` the actual library is found using the CMake FindQt package. So just specify your QTDIR environment variable. 

## Building 
This library uses [CMake](http://cmake.org) to build the library, so from an initial checkout all you would need todo is to run: 


    mkdir build  
    cd build
    cmake -DLIBSBML_LIBRARY=< path to libsbml lib> -DLIBSBML_INCLUDE_DIR=< path to includes > ... -DEXTRA_LIBS= < comma separated list of xml libraries> 
    make  
    make install
    
Should libSBML be installed in a default location it will be found automatically. Note that you do need to list the xml libraries that libSBML was linked against. In most cases libSBML is compiled against libXML and have compression enabled, so your `EXTRA_LIBS` would be:

	EXTRA_LIBS=xml2;bz2;z;iconv

note the semicolon denoting the listing of several libraries. Of course you could also enter the full path to each individual file, just to give an example, on windows I use: 

	EXTRA_LIBS=D:/dependencies/lib/expat.lib

for linking against `expat` and indicating, that libSBML was compiled without compression.

To make it easier all dependencies can be installed into a directory with a `bin`, `include` and `lib` folder. If that is passed to cmake using the variable `-DCOMBINE_DEPENDENCY_DIR=<directory>` all dependencies are easily found. 

## How to use
The library is centered around the class `CombineArchive`.  Once you created an instance of the class, you can add files and content to it using either `addFile` with a filename, or with an input stream in case it is an in memory element. To add metadata you would use `addMetadata`. The actual combine archive will only be created upon a call to `writeToFile`. 

To read a combine archive, you would use the function `initializeFromArchive`. At that point you can retrieve all the locations inside the archive using `getAllLocations()`. For each of the location you could then request metadata using: `getMetadataForLocation`, the entry in form of a string using `extractEntryToString`, have it stored to a file / folder using `extractEntry`. You can also have the whole archive written to a directory using `extractTo`.  

We have some examples using the library in the [examples folder](./examples) that demonstrate the use of the library for reading / writing.

## License 
This project is open source and freely available under the [Simplified BSD](http://opensource.org/licenses/BSD-2-Clause) license. Should that license not meet your needs, please contact me. 


  Copyright (c) 2016, SBML Team  
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met: 
  
  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer. 
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution. 
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
