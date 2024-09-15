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
 * Copyright: (C) 2024, Trushar Ghanekar,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Trushar Ghanekar <trushar.ghanekar@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

#ifndef HRI_PHYSIO_PROCESSING_MATH_H
#define HRI_PHYSIO_PROCESSING_MATH_H

#include "../utilities/helpers.h"
#include <numbers> // Requires C++20
#include <cmath>

inline double example()
{
    double pi = std::numbers::pi;       // High precision pi
    double sqrt2 = std::numbers::sqrt2; // High precision sqrt(2.0)

    return pi + sqrt2;
}

template <typename T>
T mean(const std::vector<T> &vec)
{
    T ret = T(); // Ensures that ret is initialized to 0 or the default value for type T
    if (vec.empty())
    {
        return ret;
    }

    for (size_t idx = 0; idx < vec.size(); ++idx)
    {
        ret += vec[idx];
    }

    ret /= static_cast<T>(vec.size()); // Use static_cast instead of C-style cast

    return ret;
}

template <typename T>
T stddev(const std::vector<T> &vec)
{
    T ret = T(); // Ensures ret is initialized to 0 or the default value for type T
    if (vec.empty())
    {
        return ret;
    }

    T mu = mean(vec);
    for (size_t idx = 0; idx < vec.size(); ++idx)
    {
        ret += std::pow(vec[idx] - mu, 2);
    }

    ret /= static_cast<T>(vec.size()); // Use static_cast instead of C-style cast
    ret = std::sqrt(ret);              // Use std::sqrt instead of sqrt2

    return ret;
}

#endif /* HRI_PHYSIO_PROCESSING_MATH_H */
