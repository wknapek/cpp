get_filename_component(ProjectId ${CMAKE_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)


file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

include_directories(${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})




set(CMAKE_RUNTIME_OUTPUT_DIRECTORY %{sourceDir})



IF(NOT CMAKE_BUILD_TYPE)
  #SET(CMAKE_BUILD_TYPE "Debug")
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF()
message( "Current dir: ${PROJECT_SOURCE_DIR}" )

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


find_package(Boost 1.47 COMPONENTS filesystem unit_test_framework REQUIRED)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}/boost")
#message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
#message(status "** Boost Libraries: ${Boost_LIBRARIES}")
set(Boost_ADDITIONAL_VERSIONS "1.54" "1.54.0")
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS}/boost)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR}/boost)
IF(UNIX)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -fexceptions -lboost_system -lboost_serialization -lboost_thread -lpthread -lboost_filesystem -lboost_regex")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -g -O2 -Wall -std=c++11 -fexceptions -lboost_system -lboost_serialization -lboost_thread -lpthread -lboost_filesystem")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
IF(CMAKE_BUILD_TYPE EQUAL "Release")
  message(status "release")

ENDIF()
IF(CMAKE_BUILD_TYPE EQUAL "Debug")
   message(status "debug")
ENDIF()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
