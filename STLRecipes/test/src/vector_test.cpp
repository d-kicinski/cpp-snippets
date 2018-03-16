#include "catch.hpp"

#include <vector>
#include <iostream>
#include <algorithm>

#include <stlrecipes/vector_utils.hpp>

TEST_CASE("Insert all", "[vector]") {

  std::vector v {1, 2, 3, 2};
  stlrecipes::insert_all(v, 8, 2, 6, 4);
  REQUIRE(v.size() == 8);

  // now remove all 2's from vector
  const auto new_end {remove(std::begin(v), std::end(v), 2)};
  REQUIRE(v.size() == 8);
  REQUIRE(v.capacity() == 8);




}
