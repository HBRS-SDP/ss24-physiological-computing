#ifndef HRI_PHYSIO_STREAMER_INTERFACE_H
#define HRI_PHYSIO_STREAMER_INTERFACE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../utilities/enums.h"
#include "../utilities/helpers.h"

class StreamerInterface {
protected:
    VarTag var;
    ModeTag mode;

    std::string name;
    std::string dtype;
    std::size_t frame_length;
    std::size_t num_channels;
    std::size_t sampling_rate;

    void set_mode(ModeTag new_mode);

public:
    StreamerInterface();

    void set_name(std::string new_name);

    void set_data_type(std::string dtype);

    void set_num_channels(std::size_t new_num_channels);
};

#endif //HRI_PHYSIO_STREAMER_INTERFACE_H