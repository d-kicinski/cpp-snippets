//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
  return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
  REQUIRE( Factorial(1) == 100 );
}

TEST_CASE("Test1", "[unit]") {
  int a = 1;
  int b = 2;
  REQUIRE(a == b);
}

TEST_CASE("Test2") {
  int a = 1;
  int b = 2;
  REQUIRE(a == b);
}

TEST_CASE("Test3", "[a][b][c]") {
  int a = 1;
  int b = 2;
  REQUIRE(a == b);
}
