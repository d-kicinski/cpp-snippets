#include <catch2/catch.hpp>
#include <codecvt>
#include <cstring>
#include <iostream>
#include <locale>
#include <string>
#include <map>

TEST_CASE("utf string")
{
    std::string str = "Łąka";
    std::cout << "std.length() = " << str.length() << std::endl;
    for (const auto &item : str) {
        std::cout << item << ", ";
    }

    const char text[] = "olé";
    std::cout << "sizeof(char)    : " << sizeof(char) << std::endl;
    std::cout << "text            : " << text << std::endl;
    std::cout << "sizeof(text)    : " << sizeof(text) << std::endl;
    std::cout << "strlen(text)    : " << strlen(text) << std::endl;

    std::cout << "text(ordinals)  :";
    for (size_t i = 0, iMax = strlen(text); i < iMax; ++i) {
        std::cout << " " << static_cast<unsigned int>(static_cast<unsigned char>(text[i]));
    }

    std::cout << "text  :";
    for (size_t i = 0, iMax = strlen(text); i < iMax; ++i) {
        std::cout << " " << static_cast<unsigned char>(text[i]);
    }
}

TEST_CASE("wstring")
{
    std::u32string input = U"Łąka";
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    char32_t letter = input[0];
    std::vector<char32_t> letters;
    std::map<char32_t, int> mapping;

    for (char32_t c : input) {
        std::cout << converter.to_bytes(c) << std::endl;
    }
}