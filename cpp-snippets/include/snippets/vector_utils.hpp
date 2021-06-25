#pragma once

#include <iostream>
#include <vector>

namespace snippets {

// quickly inster a few objects to vector, implemented using fold expresion
template <typename T, typename... Ts>
void insert_all(std::vector<T> &vec, Ts... ts) {
  (vec.push_back(ts), ...);
}

} // namespace snippets
