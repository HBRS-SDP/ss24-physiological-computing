/* ================================================================================
 * Copyright: (C) 2020, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 *     Hochschule Bonn-Rhein-Sieg, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 *     Shrikar Nakhye <shrikar.nakhye@smail.inf.h-brs.de>
 * CopyPolicy: Released under the terms of the MIT License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */
#ifndef HRI_PHYSIO_ARG_PARSER_H
#define HRI_PHYSIO_ARG_PARSER_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @class ArgParser
 * @brief Class for parsing command-line arguments.
 */
class ArgParser
{
public:
    /**
     * Constructor to initialize the ArgParser with command-line arguments.
     * @param argc Argument count.
     * @param argv Argument vector.
     */
    ArgParser(int &argc, char **argv);

    /**
     * Retrieves the value of a specified command-line option.
     * @param option The command-line option to search for.
     * @return The value of the command-line option if found, otherwise an empty string.
     */
    [[nodiscard]] std::string get_cmd_option(const std::string &option) const;

private:
    /**
     * Vector to store the command-line arguments as tokens.
     */
    std::vector<std::string> tokens;
};

#endif // HRI_PHYSIO_ARG_PARSER_H
