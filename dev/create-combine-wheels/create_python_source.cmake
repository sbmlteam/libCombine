# cmake script to test the archive given in in
# - create static build (x86 and x64)
# - create all python wheels for listed python versions

#if (NOT EXISTS ${PYTHON})
#  message(FATAL_ERROR "Need to specify PYTHON variable.")
#endif()

# read version


set(COPASI_VERSION_MAJOR)
set(COPASI_VERSION_MINOR)
set(COPASI_VERSION_PATCH)
set(COPASI_DOTTED_VERSION)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt")

    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" VersionString NEWLINE_CONSUME)
    string(STRIP "${VersionString}" VersionString)
    set(COPASI_DOTTED_VERSION ${VersionString})
    string(REPLACE "." ";" VersionString "${VersionString}" )
    string(REPLACE "-" ";" VersionString "${VersionString}" )
    list(LENGTH VersionString versionLength)
    list(GET VersionString 0 COPASI_VERSION_MAJOR )
    list(GET VersionString 1 COPASI_VERSION_MINOR )
    list(GET VersionString 2 COPASI_VERSION_PATCH )

endif()
set(VERSION ${COPASI_DOTTED_VERSION})

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tmp-python")
 file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tmp-python)
endif()


if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tmp-python/libcombine")
 file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tmp-python/libcombine)
endif()


if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tmp-python/build")
 foreach(version "2.7" "3.3" "3.4" "3.5" "3.6" "3.7")
 file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tmp-python/build/lib.win32-${version}/libcombine)
 file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tmp-python/build/lib.win-amd64-${version}/libcombine)
 endforeach()
endif()


file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ninja_x86/src/bindings/python/libcombine_wrap*)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/src)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/src/bindings/python/*cpp)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/src)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/src/bindings/python/*h)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/src)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/src/bindings/swig/*cpp)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/swig)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/src/bindings/swig/*h)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/swig)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ninja_x86/src/bindings/python/*py)
file(COPY ${SWIG_FILES} DESTINATION tmp-python/script)

file (GLOB SWIG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/python-src/*)
file(COPY ${SWIG_FILES} DESTINATION tmp-python)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/python-src/setup.py.in tmp-python/setup.py)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/python-src/Manifest.in tmp-python/Manifest.in)
