#ifndef HRI_PHYSIO_ARG_PARSER_H
#define HRI_PHYSIO_ARG_PARSER_H

#include <iostream>
#include <vector>
#include <algorithm>

class ArgParser {
public:
    ArgParser(int &argc, char **argv);

    [[nodiscard]] std::string get_cmd_option(const std::string &option) const;

private:
    std::vector<std::string> tokens;
};

#endif //HRI_PHYSIO_ARG_PARSER_H
