#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

#include <iostream>

#include <snippets/vector_utils.hpp>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};
  //const auto new_end {remove(begin(v), end(v), 2)};
  // v.erase(new_end, end(v));

  for (auto i : v) {
    cout << i << ", ";
  }
  cout << '\n';

  // now remove all 2's from vector


}
