/* ================================================================================
 * Copyright: (C) 2021, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 * 
 * CopyPolicy: Released under the terms of the BSD 3-Clause License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

/* ================================================================================
 * Copyright: (C) 2024, Shrikar Nakhye,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Shrikar Nakhye <shrikar.nakhye@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */
#include "streamer_factory.h"

StreamerInterface *StreamerFactory::get_streamer(std::string streamer_type)
{
    to_uppercase(streamer_type);
    if (streamer_type.empty())
    {
        std::cerr << "[WARNING] StreamerFactory received no type" << std::endl;
        return nullptr;
    }

    if (streamer_type == "LSL")
    {
        return new LSLStreamer();
    }

    if (streamer_type == "CSV")
    {
        return new CSVStreamer();
    }

    std::cerr << "[WARNING] StreamerFactory received unknown type: "
              << streamer_type
              << std::endl;
    return nullptr;
}
