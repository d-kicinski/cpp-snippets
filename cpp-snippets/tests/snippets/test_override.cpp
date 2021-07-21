#include <catch2/catch.hpp>
#include <iostream>

class Base {
  public:
    virtual auto print_vector(std::vector<std::string> const &list) -> void
    {
        std::cout << "BASE: ";
        for (const auto &item : list)
            std::cout << item << ", ";
        std::cout << std::endl;
    }

    auto print_vector(std::string const &item) -> void { print_vector(std::vector<std::string>{item}); }
};

class Derived : public Base {
  public:
    // gotcha!
    using Base::print_vector;
    auto print_vector(std::vector<std::string> const &list) -> void override
    {
        std::cout << "Derived: ";
        for (const auto &item : list)
            std::cout << item << ", ";
        std::cout << std::endl;
    }
};

TEST_CASE("override") {
    auto base = Base();
    auto derived = Derived();

    std::vector<std::string> strings = {"hello", "world", "1"};
    base.print_vector(strings);
    base.print_vector("single string");

    derived.print_vector(strings);
    derived.print_vector("single string");

}