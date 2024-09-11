#include "hilbert_transform.h"

HilbertTransform::HilbertTransform(std::size_t samples) {
    this->resize(samples);
}

HilbertTransform::~HilbertTransform() = default;

void HilbertTransform::process(const std::vector<double> &source, std::vector<double> &target) {
    if (source.size() != this->num_samples) {
        this->resize(source.size());
    }

    if (source.size() != target.size()) {
        target.resize(this->num_samples);
    }

    realToComplex(source.data(), this->input.data(), this->num_samples);

    // Perform forward FFT
    pocketfft::c2c(this->shape,
                   this->stride,
                   this->stride,
                   this->axes, pocketfft::FORWARD,
                   this->input.data(),
                   this->data.data(),
                   1.0
    );

    // Apply Hilbert transform in frequency domain
    std::size_t half_samples = this->num_samples / 2;
    this->data[0] = {0, 0};  // DC component
    for (std::size_t idx = 1; idx < half_samples; ++idx) {
        this->data[idx] *= 2.0;
    }
    if (this->num_samples % 2 == 0) {
        this->data[half_samples] = {0, 0};  // Nyquist frequency for even-length signals
    }
    for (std::size_t idx = half_samples + 1; idx < num_samples; ++idx) {
        this->data[idx] = {0, 0};
    }

    // Perform inverse FFT
    pocketfft::c2c(
        shape,
        stride,
        stride,
        axes,
        pocketfft::BACKWARD,
        data.data(),
        output.data(),
        1.0 / num_samples  // Normalization factor for inverse FFT
    );

    // Extract imaginary part (Hilbert transform)
    for (std::size_t idx = 0; idx < num_samples; ++idx) {
        target[idx] = output[idx].imag();
    }
}

void HilbertTransform::resize(const std::size_t samples) {
    this->num_samples = samples;

    this->shape = pocketfft::shape_t{this->num_samples};
    this->stride = pocketfft::stride_t(shape.size());

    std::size_t temp = sizeof(std::complex<double>);
    for (std::vector<std::size_t>::size_type idx = this->shape.size(); idx-- > 0;) {
        if (temp > static_cast<std::size_t>(std::numeric_limits<long>::max())) {
            throw std::overflow_error("temp exceeds range of long");
        }
        this->stride[idx] = static_cast<long>(temp);
        temp *= this->shape[idx];
    }

    this->axes.clear();
    for (std::size_t idx = 0; idx < this->shape.size(); ++idx) {
        this->axes.push_back(idx);
    }

    this->input.resize(this->num_samples);
    this->data.resize(this->num_samples);
    this->output.resize(this->num_samples);
}

void HilbertTransform::realToComplex(const double *source, std::complex<double> *target,
                                     const std::size_t num_samples) {
    for (std::size_t idx = 0; idx < num_samples; ++idx) {
        target[idx] = source[idx];
    }
}

void HilbertTransform::complexToReal(const std::complex<double> *source, double *target,
                                     const std::size_t num_samples) {
    for (std::size_t idx = 0; idx < num_samples; ++idx) {
        target[idx] = absoluteSquare(source[idx]);
    }
}

double HilbertTransform::absoluteSquare(const std::complex<double> value) {
    return sqrt(value.real() * value.real() + value.imag() * value.imag());
}
