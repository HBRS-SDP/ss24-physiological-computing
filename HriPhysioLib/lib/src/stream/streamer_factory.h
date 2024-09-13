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
#ifndef HRI_PHYSIO_STREAMER_FACTORY_H
#define HRI_PHYSIO_STREAMER_FACTORY_H

#include <iostream>
#include "streamer_interface.h"
#include "lsl_streamer.h"
#include "csv_streamer.h"
#include "../utilities/helpers.h"

/**
 * @class StreamerFactory
 * @brief Factory class for creating different types of streamers.
 */
class StreamerFactory
{
public:
    /**
     * Creates a streamer based on the specified type.
     * @param streamer_type Type of the streamer to create.
     * @return Pointer to the created StreamerInterface object.
     */
    StreamerInterface *get_streamer(std::string streamer_type);
};

#endif // HRI_PHYSIO_STREAMER_FACTORY_H
