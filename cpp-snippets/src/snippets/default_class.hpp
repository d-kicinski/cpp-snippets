#pragma once
#include <utility>
#include <vector>

template <typename T> class Container {
  public:
    using iterator = typename std::vector<T>::iterator;

    virtual auto begin() -> iterator {
       return _data.begin();
    }
    virtual auto end() -> iterator {
       return _data.end();
    }
    virtual auto shape() -> std::vector<int> {
        return std::vector<int>();
    }
    auto size() -> int {
        return 0;
    }

  private:
    std::vector<T> _data;
};

template <typename T> class OverriddenContainer : public Container<T> {
  public:
    explicit OverriddenContainer(std::vector<int> shape) : _shape(std::move(shape)) {
        T const value = T(1);
       _data = std::vector(_calculate_size(_shape), value);
    }
    using iterator = typename Container<T>::iterator;
    auto begin() -> iterator { return _data.begin();}
    auto end() -> iterator { return _data.end(); }
    auto shape() -> std::vector<int> { return _shape; }

  private:
    std::vector<int> _shape;
    std::vector<T> _data;

    auto _calculate_size(std::vector<int> const & shape) -> int {
        return std::reduce(shape.begin(), shape.end(), T(1), std::multiplies<>());
    }
};