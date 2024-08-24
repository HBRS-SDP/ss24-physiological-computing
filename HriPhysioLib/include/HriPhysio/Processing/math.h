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

#ifndef HRI_PHYSIO_PROCESSING_MATH_H
#define HRI_PHYSIO_PROCESSING_MATH_H

#include <cmath>
#include <memory>
#include <HriPhysio/helpers.h>

namespace hriPhysio {
    namespace Processing {
        
        /* ============================================================================
        **  Mathematical Constants
        ** ============================================================================ */
        const double pi    = 2 * acos(0.0);  // High precision pi
        const double sqrt2 = sqrt(2.0);      // High precision sqrt(2.0)

        /* ============================================================================
        **  Calculate the Mean of a Vector
        ** 
        **  This function calculates the arithmetic mean of the elements in the vector.
        **
        **  @param vec: A vector of type T containing the elements.
        **  @return T: The mean of the vector elements.
        ** ============================================================================ */
       
        template<typename T>
        T mean(const std::vector<T>& vec) {
            T ret = 0; //Initialize sum to 0
            if (vec.empty()) {
                return ret;
            }
            // Sum all elements in the vector
            for (size_t idx = 0; idx < vec.size(); ++idx) {
                ret += vec[idx];
            }
            // Calculate mean by dividing the sum by the number of elements
            ret /= (T) vec.size();
            return ret;
        };

        /* ============================================================================
        **  Calculate the Standard Deviation of a Vector
        **
        **  This function calculates the standard deviation of the elements in the vector.
        **
        **  @param vec: A vector of type T containing the elements.
        **  @return T: The standard deviation of the vector elements.
        ** ============================================================================ */

        template<typename T>
        T stddev(const std::vector<T>& vec) {
            T ret = 0;
            if (vec.empty()) {
                return ret;
            }

            T mu = mean(vec);
            // Compute the sum of squared differences from the mean
            for (size_t idx = 0; idx < vec.size(); ++idx) {
                ret += pow(vec[idx] - mu, 2);
            }

            // Calculate variance by dividing the sum by the number of elements
            ret /= (T) vec.size();
            ret = sqrt2(ret);  // sqrt2 is a constant representing the square root of 2, not to be confused with the square root function.
            return ret;
        };

    } // namespace Processing
} // namespace hriPhysio

#endif /* HRI_PHYSIO_PROCESSING_MATH_H */
