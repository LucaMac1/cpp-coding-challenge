#include "RomanNumeralsConverter.h"
#include <sstream>
#include <string>
#include <vector>

std::vector<std::pair<int, std::string>> roman_map = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

std::string intToRoman(int number){
    if(number > 0 && number < 4000){
        std::string result;
        for (const auto& [value, symbol] : roman_map) {
            while (number >= value) {
                result += symbol;
                number -= value;
            }
        }
        return result;
    }
    return "Invalid Input";
}