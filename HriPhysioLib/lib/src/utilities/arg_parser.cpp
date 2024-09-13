#include "arg_parser.h"

ArgParser::ArgParser(int &argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        this->tokens.emplace_back(argv[i]);
    }
}

std::string ArgParser::get_cmd_option(const std::string &option) const
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end())
    {
        return *itr;
    }

    return "";
}
