#ifndef HILBERT_TRANSFORM_H
#define HILBERT_TRANSFORM_H

#include <memory>

#include "pocketfft.h"

class HilbertTransform {
	std::size_t num_samples{};

	pocketfft::shape_t shape;
	pocketfft::stride_t stride;
	pocketfft::shape_t axes;

	std::vector<std::complex<double> > input;
	std::vector<std::complex<double> > data;
	std::vector<std::complex<double> > output;

public:
	explicit HilbertTransform(std::size_t samples);

	~HilbertTransform();

	void process(const std::vector<double> &source, std::vector<double> &target);

	void resize(std::size_t samples);

private:
	static void realToComplex(const double *source, std::complex<double> *target, std::size_t num_samples);

	static void complexToReal(const std::complex<double> *source, double *target, std::size_t num_samples);

	static double absoluteSquare(std::complex<double> value);
};

#endif //HILBERT_TRANSFORM_H
