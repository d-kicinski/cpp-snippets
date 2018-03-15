#include <vector>
#include <iostream>


template <typename T, typename ... Ts>
void insert_all(std::vector<T> & vec, Ts ... ts)
{
  (vec.push_back(ts), ...);
}

int main()
{
  std::vector v {1, 2, 3};
  insert_all(v, 4, 5, 6);

  for (auto const & val  : v){
    std::cout << val << "\n";
  }
}
