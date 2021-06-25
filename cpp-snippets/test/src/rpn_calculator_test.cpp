#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iterator>
#include <sstream>

#include <snippets/rpn_calculator.hpp>

TEST_CASE("RPN calculator", "[rpn]") {

  std::string equation{"2 2 +"};
  std::istringstream str(equation);

  REQUIRE(snippets::evaluate_rpn(std::istream_iterator<std::string>{str}, {}) ==
          4.0);
}
