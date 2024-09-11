#ifndef HRI_PHYSIO_CSV_STREAMER_H
#define HRI_PHYSIO_CSV_STREAMER_H

#include <fstream>
#include <vector>

#include "streamer_interface.h"

class CSVStreamer : public StreamerInterface {
    std::ofstream output;
    std::string system_time;

public:
    std::ifstream input;

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
