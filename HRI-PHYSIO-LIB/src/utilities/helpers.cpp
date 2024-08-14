#include "helpers.h"

std::string to_uppercase(std::string &input_string) {
    std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::toupper);
    return input_string;
}

std::string to_lowercase(std::string &input_string) {
    std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::tolower);
    return input_string;
}