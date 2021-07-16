#include <catch2/catch.hpp>
#include <snippets/unique_ptr.hpp>

TEST_CASE("unique_ptr")
{
    using Type = std::vector<float>;
    auto first = std::make_unique<Type>(Type{1, 2, 3});
    auto second = std::make_unique<Type>(Type{4, 5, 6});
    auto composition = ViewableComposition<Type>(std::move(first), std::move(second));

    REQUIRE(composition.first() == Type{1, 2, 3});
    REQUIRE(composition.second() == Type{4, 5, 6});
}