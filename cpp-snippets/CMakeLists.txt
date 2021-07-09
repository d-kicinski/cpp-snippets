cmake_minimum_required(VERSION 3.10)
project(snippets VERSION 1.0.0 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

add_library(snippets
        src/snippets/rpn_calculator.cpp
        src/snippets/vector_utils.cpp
        src/snippets/granting_access_private_inheritance.hpp
        src/snippets/avx2_hello.hpp
        )
add_library(snippets::snippets ALIAS snippets)

target_include_directories(snippets
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

target_compile_features(snippets PRIVATE cxx_auto_type)
target_compile_options(snippets PRIVATE -Werror -Wall PUBLIC -mavx2)

add_executable(snippets_test
        tests/catch_main.cpp
        tests/snippets/test_rpn_calculator.cpp
        tests/snippets/test_vector.cpp
        tests/snippets/test_avx2.cpp
        )
target_link_libraries(snippets_test snippets::snippets Catch2::Catch2)

include(${CMAKE_SOURCE_DIR}/third-party/Catch2/contrib/Catch.cmake)
enable_testing()
catch_discover_tests(snippets_test)
