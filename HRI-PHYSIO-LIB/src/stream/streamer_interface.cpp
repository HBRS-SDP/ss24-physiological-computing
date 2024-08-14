#include "streamer_interface.h"

StreamerInterface::StreamerInterface() : frame_length(0), num_channels(0), sampling_rate(0),
                                         var(VarTag::CHAR),
                                         mode(ModeTag::NOT_SET) {}

const std::string &StreamerInterface::get_name() const {
    return name;
}

const std::string &StreamerInterface::get_dtype() const {
    return dtype;
}

size_t StreamerInterface::get_frame_length() const {
    return frame_length;
}

size_t StreamerInterface::get_num_channels() const {
    return num_channels;
}

size_t StreamerInterface::get_sampling_rate() const {
    return sampling_rate;
}

VarTag StreamerInterface::get_variable_tag() const {
    return var;
}

ModeTag StreamerInterface::get_mode() const {
    return mode;
}

void StreamerInterface::set_name(const std::string &new_name) {
    StreamerInterface::name = new_name;
}

void StreamerInterface::set_dtype(const std::string &new_dtype) {
    StreamerInterface::dtype = new_dtype;
}

void StreamerInterface::set_frame_length(size_t new_frame_length) {
    frame_length = new_frame_length;
}

void StreamerInterface::set_num_channels(size_t new_num_channels) {
    num_channels = new_num_channels;
}

void StreamerInterface::set_sampling_rate(size_t new_sampling_rate) {
    sampling_rate = new_sampling_rate;
}

void StreamerInterface::set_mode(ModeTag new_mode) {
    mode = new_mode;
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
