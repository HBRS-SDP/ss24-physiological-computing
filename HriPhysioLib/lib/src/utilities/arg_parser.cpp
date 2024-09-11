#include "arg_parser.h"

ArgParser::ArgParser(const int &argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        this->tokens.emplace_back(argv[i]);
    }
}

std::string ArgParser::get_cmd_option(const std::string &option) const {
    if (auto itr = std::ranges::find(this->tokens, option); itr != this->tokens.end() && ++itr != this->tokens.end()) {
        return *itr;
    }

    return "";
}
