#include <iostream>
#include <string>
#include <functional>

int main() {
    std::hash<int> int_hash;
    std::hash<std::string> string_hash;

    int number = 42;
    std::string text = "hello";

    std::cout << "Hash of number: " << int_hash(number) << std::endl;
    std::cout << "Hash of text: " << string_hash(text) << std::endl;

    return 0;
}