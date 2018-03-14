cmake_minimum_required(VERSION 3.5)
project(stl17-cookbook)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(out
  app/src/main.cpp)

add_custom_target(run
  COMMAND out
  COMMENT " Run binary in ${CMAKE_CURRENT_SOURCE_DIR}"
)
