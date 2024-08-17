//
// Created by Shrikar Nakhye on 17.08.24
//
#include "streamer_interface.h"

StreamerInterface::StreamerInterface() : frame_length(0), num_channels(0), sampling_rate(0),
                                         var(VarTag::CHAR),
                                         mode(ModeTag::NOT_SET) {}

void StreamerInterface::set_mode(ModeTag new_mode) {
    mode = new_mode;
}

void StreamerInterface::set_name(std::string new_name) {
    this->name = new_name;
}

void StreamerInterface::set_data_type(std::string dtype_tag) {
    dtype_tag = to_uppercase(dtype_tag);

    static const std::unordered_map<std::string, VarTag> string_to_var_tag = {
        {"INT8",     VarTag::CHAR},
        {"CHAR",     VarTag::CHAR},
        {"INT16",    VarTag::INT16},
        {"INT32",    VarTag::INT32},
        {"INT64",    VarTag::INT64},
        {"FLOAT",    VarTag::FLOAT},
        {"FLOAT32",  VarTag::FLOAT},
        {"DOUBLE",   VarTag::DOUBLE},
        {"DOUBLE64", VarTag::DOUBLE},
        {"STRING",   VarTag::STRING},
};

    auto candidate = string_to_var_tag.find(dtype_tag);
    if (candidate != string_to_var_tag.end()) {
        this->var = candidate->second;
    }
}

void StreamerInterface::set_num_channels(std::size_t new_num_channels) {
    this->num_channels = new_num_channels;
}
