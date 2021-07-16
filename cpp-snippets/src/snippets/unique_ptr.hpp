#include <memory>

template <typename T> class Data {
  public:
    explicit Data(int size) : _size(size) { _raw = new T[_size]; }
    ~Data() { delete _raw; }

    auto at(int index) -> T const &
    {
        if (index >= _size)
            return 0;
        return _raw[index];
    }

  private:
    T *_raw;
    int _size;
};

template <typename T> class ViewableComposition {
  public:
    ViewableComposition(std::unique_ptr<T> &&first, std::unique_ptr<T> &&second)
        : _first(std::move(first)), _second(std::move(second)) {}
    auto first() -> T & { return *_first; }

    auto second() -> T & { return *_second; }

  private:
    std::unique_ptr<T> _first;
    std::unique_ptr<T> _second;
};
