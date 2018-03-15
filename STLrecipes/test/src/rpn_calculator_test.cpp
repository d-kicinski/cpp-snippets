#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include <sstream>
#include <iterator>

#include <stlrecipes/rpn_calculator.hpp>

TEST_CASE( "RPN calculator", "[rpn]" ) {


  std::string equation {"2 2 +"};
  std::istringstream str(equation);

  REQUIRE( stlrecipes::evaluate_rpn(std::istream_iterator<std::string>{str}, {}) == 4.0 );


}
