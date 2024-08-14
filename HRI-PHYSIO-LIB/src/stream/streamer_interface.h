#ifndef HRI_PHYSIO_STREAMER_INTERFACE_H
#define HRI_PHYSIO_STREAMER_INTERFACE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../utilities/enums.h"
#include "../utilities/helpers.h"

class StreamerInterface {
private:
    std::string name;
    std::string dtype;
    std::size_t frame_length;
    std::size_t num_channels;
    std::size_t sampling_rate;

    VarTag var;
    ModeTag mode;

public:
    StreamerInterface();

    // Getters
    [[nodiscard]] const std::string &get_name() const;

    [[nodiscard]] const std::string &get_dtype() const;

    [[nodiscard]] std::size_t get_frame_length() const;

    [[nodiscard]] std::size_t get_num_channels() const;

    [[nodiscard]] std::size_t get_sampling_rate() const;

    [[nodiscard]] VarTag get_variable_tag() const;

    [[nodiscard]] ModeTag get_mode() const;

    // Setters
    void set_name(const std::string &new_name);

    void set_dtype(const std::string &new_dtype);

    void set_frame_length(size_t new_frame_length);

    void set_num_channels(size_t new_num_channels);

    void set_sampling_rate(size_t new_sampling_rate);

    void set_mode(ModeTag new_mode);

    // Set variable tag from dtype
    void set_data_type(std::string dtype_tag);
};

#endif //HRI_PHYSIO_STREAMER_INTERFACE_H
