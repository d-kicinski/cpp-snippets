#include <iostream>
#include <map>
#include <stack>

std::pair<int, int> divide_remainder(int dividend, int divisior)
{
    return std::pair<int, int>(dividend / divisior, divisior);
}

template <typename T1, typename T2> class map_wrapper {
    T1 t1;
    T2 t2;

  public:
    explicit map_wrapper(T1 t1_, T2 t2_) : t1(t1_), t2(t2_) {}
};

template <typename T1, typename T2> map_wrapper<T1, T2> make_map(T1 t1, T2 t2) { return {t1, t2}; }

int main(int argc, char *argv[])
{
    // Strictured bindings
    // variables will be declared and initialized but we have to catch all
    // returned values
    auto [fraction, reminder] = divide_remainder(16, 3);

    // Variables have to be declared before invocation but some returned values
    // could be ignored
    std::tie(std::ignore, reminder) = divide_remainder(16, 5);

    // this comiles
    std::map<std::string, int> person_age{
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
    if (auto itr(person_age.find("Dejw")); itr != person_age.end()) {
        std::cout << "itr is valid"
                  << "\n";
        auto value = person_age.at("Dejw");
        // auto value2 = person_age[itr];
        std::cout << itr->first << "\n";
        std::cout << itr->second << "\n";
        person_age.erase(itr);
    }

    // try to acces that deleted entry -> it throws 'std::out_of_range '
    // auto what = person_age.at("Dejw");

    std::tuple tpl{1, 1.0, "abc"};  // OK
    std::tuple tpl2(1, 1.0, "abc"); // OK
    // std::map my_map ({1, "abc"}, {2, "def"}); // Failed: Class argument
    // deduction failded

    map_wrapper mapa2{2.0, "Hello"}; // OK!  yo its 2018

    map_wrapper<float, std::string> mapa1{2.0, std::string("Hello")}; // OK but inconvinient and old way

    std::stack<float> val_stack;
    val_stack.push(10);
    val_stack.push(50);

    auto ref = val_stack.top();
    val_stack.pop();

    std::cout << ref << "\n";

    return 0;
}
