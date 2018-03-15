#include <stlrecipes/rpn_calculator.hpp>

#include <iostream>
#include <iterator>
#include <sstream>


int main(int argc, char *argv[])
{

  std::string equation {"2 2 +"};
  std::istringstream str(equation);

  auto const result = stlrecipes::evaluate_rpn(std::istream_iterator<std::string>{std::cin}, {});

  std::cout << result << "\n";
  return 0;
}

