cmake_minimum_required(VERSION 3.5)
project(app VERSION 0.0.1 LANGUAGES CXX)

add_executable(app src/main)
target_compile_features(app PRIVATE cxx_auto_type)

find_package(STLRecipes 1.0 REQUIRED)
target_link_libraries(app STLRecipes::STLRecipes)
