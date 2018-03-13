#include <iostream>
#include <map>

std::pair<int , int> divide_remainder(int dividend, int divisior)
{
  return std::pair<int, int>(dividend/divisior, divisior);
}


int main(int argc, char *argv[])
{
  // std::cout << "Hello, world!\n";

  std::cout << " # Structured bindings" << "\n";
  auto [fraction, reminder] = divide_remainder(16, 3);
  std::cout << " 16 / 3 is "
            << fraction << " with reminder of "
            << reminder
            << "\n";

  std::map<std::string,  int> person_age {
    {"Dave", 21},
    {"Dejw", 17},
    {"Foo", 53},
  };

  for (const auto &[name, age] : person_age) {
    std::cout << name << " is " << age << "\n"; 
  }


  return 0;
}
