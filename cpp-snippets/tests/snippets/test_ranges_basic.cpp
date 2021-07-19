#include <catch2/catch.hpp>
#include <iostream>
#include <ranges>
#include <vector>

auto stl_example() -> void
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::vector<int> even_numbers;
    std::copy_if(begin(numbers), end(numbers), std::back_inserter(even_numbers), [](int n) { return n % 2 == 0; });

    std::vector<int> results;
    std::transform(begin(even_numbers), end(even_numbers), std::back_inserter(results), [](int n) { return n * 2; });

    for (int n : results) {
        std::cout << n << ' ';
    }
}

auto range_example() -> void
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    auto results = numbers
                   | std::views::filter([](int n) { return n % 2 == 0; })
                   | std::views::transform([](int n) { return n * 2; });

    for (auto v : results)
        std::cout << v << " ";
}

auto ranges_sort() -> void
{
    struct Task {
        std::string desc;
        unsigned int priority{0};
    };

    std::vector<Task> tasks{
        {"clean up my room", 10}, {"finish homework", 5}, {"test a car", 8}, {"buy new monitor", 12}};

    std::ranges::sort(tasks, std::ranges::greater{}, &Task::priority);
}

auto ranges_cpp_reference_example()
{
    auto const ints = {0, 1, 2, 3, 4, 5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    // "pipe" syntax of composing the views:
    for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    // a traditional "functional" composing syntax:
    for (int i : std::views::transform(std::views::filter(ints, even), square)) {
        std::cout << i << ' ';
    }
}

TEST_CASE("ranges basic")
{
    stl_example();
    range_example();
    ranges_cpp_reference_example();
    ranges_sort();
}