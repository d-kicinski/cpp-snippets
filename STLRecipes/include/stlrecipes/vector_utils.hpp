#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H


#include <vector>
#include <iostream>

namespace stlrecipes {

  // quickly inster a few objects to vector, implemented using fold expresion
  template <typename T, typename ... Ts>
  void insert_all(std::vector<T> & vec, Ts ... ts)
  {
    (vec.push_back(ts), ...);
  }

}


#endif /* VECTOR_UTILS_H */
