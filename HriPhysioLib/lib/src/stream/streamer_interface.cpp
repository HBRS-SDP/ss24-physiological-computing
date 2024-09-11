#include "streamer_interface.h"

#include <unordered_map>

#include "../utilities/helpers.h"

StreamerInterface::StreamerInterface() : var(CHAR), mode(NOT_SET), frame_length(0),
                                         num_channels(0),
                                         sampling_rate(0) {
}

void StreamerInterface::set_mode(const ModeTag new_mode) {
    mode = new_mode;
}

void StreamerInterface::set_name(const std::string &new_name) {
    this->name = new_name;
}

void StreamerInterface::set_data_type(std::string dtype) {
    dtype = to_uppercase(dtype);

    static const std::unordered_map<std::string, VarTag> string_to_var_tag = {
        {"INT8", CHAR},
        {"CHAR", CHAR},
        {"INT16", INT16},
        {"INT32", INT32},
        {"INT64", INT64},
        {"FLOAT", FLOAT},
        {"FLOAT32", FLOAT},
        {"DOUBLE", DOUBLE},
        {"DOUBLE64", DOUBLE},
        {"STRING", STRING},
    };

    if (const auto candidate = string_to_var_tag.find(dtype); candidate != string_to_var_tag.end()) {
        this->var = candidate->second;
    }
}

void StreamerInterface::set_num_channels(std::size_t new_num_channels) {
    this->num_channels = new_num_channels;
}
