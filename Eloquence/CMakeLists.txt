cmake_minimum_required(VERSION 3.18)
project(Eloquence VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

string(TIMESTAMP BUILD_DATE)
message(STATUS "Will add the following timestamp to binary: ${BUILD_DATE}")

add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")
add_compile_definitions(BUILD_DATE="${BUILD_DATE}")

add_compile_options(-Wall -Wextra -pedantic -Werror)

message(STATUS "Checking whether all RapidXml files exist anywhere")
message(STATUS "Install RapidXml from https://rapidxml.sourceforge.net/ if files do not exist")

set(RAPIDXML_NOT_FOUND BOOL TRUE)
set(RAPIDXML_ITERATORS_NOT_FOUND BOOL TRUE)
set(RAPIDXML_PRINT_NOT_FOUND BOOL TRUE)
set(RAPIDXML_UTILS_NOT_FOUND BOOL TRUE)

foreach(dir ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
  if(EXISTS "${dir}/rapidxml.hpp")
    message(STATUS "Found ${dir}/rapidxml.hpp")
    set(RAPIDXML_NOT_FOUND FALSE)
  endif()

  if(EXISTS "${dir}/rapidxml_iterators.hpp")
    message(STATUS "Found ${dir}/rapidxml_iterators.hpp")
    set(RAPIDXML_ITERATORS_NOT_FOUND FALSE)
  endif()

  if(EXISTS "${dir}/rapidxml_print.hpp")
    message(STATUS "Found ${dir}/rapidxml_print.hpp")
    set(RAPIDXML_PRINT_NOT_FOUND FALSE)
  endif()

  if(EXISTS "${dir}/rapidxml_utils.hpp")
    message(STATUS "Found ${dir}/rapidxml_utils.hpp")
    set(RAPIDXML_UTILS_NOT_FOUND FALSE)
  endif()
endforeach()

if(RAPIDXML_NOT_FOUND)
  message(FATAL_ERROR "Could not find rapidxml.hpp in any include directory")
endif()

if(RAPIDXML_ITERATORS_NOT_FOUND)
  message(FATAL_ERROR "Could not find rapidxml_iterators.hpp in any include directory")
endif()

if(RAPIDXML_PRINT_NOT_FOUND)
  message(FATAL_ERROR "Could not find rapidxml_print.hpp in any include directory")
endif()

if(RAPIDXML_UTILS_NOT_FOUND)
  message(FATAL_ERROR "Could not find rapidxml_utils.hpp in any include directory")
endif()

include_directories(
  "include"
)
add_executable(
  "elo"
  "src/main.cpp"
  "src/parse-hosts.cpp"
  "src/parse-runstats.cpp"
  "src/utils.cpp"
)

set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")
install(TARGETS "elo" DESTINATION "bin")
