#ifndef HRI_PHYSIO_STREAMER_FACTORY_H
#define HRI_PHYSIO_STREAMER_FACTORY_H

#include <iostream>

#include "streamer_interface.h"

class StreamerFactory {
public:
    static StreamerInterface *get_streamer(std::string streamer_type);
};

#endif //HRI_PHYSIO_STREAMER_FACTORY_H
