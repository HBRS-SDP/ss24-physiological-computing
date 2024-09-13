/* ================================================================================
 * Copyright: (C) 2020, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 *     Hochschule Bonn-Rhein-Sieg, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 *     Shrikar Nakhye <shrikar.nakhye@smail.inf.h-brs.de>
 * CopyPolicy: Released under the terms of the MIT License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */
#ifndef HRI_PHYSIO_LSL_STREAMER_H
#define HRI_PHYSIO_LSL_STREAMER_H

#include <iostream>
#include <vector>
#include <lsl_cpp.h>
#include "streamer_interface.h"
#include "../utilities/enums.h"

/**
 * @class LSLStreamer
 * @brief Class for streaming data using the Lab Streaming Layer (LSL) protocol.
 */
class LSLStreamer : public StreamerInterface
{
private:
    /**
     * Unique pointer to the LSL stream inlet.
     */
    std::unique_ptr<lsl::stream_inlet> inlet;

    /**
     * Unique pointer to the LSL stream outlet.
     */
    std::unique_ptr<lsl::stream_outlet> outlet;

public:
    /**
     * Constructor to initialize the LSLStreamer.
     */
    LSLStreamer();

    /**
     * Destructor to clean up resources.
     */
    ~LSLStreamer();

    /**
     * Gets the LSL channel format type.
     * @return LSL channel format type.
     */
    lsl::channel_format_t get_lsl_format_type();

    /**
     * Opens the input LSL stream.
     * @return True if the input stream is successfully opened, false otherwise.
     */
    bool open_input_stream();

    /**
     * Opens the output LSL stream.
     * @return True if the output stream is successfully opened, false otherwise.
     */
    bool open_output_stream();

    /**
     * Publishes a buffer of data to the LSL stream.
     * @param buffer Data buffer to be published.
     */
    void publish(const std::vector<VarTag> &buffer);

    /**
     * Receives data from the LSL stream into a buffer.
     * @param buffer Buffer to store the received data.
     * @param timestamps Optional timestamps for the data.
     */
    void receive(std::vector<VarTag> &buffer, std::vector<double> *timestamps = nullptr);

    /**
     * Publishes a string buffer to the LSL stream.
     * @param buffer String buffer to be published.
     */
    void publish(const std::string &buffer);

    /**
     * Receives a string buffer from the LSL stream.
     * @param buffer Buffer to store the received string data.
     * @param timestamps Optional timestamps for the data.
     */
    void receive(std::string &buffer, double *timestamps = nullptr);

private:
    /**
     * Pushes a buffer of data to the LSL stream.
     * @tparam T Type of the data in the buffer.
     * @param buffer Data buffer to be pushed.
     */
    template <typename T>
    void push_stream(const std::vector<T> &buffer);

    /**
     * Pulls data from the LSL stream into a buffer.
     * @tparam T Type of the data in the buffer.
     * @param buffer Buffer to store the pulled data.
     * @param timestamps Optional timestamps for the data.
     */
    template <typename T>
    void pull_stream(std::vector<T> &buffer, std::vector<double> *timestamps);
};

#endif // HRI_PHYSIO_LSL_STREAMER_H
