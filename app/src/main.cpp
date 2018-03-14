#include <iostream>
#include <map>

std::pair<int , int> divide_remainder(int dividend, int divisior)
{
  return std::pair<int, int>(dividend/divisior, divisior);
}


int main(int argc, char *argv[])
{


  // Strictured bindings
  // variables will be declared and initialized but we have to catch all returned values
  auto [fraction, reminder] = divide_remainder(16, 3);

  // Variables have to be declared before invocation but some returned values could be ignored
  std::tie(std::ignore, reminder) = divide_remainder(16, 5);


  // this comiles
  std::map<std::string,  int> person_age {
    {"Dave", 21},
    {"Dejw", 17},
    {"Foo", 53},
  };

  // // this not compiles -> template type deduction failed
  // std::map person_id {
  //   {"Dave", 1},
  //   {"Foo", 2},
  // };

  for (const auto &[name, age] : person_age) {
    std::cout << name << " is " << age << "\n";
  }


  // if/switch initializers -> delete one entry in defined map
  if (auto itr (person_age.find("Dejw")); itr != person_age.end()) {
    std::cout << "itr is valid" << "\n";
    auto value = person_age.at("Dejw");
    //auto value2 = person_age[itr];
    std::cout << itr->first  << "\n";
    std::cout << itr->second  << "\n";
    person_age.erase(itr);
  }

  // try to acces that deleted entry -> it throws 'std::out_of_range '
  // auto what = person_age.at("Dejw");

  return 0;
}
