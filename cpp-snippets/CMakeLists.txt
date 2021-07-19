cmake_minimum_required(VERSION 3.10)
project(snippets VERSION 1.0.0 LANGUAGES CXX)


add_library(snippets
        src/snippets/rpn_calculator.cpp
        src/snippets/vector_utils.cpp
        src/snippets/granting_access_private_inheritance.hpp
        src/snippets/avx2_dot_product.hpp
        src/snippets/abstract_class.hpp
        src/snippets/default_class.hpp
        src/snippets/unique_ptr.hpp
        src/snippets/return_type.hpp
        src/snippets/ranges_basic.hpp
        )

target_include_directories(snippets
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

target_compile_features(snippets PRIVATE cxx_auto_type)
target_compile_options(snippets PRIVATE -Werror -Wall PUBLIC -mavx2)
set_property(TARGET snippets PROPERTY CXX_STANDARD 20)

add_executable(snippets_test
        tests/catch_main.cpp
        tests/snippets/test_rpn_calculator.cpp
        tests/snippets/test_vector.cpp
        tests/snippets/test_avx2.cpp
        tests/snippets/test_abstract_class.cpp
        tests/snippets/test_default_class.cpp
        tests/snippets/test_unique_ptr.cpp
        tests/snippets/test_return_type.cpp
        tests/snippets/test_ranges_basic.cpp
        )
target_link_libraries(snippets_test snippets Catch2::Catch2)
set_property(TARGET snippets_test PROPERTY CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/third-party/Catch2/contrib/Catch.cmake)
enable_testing()
catch_discover_tests(snippets_test)
