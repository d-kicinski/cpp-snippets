#pragma once

struct return_fail {
};
struct return_success {
};

template <typename T> class Return {
  public:
    explicit Return(T &&value) : Return(value, return_success{}) {}

    Return(std::string &&what, return_fail) : _what(what) {}

    Return(T &&value, return_success) : _value(value) {}

    static auto ok(T &&value) -> Return<T> { return Return{std::move(value), return_success{}}; }

    static auto fail(std::string what) -> Return<T> { return Return{std::move(what), return_fail{}}; }

    auto what() -> std::string { return _what; }

    auto is_ok() -> bool
    {
        if (_what.empty()) {
            return true;
        } else {
            return false;
        }
    }

    auto operator*() -> T { return _value; }

  private:
    T _value;
    std::string _what;
};
