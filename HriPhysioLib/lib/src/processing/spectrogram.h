#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include "pocketfft.h"

/**
 * @class Spectrogram
 * @brief Class for generating spectrograms using PocketFFT.
 */
class Spectrogram
{
private:
	/**
	 * Number of samples received from the constructor.
	 */
	std::size_t num_samples{};

	/**
	 * PocketFFT shape configuration.
	 */
	pocketfft::shape_t shape;

	/**
	 * PocketFFT stride configuration.
	 */
	pocketfft::stride_t stride;

	/**
	 * PocketFFT axes configuration.
	 */
	pocketfft::shape_t axes;

	/**
	 * Input data for FFT.
	 */
	std::vector<std::complex<double>> input;

	/**
	 * Data buffer for FFT processing.
	 */
	std::vector<std::complex<double>> data;

	/**
	 * Output data from FFT.
	 */
	std::vector<std::complex<double>> output;

public:
	/**
	 * Main constructor.
	 * @param samples Number of samples.
	 */
	explicit Spectrogram(std::size_t samples);

	/**
	 * Destructor.
	 */
	~Spectrogram();

	/**
	 * Processes the input data to generate a spectrogram.
	 * @param source Input data.
	 * @param target Output spectrogram.
	 * @param sample_rate Sample rate of the input data.
	 * @param stride_ms Stride in milliseconds.
	 * @param window_ms Window size in milliseconds.
	 */
	void process(const std::vector<double> &source, std::vector<std::vector<double>> &target, double sample_rate,
				 double stride_ms = 20.0, double window_ms = 20.0);

	/**
	 * Resizes the internal buffers.
	 * @param samples New number of samples.
	 */
	void resize(std::size_t samples);

private:
	/**
	 * Applies a Hamming window to the buffer.
	 * @param buffer Buffer to apply the window to.
	 * @param length Length of the buffer.
	 */
	static auto hammingWindow(std::vector<double> &buffer, std::size_t length) -> void;

	/**
	 * Resizes a matrix to the specified dimensions.
	 * @param mat Matrix to resize.
	 * @param nrows Number of rows.
	 * @param ncols Number of columns.
	 */
	static void resizeMatrix(std::vector<std::vector<double>> &mat, std::size_t nrows, std::size_t ncols);

	/**
	 * Converts real data to complex data.
	 * @param source Source real data.
	 * @param target Target complex data.
	 * @param num_samples Number of samples.
	 */
	static void realToComplex(const double *source, std::complex<double> *target, std::size_t num_samples);

	/**
	 * Converts complex data to real data.
	 * @param source Source complex data.
	 * @param target Target real data.
	 * @param num_samples Number of samples.
	 */
	static void complexToReal(const std::complex<double> *source, double *target, std::size_t num_samples);

	/**
	 * Computes the absolute square of a complex number.
	 * @param value Complex number.
	 * @return Absolute square of the complex number.
	 */
	static double absoluteSquare(std::complex<double> value);
};

#endif // SPECTROGRAM_H
