#ifndef HRI_PHYSIO_HELPERS_H
#define HRI_PHYSIO_HELPERS_H

#include <string>
#include <vector>

std::string to_uppercase(std::string &input_string);

std::string to_lowercase(std::string &input_string);

std::vector<std::string> parse_string(const std::string &string);

std::string combine_string(const std::vector<std::string> &source, size_t idx = 0);

std::vector<double> to_vec_double(const std::vector<std::string> &source, size_t idx = 0);

#endif //HRI_PHYSIO_HELPERS_H
