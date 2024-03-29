###############################################################################
#
# Description       : CMake build script for libCOMBINE Python bindings
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libCOMBINE.  Please visit http://sed-ml.org for more
# information about COMBINE, and the latest version of libCOMBINE.
#
# Copyright (c) 2013, Frank T. Bergmann  
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met: 
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer. 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution. 
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
###############################################################################

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
find_package(PythonInterp)

# specify that the same python library should be found 
# as the one the selected interpreter uses
set (Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_STRING})
find_package(PythonLibs)


####################################################################
#
# determine local dependencies, so as to re-swig if one of them changed
# 

file(GLOB SWIG_DEPENDENCIES 
  ${CMAKE_CURRENT_SOURCE_DIR}/*.i 
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.i
  ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.h
  )

#
# Remove SWIG wrappers if requested
#
if (LIBCOMBINE_REMOVE_WRAPPERS)
  foreach(file 
    ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
  )
    if (EXISTS ${file})
      FILE(REMOVE ${file})
    endif()
  endforeach()
endif(LIBCOMBINE_REMOVE_WRAPPERS)


set(SWIG_EXTRA_FLAGS -DSWIGEXPORT -DLIBSBML_CPP_NAMESPACE_BEGIN= -DLIBSBML_CPP_NAMESPACE_END= -DLIBSBML_CPP_NAMESPACE_QUALIFIER= -DLIBSBML_CPP_NAMESPACE_USE=)
if(NOT UNIX)
  set(SWIG_EXTRA_FLAGS ${SWIG_EXTRA_FLAGS} -DSWIGWIN -DSWIG_CSHARP_NO_WSTRING_HELPER )
endif()


ADD_CUSTOM_COMMAND(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS  -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
      -I${CMAKE_CURRENT_SOURCE_DIR}/../../
      -I${CMAKE_CURRENT_BINARY_DIR}/../../
      -I${CMAKE_CURRENT_SOURCE_DIR}/../../omex
      -I${CMAKE_CURRENT_SOURCE_DIR}
      -I${LIBSBML_INCLUDE_DIR}/
      -I${LIBNUML_INCLUDE_DIR}/
      -c++
      -python    
      ${SWIG_EXTRA_FLAGS}     
      ${SWIG_EXTRA_ARGS}     
      -o ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp 
      ${CMAKE_CURRENT_SOURCE_DIR}/libcombine.i

  COMMAND "${CMAKE_COMMAND}"
  ARGS  -DCUR_BIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
        -DVERSION=\"${LIBCOMBINE_VERSION}\"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/add_version.cmake"

  DEPENDS local.i local.cpp local-contrib.i
    COMMENT "Swig Python source") 

add_custom_target(binding_python_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp)
  
####################################################################
#
# Build native library
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${LIBSBML_INCLUDE_DIR})
include_directories(BEFORE ${LIBNUML_INCLUDE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/../../)
add_definitions(-DLIBCOMBINE_STATIC)
include_directories(${PYTHON_INCLUDE_DIRS})
if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

if (MSVC)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC)

add_library(binding_python_lib SHARED libcombine_wrap.cpp)
add_dependencies( binding_python_lib binding_python_swig) 

set_target_properties (binding_python_lib PROPERTIES OUTPUT_NAME "_libcombine")
if (UNIX)
  set_target_properties (binding_python_lib PROPERTIES PREFIX "")
  set_target_properties (binding_python_lib PROPERTIES SUFFIX ".so")
else()    
  if (CYGWIN)
    set_target_properties (binding_python_lib PROPERTIES PREFIX "")
    set_target_properties (binding_python_lib PROPERTIES SUFFIX ".dll")
  else()
    set_target_properties (binding_python_lib PROPERTIES SUFFIX ".pyd")  
  endif()
endif()


if(APPLE OR UNIX)
  option (PYTHON_USE_DYNAMIC_LOOKUP
  "Do not actually link against the python library, instead use the undefined lookup mechanism, that ." OFF)
  mark_as_advanced(PYTHON_USE_DYNAMIC_LOOKUP)
endif(APPLE OR UNIX)

if (PYTHON_USE_DYNAMIC_LOOKUP)
  if (APPLE)
    set_target_properties (binding_python_lib PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  endif()
  target_link_libraries(binding_python_lib ${LIBCOMBINE_LIBRARY}-static)
else()
  target_link_libraries(binding_python_lib ${LIBCOMBINE_LIBRARY}-static ${PYTHON_LIBRARIES})
endif()

# 
# Determine the python installation directory
#
set(PYTHON_PACKAGE_INSTALL_DIR)
if (UNIX OR CYGWIN) 
  execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "import sys; sys.stdout.write('{}.{}'.format(*sys.version_info[:2]))"
    OUTPUT_VARIABLE PYTHON_VERSION)
  set(PYTHON_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/python${PYTHON_VERSION}/site-packages)
else()
  set(PYTHON_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/python)
endif()

INSTALL(TARGETS binding_python_lib DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/libcombine )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/libcombine.pth" "libcombine\n")
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcombine.pth  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcombine.py  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/libcombine )
