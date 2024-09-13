#ifndef HRI_PHYSIO_STREAMER_INTERFACE_H
#define HRI_PHYSIO_STREAMER_INTERFACE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../utilities/enums.h"
#include "../utilities/helpers.h"

/**
 * @class StreamerInterface
 * @brief Base class for streaming data with various configurations.
 */
class StreamerInterface
{
protected:
    /**
     * Variable tag for the streamer.
     */
    VarTag var;

    /**
     * Mode tag for the streamer.
     */
    ModeTag mode;

    /**
     * Name of the streamer.
     */
    std::string name;

    /**
     * Data type of the stream.
     */
    std::string dtype;

    /**
     * Length of each frame in the stream.
     */
    std::size_t frame_length;

    /**
     * Number of channels in the stream.
     */
    std::size_t num_channels;

    /**
     * Sampling rate of the stream.
     */
    std::size_t sampling_rate;

    /**
     * Sets the mode of the streamer.
     * @param new_mode New mode to be set.
     */
    void set_mode(ModeTag new_mode);

public:
    /**
     * Constructor to initialize the StreamerInterface.
     */
    StreamerInterface();

    /**
     * Sets the name of the streamer.
     * @param new_name New name to be set.
     */
    void set_name(std::string new_name);

    /**
     * Sets the data type of the stream.
     * @param dtype Data type to be set.
     */
    void set_data_type(std::string dtype);

    /**
     * Sets the number of channels in the stream.
     * @param new_num_channels Number of channels to be set.
     */
    void set_num_channels(std::size_t new_num_channels);
};

#endif // HRI_PHYSIO_STREAMER_INTERFACE_H
