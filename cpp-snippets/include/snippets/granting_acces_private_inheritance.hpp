#pragma once

class Base {
  public:
    auto foo() -> void {}
    auto bar() -> void {}
};

class DerivedPublic : public Base {
    // Base::foo and Base::bar are available for the user
};

class DerivedPrivate : private Base {
    // only Base::foo is available, we explicitly grant access to Base type method
  public:
    using Base::foo;
};
