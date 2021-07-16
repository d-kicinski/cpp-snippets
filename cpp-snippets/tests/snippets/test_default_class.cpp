#include <catch2/catch.hpp>
#include <iostream>
#include <snippets/default_class.hpp>

template <typename T>
auto print_container_ref(Container<T> &container) -> void {
    for (const auto &item : container)
        std::cout << item << std::endl;
}

template <typename T>
auto print_container_copy(Container<T> container) -> void {
    for (const auto &item : container)
        std::cout << item << std::endl;
}

TEST_CASE("default class")
{
    auto shape = std::vector<int>{2, 3};
    auto container = OverriddenContainer<float>(shape);

    print_container_copy(container); // will use methods from Container<T>
    print_container_ref(container); // will use methods from OverriddenContainer<T>
}