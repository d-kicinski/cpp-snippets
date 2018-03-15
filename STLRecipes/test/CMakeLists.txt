## Testing
include(Catch)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(stlrecipes_test
  src/rpn_calculator_test.cpp
  #src/catch_test.cpp
  )

target_compile_features(stlrecipes_test PRIVATE cxx_auto_type)
target_link_libraries(stlrecipes_test Catch STLRecipes::stlrecipes)

catch_discover_tests(stlrecipes_test)


