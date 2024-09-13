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
#ifndef HRI_PHYSIO_CSV_STREAMER_H
#define HRI_PHYSIO_CSV_STREAMER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "streamer_interface.h"

/**
 * @class CSVStreamer
 * @brief Class for streaming data to and from CSV files.
 */
class CSVStreamer : public StreamerInterface
{
private:
    /**
     * Output file stream for writing CSV data.
     */
    std::ofstream output;

    /**
     * System time for timestamping data.
     */
    std::string system_time;

public:
    /**
     * Constructor to initialize the CSVStreamer.
     */
    CSVStreamer();

    /**
     * Destructor to clean up resources.
     */
    ~CSVStreamer();

    /**
     * Input file stream for reading CSV data.
     */
    std::ifstream input;

    /**
     * Opens the input CSV stream.
     * @return True if the input stream is successfully opened, false otherwise.
     */
    bool open_input_stream();

    /**
     * Opens the output CSV stream.
     * @return True if the output stream is successfully opened, false otherwise.
     */
    bool open_output_stream();

    /**
     * Publishes a buffer of data to the CSV stream.
     * @param buffer Data buffer to be published.
     * @param timestamps Optional timestamps for the data.
     */
    void publish(const std::vector<VarTag> &buffer, const std::vector<double> *timestamps = nullptr);

    /**
     * Publishes a string buffer to the CSV stream.
     * @param buffer String buffer to be published.
     * @param timestamps Optional timestamps for the data.
     */
    void publish(const std::string &buffer, const double *timestamps = nullptr);

private:
    /**
     * Pushes a buffer of data to the stream.
     * @tparam T Type of the data in the buffer.
     * @param buffer Data buffer to be pushed.
     * @param timestamps Optional timestamps for the data.
     */
    template <typename T>
    void push_stream(const std::vector<T> &buffer, const std::vector<double> *timestamps);
};

#endif // HRI_PHYSIO_CSV_STREAMER_H
