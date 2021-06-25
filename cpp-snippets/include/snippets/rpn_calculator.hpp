#pragma once

// include a lot of helpers from STL
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

namespace snippets {

/**
 *  \brief RPN parser
 *
 *  Accept an iterator pair, which denotes the beginning and end of a
 *  mathematical expression in string form, which will be concumed token by
 * token.
 *
 *  \param param
 *  \return float evaluation of given mathematical expression
 */
template <typename IT> float evaluate_rpn(IT it, IT end) {

  // While we iterate though the token we need  to memorize all operand on the
  // way until we see an operation, stack should be perfect
  std::stack<float> val_stack;

  // Helper to make pop operation return popped element
  auto pop_stack([&]() {
    auto r{val_stack.top()}; // get top value copy
    val_stack.pop();
    return r;
  });

  // To each supprted operations we assain callable lamda taking two argumant
  std::map<std::string, float (*)(float, float)> ops{
      {"+", [](float a, float b) { return a + b; }},
      {"-", [](float a, float b) { return a - b; }},
      {"*", [](float a, float b) { return a * b; }},
      {"/", [](float a, float b) { return a / b; }},
      {"^", [](float a, float b) { return std::pow(a, b); }},
      {"%", [](float a, float b) { return std::fmod(a, b); }},
  };

  for (; it != end; ++it) {
    // string stream can be treated as string parser here
    std::istringstream ss{*it};

    if (float val; ss >> val) {
      // succesfully parsed token to float so it's should be operand
      val_stack.push(val);
    } else {
      // not operand, so it has to be operation token, get operand from stack
      const auto &r{pop_stack()};
      const auto &l{pop_stack()};

      // try to extrack and evaluate operation on operands
      try {
        const auto &op(ops.at(*it));
        const float result{op(l, r)};
        val_stack.push(result);
      } catch (const std::out_of_range &) {
        // out_of_range exception means .at(string op) didn't find supported
        // opertion
        throw std::invalid_argument(*it);
      }
    }
  }

  return val_stack.top();
}
} // namespace snippets
