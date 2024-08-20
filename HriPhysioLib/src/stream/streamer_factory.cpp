#include "streamer_factory.h"

StreamerInterface *StreamerFactory::get_streamer(std::string streamer_type) {
    to_uppercase(streamer_type);
    if (streamer_type.empty()) {
        std::cerr << "[WARNING] StreamerFactory received no type" << std::endl;
        return nullptr;
    }

    if (streamer_type == "LSL") {
        return new LSLStreamer();
    }

    if (streamer_type == "CSV") {
        return new CSVStreamer();
    }

    std::cerr << "[WARNING] StreamerFactory received unknown type: "
              << streamer_type
              << std::endl;
    return nullptr;
}