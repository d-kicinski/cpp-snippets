#pragma once
#include <utility>
#include <vector>

template <typename T> class Container {
  public:
    using iterator = typename std::vector<T>::iterator;

    virtual auto begin() -> iterator = 0;
    virtual auto end() -> iterator = 0;
    virtual auto raw_data() -> T * = 0;
    virtual auto shape() -> std::vector<int> = 0;
    virtual auto size() -> int = 0;
};

template <typename T> class Matrix : public Container<T> {
  public:
    explicit Matrix(std::vector<int> shape) : _shape(std::move(shape)), _size(_calculate_size(_shape)), _data(_size) {}
    using iterator = typename Container<T>::iterator;
    auto begin() -> iterator { return _data.begin();}
    auto end() -> iterator { return _data.end(); }
    auto raw_data() -> T * { return _data.data(); }
    auto shape() -> std::vector<int> { return _shape; }
    auto size() -> int { return _size; }

  private:
    std::vector<int> _shape;
    int _size;
    std::vector<T> _data;

    auto _calculate_size(std::vector<int> const & shape) -> int {
        return std::reduce(shape.begin(), shape.end(), T(1), std::multiplies<>());
    }
};