#ifndef HRI_PHYSIO_STREAMER_FACTORY_H
#define HRI_PHYSIO_STREAMER_FACTORY_H

#include <iostream>

#include "streamer_interface.h"
#include "lsl_streamer.h"
#include "csv_streamer.h"
#include "../utilities/helpers.h"

class StreamerFactory {
public:
    StreamerInterface *get_streamer(std::string streamer_type);
};

#endif //HRI_PHYSIO_STREAMER_FACTORY_H