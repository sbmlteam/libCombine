## @file    CMakeLists.txt
## @brief   CMake build script for C++ example programs
## @author  Frank T. Bergmann
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${LIBCOMBINE_ROOT_SOURCE_DIR}/src)
include_directories(${LIBCOMBINE_ROOT_SOURCE_DIR}/include)
include_directories(BEFORE ${LIBCOMBINE_ROOT_BINARY_DIR}/src)


if (EXTRA_INCLUDE_DIRS) 
include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

foreach(example 

	create_archive
	
)
	add_executable(example_cpp_${example} ${example}.cpp)
	set_target_properties(example_cpp_${example} PROPERTIES  OUTPUT_NAME ${example})
	target_link_libraries(example_cpp_${example} ${LIBCOMBINE_LIBRARY}-static ${ZIPPER_LIBRARY} ${LIBZ_LIBRARY} ${LIBSBML_LIBRARY} ${EXTRA_LIBS})
  if (WITH_BOOST_FILESYSTEM)
    target_link_libraries(example_cpp_${example} ${BOOST_SYSTEM_LIBRARY} ${BOOST_FILESYSTEM_LIBRARY})
  endif()
  if (WITH_QT_FILESYSTEM)
    target_link_libraries(example_cpp_${example} ${QT_CORE_LIBRARY})
  endif()

endforeach()
