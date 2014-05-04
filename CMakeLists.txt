cmake_minimum_required(VERSION 2.8)

project (wxGraphStructure)
enable_language(C)
enable_language(CXX)

# Options
#   Usage: cmake -D<option name>=<value> <directory>
if(NOT DEFINED C_LANG_VERSION)
	set(C_LANG_VERSION   "c11")
endif()

if(NOT DEFINED CXX_LANG_VERSION)
	set(CXX_LANG_VERSION "c++11")
endif()

# Find all source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.hpp")

set (INCLUDE_DIRS "src")

include_directories(${INCLUDE_DIRS})

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=${C_LANG_VERSION}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_LANG_VERSION}")

ADD_DEFINITIONS(
	-Wall
)

# Compile and assemble the executable with all found source files
add_executable(wxGraphStructure ${SOURCES})

# Find and use pkg-config
find_package(PkgConfig REQUIRED)

# OpenGL linking
pkg_search_module(OPENGL REQUIRED gl)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
target_link_libraries(wxGraphStructure ${OPENGL_LIBRARIES})

# Find and use wx-config
find_package(wxWidgets COMPONENTS core base gl adv REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(wxGraphStructure ${wxWidgets_LIBRARIES})
