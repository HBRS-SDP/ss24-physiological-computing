//
// Created by Shrikar Nakhye on 18.08.24.
//
#ifndef HRI_PHYSIO_CSV_STREAMER_H
#define HRI_PHYSIO_CSV_STREAMER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

#include "streamer_interface.h"

class CSVStreamer : public StreamerInterface {
private:
    std::ifstream input;
    std::ofstream output;
    std::string system_time;

public:
    CSVStreamer();

    ~CSVStreamer();

    bool open_input_stream();

    bool open_output_stream();

    void publish(const std::vector<VarTag> &buffer, const std::vector<double> *timestamps = nullptr);

    void publish(const std::string &buffer, const double *timestamps = nullptr);

private:
    template<typename T>
    void push_stream(const std::vector<T> &buffer, const std::vector<double> *timestamps);
};

#endif //HRI_PHYSIO_CSV_STREAMER_H