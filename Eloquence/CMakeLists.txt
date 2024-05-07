cmake_minimum_required(VERSION 3.18)
project(Eloquence VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(
  "include"
)
add_executable(
  "elo"
  "src/main.cpp"
)
