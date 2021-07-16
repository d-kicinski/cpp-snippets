#include <catch2/catch.hpp>

#include <iostream>
#include <snippets/abstract_class.hpp>

template <typename T>
auto accept_abstract_class(Container<T> & container) -> void
{
    for (auto const &item : container) {
        std::cout << item << std::endl;
    }
}

TEST_CASE("abstract")
{
    Matrix<float> matrix({2, 6});
    accept_abstract_class<float>(matrix);
}