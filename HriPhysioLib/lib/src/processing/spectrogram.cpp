#include "iostream"
#include "spectrogram.h"

Spectrogram::Spectrogram(std::size_t samples)
{
    resize(samples);
}

Spectrogram::~Spectrogram() = default;

void Spectrogram::resize(std::size_t samples)
{
    num_samples = samples;
    input.resize(samples);  // Resize the input vector
    data.resize(samples);   // Resize the data vector
    output.resize(samples); // Resize the output vector (if used)
}

void Spectrogram::hammingWindow(std::vector<double> &buffer, std::size_t length)
{
    buffer.resize(length);
    for (std::size_t i = 0; i < length; ++i)
    {
        buffer[i] = 0.54 - 0.46 * std::cos(2.0 * M_PI * static_cast<double>(i) / static_cast<double>(length - 1));
    }
}

void Spectrogram::resizeMatrix(std::vector<std::vector<double>> &mat, std::size_t nrows, std::size_t ncols)
{
    mat.resize(nrows);
    for (auto &row : mat)
    {
        row.resize(ncols);
    }
}

void Spectrogram::realToComplex(const double *source, std::complex<double> *target, std::size_t num_samples)
{
    for (std::size_t i = 0; i < num_samples; ++i)
    {
        target[i] = std::complex<double>(source[i], 0.0);
    }
}

void Spectrogram::complexToReal(const std::complex<double> *source, double *target, std::size_t num_samples)
{
    for (std::size_t i = 0; i < num_samples; ++i)
    {
        target[i] = source[i].real();
    }
}

double Spectrogram::absoluteSquare(const std::complex<double> value)
{
    return std::norm(value); // std::norm gives the squared magnitude of a complex number
}

auto Spectrogram::process(const std::vector<double> &source, std::vector<std::vector<double>> &target,
                          const double sample_rate, const double stride_ms, const double window_ms) -> void
{
    const auto stride_size = static_cast<std::size_t>(0.001 * sample_rate * stride_ms);
    const auto window_size = static_cast<std::size_t>(0.001 * sample_rate * window_ms);

    std::cout << "stride: " << stride_size << std::endl
              << "window: " << window_size << std::endl;

    resize(window_size);
    resizeMatrix(target, static_cast<std::size_t>(sample_rate / 2 + 1),
                 static_cast<std::size_t>(window_size / 2 + 1));

    std::vector<double> window;
    hammingWindow(window, window_size);

    std::cout << "Window:\n";
    for (std::size_t i = 0; i < window.size(); ++i)
    {
        if (i)
            std::cout << ",";
        std::cout << window[i] << " ";
    }
    std::cout << std::endl;

    int counter = 0;
    for (std::size_t idx = 0; idx < source.size(); idx += stride_size)
    {
        for (std::size_t i = 0; i < window_size; ++i)
        {
            if (idx + i < source.size())
            {
                input[i] = source[idx + i] * window[i];
            }
            else
            {
                input[i] = 0.0;
            }
        }

        pocketfft::c2c(
            /* shape      =*/shape,
            /* stride_in  =*/stride,
            /* stride_out =*/stride,
            /* axes       =*/axes,
            /* forward    =*/pocketfft::FORWARD,
            /* data_in    =*/input.data(),
            /* data_out   =*/data.data(),
            /* fct        =*/1.0);

        std::cout << "\nOutput:\n";
        for (std::size_t i = 0; i < data.size() / 2 + 1; ++i)
        {
            std::cout << i << ": " << data[i].real() << "+" << data[i].imag() << std::endl;
        }

        std::cout << "Counter:" << ++counter << std::endl;
    }
}
