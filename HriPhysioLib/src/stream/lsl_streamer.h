//
// Created by Shrikar Nakhye on 19.08.24.
//
#ifndef HRI_PHYSIO_LSL_STREAMER_H
#define HRI_PHYSIO_LSL_STREAMER_H

#include <iostream>
#include <vector>

#include <lsl_cpp.h>

#include "streamer_interface.h"
#include "../utilities/enums.h"

class LSLStreamer : public StreamerInterface {
private:
    std::unique_ptr<lsl::stream_inlet> inlet;
    std::unique_ptr<lsl::stream_outlet> outlet;

public:
    LSLStreamer();

    ~LSLStreamer();

    lsl::channel_format_t get_lsl_format_type();

    bool open_input_stream();

    bool open_output_stream();

    void publish(const std::vector<VarTag> &buffer);

    void receive(std::vector<VarTag> &buffer, std::vector<double> *timestamps = nullptr);

    void publish(const std::string &buffer);

    void receive(std::string &buffer, double *timestamps = nullptr);


private:
    template<typename T>
    void push_stream(const std::vector<T> &buffer);

    template<typename T>
    void pull_stream(std::vector<T> &buffer, std::vector<double> *timestamps);
};

#endif //HRI_PHYSIO_LSL_STREAMER_H
