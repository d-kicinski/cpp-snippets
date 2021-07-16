#include <catch2/catch.hpp>
#include <snippets/return_type.hpp>


auto may_fail(bool to_fail) -> Return<std::vector<float>> {
    if (to_fail) {
       return Return<std::vector<float>>::fail("failed");
    } else {
        std::vector<float> return_value{1, 2, 3, 4};
        return Return<std::vector<float>>::ok(std::move(return_value));
    }
}


TEST_CASE("return") {
    auto return_ok = may_fail(false);
    REQUIRE(return_ok.is_ok());
    REQUIRE(*return_ok == std::vector<float>{1, 2, 3 , 4});

    auto return_fail = may_fail(true);
    REQUIRE(return_fail.what() == "failed");
    REQUIRE(!return_fail.is_ok());
}