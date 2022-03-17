# Locate library providing crossguid
# This module defines:
# ZIPPER_INCLUDE_DIR, where to find the headers
#
# ZIPPER, ZIPPER_DEBUG
# ZIPPER_FOUND
#
# $ZIPPER_DIR is an environment variable that would
# correspond to the ./configure --prefix=$ZIPPER_DIR

MACRO (FIND_ZIPPER)

ENDMACRO ()

find_library(ZIPPER_LIBRARY
    NAMES Zipper-static Zipper libZipper-static libZipper
    PATHS ${CMAKE_OSX_SYSROOT}/usr/lib
          ${COMBINE_DEPENDENCY_DIR}/lib
          ${ADDITIONAL_LIB_DIRS}
          $ENV{ZLIBROOT}/lib
          /usr/lib
          /usr/local/lib
    DOC "The file name of the ZIPPER library."
)

find_path(ZIPPER_INCLUDE_DIR
      NAMES zipper/zipper.h
      PATHS ${COMBINE_DEPENDENCY_DIR}/include
            $ENV{ZLIBROOT}/include
            ${CMAKE_OSX_SYSROOT}/usr/include
            /usr/include
            /usr/local/include
            NO_DEFAULT_PATH
      DOC "The directory containing the ZIPPER include files."
            )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    ZIPPER
    REQUIRED_VARS ZIPPER_LIBRARY ZIPPER_INCLUDE_DIR)

mark_as_advanced(ZIPPER_LIBRARY ZIPPER_INCLUDE_DIR)


