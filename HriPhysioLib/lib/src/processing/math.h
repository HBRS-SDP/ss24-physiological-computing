#ifndef HRI_PHYSIO_PROCESSING_MATH_H
#define HRI_PHYSIO_PROCESSING_MATH_H

#include <numbers>
#include <cmath>

inline double example() {
    double pi = std::numbers::pi; // High precision pi
    double sqrt2 = std::numbers::sqrt2; // High precision sqrt(2.0)

    return pi + sqrt2;
}

template<typename T>

T mean(const std::vector<T> &vec) {
    T ret = T(); // Ensures that ret is initialized to 0 or the default value for type T
    if (vec.empty()) {
        return ret;
    }

    for (size_t idx = 0; idx < vec.size(); ++idx) {
        ret += vec[idx];
    }

    ret /= static_cast<T>(vec.size()); // Use static_cast instead of C-style cast

    return ret;
}

template<typename T>

T stddev(const std::vector<T> &vec) {
    T ret = T(); // Ensures ret is initialized to 0 or the default value for type T
    if (vec.empty()) {
        return ret;
    }

    T mu = mean(vec);
    for (size_t idx = 0; idx < vec.size(); ++idx) {
        ret += std::pow(vec[idx] - mu, 2);
    }

    ret /= static_cast<T>(vec.size()); // Use static_cast instead of C-style cast
    ret = std::sqrt(ret); // Use std::sqrt instead of sqrt2

    return ret;
}

#endif /* HRI_PHYSIO_PROCESSING_MATH_H */
