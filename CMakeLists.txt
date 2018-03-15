cmake_minimum_required(VERSION 3.10)
project(stl17-cookbook)
enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(STLrecipes)
add_subdirectory(app)

#add_executable(out app/main.cpp)
#target_link_libraries(out STLrecipes)

add_custom_target(run
  COMMAND out
  COMMENT " Run binary in ${CMAKE_CURRENT_SOURCE_DIR}"
)

