# cmake script to test the archive given in in
# - create static build (x86 and x64)
# - create all python wheels for listed python versions

# first extract source file if it exists

file(GLOB archives "${CMAKE_CURRENT_SOURCE_DIR}/in/*.tar.gz")


set(COPASI_VERSION_MAJOR)
set(COPASI_VERSION_MINOR)
set(COPASI_VERSION_PATCH)
set(COPASI_DOTTED_VERSION)
set(COPASI_ARCHIVE)
set(COPASI_ARCHIVE_NAME)


foreach(archive ${archives})
get_filename_component(COPASI_ARCHIVE_NAME ${archive} NAME)
# extract version from a string like 'libCombine-0.2.3-Source.tar.gz'
string(FIND ${COPASI_ARCHIVE_NAME} "-Source" index)
if (${index} EQUAL -1)
continue()
endif()

string(LENGTH COPASI_ARCHIVE_NAME name_length)
math(EXPR end_pos "${index} - 11")
string(SUBSTRING ${COPASI_ARCHIVE_NAME} 11 ${end_pos} version)
set(COPASI_DOTTED_VERSION ${version})
set(COPASI_ARCHIVE ${archive})
endforeach()

string(STRIP "${COPASI_DOTTED_VERSION}" VersionString)
set(COPASI_DOTTED_VERSION ${VersionString})
string(REPLACE "." ";" VersionString "${VersionString}" )
string(REPLACE "-" ";" VersionString "${VersionString}" )
list(LENGTH VersionString versionLength)
list(GET VersionString 0 COPASI_VERSION_MAJOR )
list(GET VersionString 1 COPASI_VERSION_MINOR )
list(GET VersionString 2 COPASI_VERSION_PATCH )




# # print what we have 
# message(${COPASI_VERSION_MAJOR})
# message(${COPASI_VERSION_MINOR})
# message(${COPASI_VERSION_PATCH})
# message("${COPASI_DOTTED_VERSION}")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt "${COPASI_DOTTED_VERSION}")

# extract archive if src dir does not exist
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src)

# extract archive 

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libCombine-${COPASI_DOTTED_VERSION}-Source)
message("extracting archive")
execute_process(
COMMAND ${CMAKE_COMMAND} -E tar xzf ${COPASI_ARCHIVE}
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()

# rename archive
execute_process(
COMMAND ${CMAKE_COMMAND} -E rename libCombine-${COPASI_DOTTED_VERSION}-Source src
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


endif()


