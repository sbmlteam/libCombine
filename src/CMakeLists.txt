###############################################################################
#
# Initialize Ca sources
#

###############################################################################
#
# utility macro for copying files only if they have changed, for this it is
# assumed that the source file is always created. Then the macro is called.
# If the target file will only be overwritten if it does not yet exist, or
# its content is different. At the end the source file will be removed.
#
macro(copy_if_different_and_remove source target)
# message(
# "
# copy_if_different_and_remove called with:
#     source = ${source}
#     target = ${target}
# "
# )
file(READ ${source} CONTENT)

if (EXISTS ${target})
    # message("target exists")
    file(READ ${target} CURRENT_CONTENT)
    string(COMPARE EQUAL ${CURRENT_CONTENT} ${CONTENT} IS_SAME)
    if (NOT ${IS_SAME})
        #message("content is different")
        file(WRITE ${target} ${CONTENT})
    endif()
else()
    #message("target does not exist")
    file(WRITE ${target} ${CONTENT})
endif()

file(REMOVE ${source})

endmacro(copy_if_different_and_remove)

###############################################################################
#
# create libcombine-config-common.h
#
include(CheckIncludeFiles)
check_include_files (check.h HAVE_CHECK_H)
check_include_files (expat.h HAVE_EXPAT_H)
check_include_files (errno.h HAVE_ERRNO_H)
check_include_files (ieeefp.h HAVE_IEEEFP_H)
check_include_files (math.h HAVE_MATH_H)
check_include_files (sys/types.h HAVE_SYS_TYPES_H)
check_include_files (float.h STDC_HEADERS)
check_include_files (stdarg.h STDC_HEADERS)
check_include_files (stdlib.h STDC_HEADERS)
check_include_files (string.h STDC_HEADERS)

set(WORDS_BIGENDIAN)
if (UNIX)
  include (TestBigEndian)
  test_big_endian(WORDS_BIGENDIAN)
else()
  # test_big_endian seems to fail with nmake (VS 2010) on windows
  # however, windows is always little endian, so catch this here
  set(WORDS_BIGENDIAN FALSE)
endif()

# for whatever reason some of the values are not correctly picked up
# so we encode these values here
if (MSVC)
  set(HAVE_ERRNO_H TRUE)
  set(HAVE_IEEEFP_H TRUE)
  set(STDC_HEADERS TRUE)
  set(HAVE_MATH_H TRUE)
  set(HAVE_SYS_TYPES_H TRUE)
endif()


include(CheckLibraryExists)
check_library_exists(m sqrt "" HAVE_LIBM)

# generate configuration for this system
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/omex/common/libcombine-config-common.h.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/omex/common/libcombine-config-common.h
)

# Replace: @LIBCOMBINE_VERSION@ and @LIBCOMBINE_VERSION_NUMERIC@
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/omex/common/libcombine-version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/omex/common/libcombine-version.h"
)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/omex/common/libcombine-namespace.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/omex/common/libcombine-namespace.h"
)

  
###############################################################################
#
# mark header files for installation
#

foreach(dir annotation common compress conversion extension units util validator xml  )

    file(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/omex/${dir}/*.h")
    install(FILES ${header_files} DESTINATION include/omex/${dir})

endforeach(dir)


file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/omex/*.h")
install(FILES ${files} DESTINATION include/omex)


###############################################################################
#
# copy build specific header files
#

file(GLOB additional_common "${CMAKE_CURRENT_BINARY_DIR}/omex/common/*.h")

install(FILES ${additional_common} DESTINATION include/omex/common)

###############################################################################
#
# specify include directories
#

if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)
include_directories(BEFORE ${LIBCOMBINE_ROOT_SOURCE_DIR}/src/omex)
include_directories(BEFORE ${LIBCOMBINE_ROOT_SOURCE_DIR}/src)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/src)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/src/omex)


###############################################################################
#
# Find all sources
#

macro(ADD_FUNCTION directory)

    set(prefix "omex/")

    if ("${directory}" STREQUAL "omex")
        set(prefix "")
    endif()


    file(GLOB temp
            ${prefix}${directory}/*.cpp
            ${prefix}${directory}/*.cxx
            ${prefix}${directory}/*.c
            ${prefix}${directory}/*.h)

    # Set the constraint files to be 'headers' as they don't have to be compiled
    # since they don't contain symbols but rather are included directly.  Could
    # remove them, but that keeps their content from being found in searches, etc.
    # in IDEs such as VisualStudio.
    foreach(tempFile ${temp})
        if ("${directory}" STREQUAL "validator/constraints")
            if ("${tempFile}" MATCHES ".*Constraints.cpp")
              set_source_files_properties(
                  ${tempFile}
                  PROPERTIES HEADER_FILE_ONLY true
                  )
#              list(REMOVE_ITEM temp "${tempFile}")
            endif()
        endif()
        if ("${tempFile}" MATCHES ".*.cxx$")
          set_source_files_properties(
              ${tempFile}
              PROPERTIES HEADER_FILE_ONLY true
              )
        endif()
    endforeach()

    # create source group for IDEs
    source_group(${directory} FILES ${temp})

    # add to libcombine sources
    set(LIBCOMBINE_SOURCES ${LIBCOMBINE_SOURCES} ${temp})

endmacro(ADD_FUNCTION)

foreach (directory common omex)

  ADD_FUNCTION(${directory})
               
endforeach()

###############################################################################
#
# Build library
#

# used to create CMake config files for projects using this library
if (${CMAKE_VERSION} VERSION_GREATER 2.8.7)
include(CMakePackageConfigHelpers)
endif()

SET (INCLUDE_DESTINATION)
if (${CMAKE_VERSION} VERSION_GREATER "2.8.11")
  set(INCLUDE_DESTINATION INCLUDES DESTINATION include)
endif()


if (NOT LIBCOMBINE_SKIP_SHARED_LIBRARY)

add_library (${LIBCOMBINE_LIBRARY} SHARED ${LIBCOMBINE_SOURCES} )

if (LIBCOMBINE_SHARED_VERSION)
  SET_TARGET_PROPERTIES(${LIBCOMBINE_LIBRARY} 
    PROPERTIES
      SOVERSION ${LIBCOMBINE_VERSION_MAJOR}
      VERSION ${LIBCOMBINE_VERSION_MAJOR}.${LIBCOMBINE_VERSION_MINOR}.${LIBCOMBINE_VERSION_PATCH}
  )
endif()

target_link_libraries(${LIBCOMBINE_LIBRARY} ${LIBCOMBINE_LIBS} ${EXTRA_LIBS})

message (VERBOSE "GNU ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_FULL_LIBDIR}")

INSTALL(TARGETS ${LIBCOMBINE_LIBRARY}
        EXPORT  ${LIBCOMBINE_LIBRARY}-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ${INCLUDE_DESTINATION}
)

# and install the exported target configuration
INSTALL(EXPORT ${LIBCOMBINE_LIBRARY}-targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)

if (${CMAKE_VERSION} VERSION_GREATER 2.8.7)

CONFIGURE_PACKAGE_CONFIG_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/libcombine-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

WRITE_BASIC_PACKAGE_VERSION_FILE(
  ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-config-version.cmake 
  VERSION ${PROJECT_VERSION}
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
  
INSTALL(
  FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-config-version.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
endif()

endif()

add_library (${LIBCOMBINE_LIBRARY}-static STATIC ${LIBCOMBINE_SOURCES} )

if (WIN32 AND NOT CYGWIN)
    # don't decorate static library 
    set_target_properties(${LIBCOMBINE_LIBRARY}-static PROPERTIES COMPILE_DEFINITIONS "LIBLAX_STATIC=1;LIBCOMBINE_STATIC=1")
endif(WIN32 AND NOT CYGWIN)

target_link_libraries(${LIBCOMBINE_LIBRARY}-static ${LIBCOMBINE_LIBS} ${EXTRA_LIBS})

INSTALL(TARGETS ${LIBCOMBINE_LIBRARY}-static
        EXPORT  ${LIBCOMBINE_LIBRARY}-static-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ${INCLUDE_DESTINATION}
)


# and install the exported target configuration
INSTALL(EXPORT ${LIBCOMBINE_LIBRARY}-static-targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)

if (${CMAKE_VERSION} VERSION_GREATER 2.8.7)

CONFIGURE_PACKAGE_CONFIG_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/libcombine-static-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-static-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

WRITE_BASIC_PACKAGE_VERSION_FILE(
  ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-static-config-version.cmake 
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
  
INSTALL(
  FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-static-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMBINE_LIBRARY}-static-config-version.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
endif()

##############################################################################
#
# construct list of all header files to create dependency list for 
# language bindings
#

file(GLOB LIBCOMBINE_HEADER_FILES "${CMAKE_CURRENT_BINARY_DIR}/omex/common/*.h")    
foreach(file ${LIBCOMBINE_SOURCES})
   
   if ("${file}" MATCHES "h$" )
     get_filename_component(full_path ${file} ABSOLUTE)
     list(APPEND LIBCOMBINE_HEADER_FILES ${full_path})     
   endif()

endforeach()

##############################################################################
#
# create language bindings
#
add_subdirectory(bindings)
