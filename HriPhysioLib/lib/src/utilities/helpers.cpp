#include "helpers.h"

std::string to_uppercase(std::string &input_string)
{
    std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::toupper);
    return input_string;
}

std::string to_lowercase(std::string &input_string)
{
    std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::tolower);
    return input_string;
}

std::vector<std::string> parse_string(const std::string &string)
{
    std::stringstream string_stream(string);
    std::vector<std::string> return_vector;
    std::string current_string;
    while (string_stream >> current_string)
    {
        return_vector.push_back(current_string);
    }

    return return_vector;
}

std::string combine_string(const std::vector<std::string> &source, size_t idx)
{
    std::string return_string;
    while (idx < source.size())
    {
        if (!return_string.empty())
        {
            return_string += " ";
        }

        return_string += source[idx];
        ++idx;
    }

    return return_string;
}

std::vector<double> to_vec_double(const std::vector<std::string> &source, size_t idx)
{
    std::vector<double> return_vector;
    while (idx < source.size())
    {
        return_vector.push_back(std::stod(source[idx]));
        ++idx;
    }

    return return_vector;
}
