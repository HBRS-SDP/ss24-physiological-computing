/* ================================================================================
 * Copyright: (C) 2021, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 * 
 * CopyPolicy: Released under the terms of the BSD 3-Clause License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

/* ================================================================================
 * Copyright: (C) 2024, Shrikar Nakhye,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Shrikar Nakhye <shrikar.nakhye@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */
#ifndef HRI_PHYSIO_HELPERS_H
#define HRI_PHYSIO_HELPERS_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/**
 * Converts a string to uppercase.
 * @param input_string The string to convert.
 * @return The uppercase version of the input string.
 */
std::string to_uppercase(std::string &input_string);

/**
 * Converts a string to lowercase.
 * @param input_string The string to convert.
 * @return The lowercase version of the input string.
 */
std::string to_lowercase(std::string &input_string);

/**
 * Parses a string into a vector of substrings based on whitespace.
 * @param string The string to parse.
 * @return A vector of substrings.
 */
std::vector<std::string> parse_string(const std::string &string);

/**
 * Combines a vector of strings into a single string starting from a specified index.
 * @param source The vector of strings to combine.
 * @param idx The starting index.
 * @return The combined string.
 */
std::string combine_string(const std::vector<std::string> &source, size_t idx = 0);

/**
 * Converts a vector of strings to a vector of doubles starting from a specified index.
 * @param source The vector of strings to convert.
 * @param idx The starting index.
 * @return The vector of doubles.
 */
std::vector<double> to_vec_double(const std::vector<std::string> &source, size_t idx = 0);

#endif // HRI_PHYSIO_HELPERS_H
