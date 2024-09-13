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
#ifndef HRI_PHYSIO_ENUMS_H
#define HRI_PHYSIO_ENUMS_H

enum ModeTag
{
    NOT_SET,
    SENDER,
    RECEIVER
};

enum VarTag
{
    CHAR,
    INT16,
    INT32,
    INT64,
    LONG_LONG,
    FLOAT,
    DOUBLE,
    STRING
};

#endif // HRI_PHYSIO_ENUMS_H
