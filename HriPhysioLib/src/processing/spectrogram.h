//
// Created by trushar on 27.08.19.
//


#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H


#include "pocketfft.h"


class Spectrogram {
private:
    /* ============================================================================
    **  Variables received from the constructor.
    ** ============================================================================ */
    std::size_t num_samples{};


    /* ============================================================================
    **  PocketFFT variables.
    ** ============================================================================ */
    pocketfft::shape_t shape;
    pocketfft::stride_t stride;
    pocketfft::shape_t axes;

    std::vector<std::complex<double> > input;
    std::vector<std::complex<double> > data;
    std::vector<std::complex<double> > output;

public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    explicit Spectrogram(std::size_t samples);


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~Spectrogram();


    /* ===========================================================================
    **  Process.
    ** =========================================================================== */
    void process(const std::vector<double> &source, std::vector<std::vector<double> > &target, double sample_rate,
                 double stride_ms = 20.0, double window_ms = 20.0);


    /* ===========================================================================
    **  Resize.
    ** =========================================================================== */
    void resize(std::size_t samples);

private:
    /* ===========================================================================
    **  Hamming Window.
    ** =========================================================================== */
    static auto hammingWindow(std::vector<double> &buffer, std::size_t length) -> void;


    /* ===========================================================================
    **  Resize Matrix.
    ** =========================================================================== */
    static void resizeMatrix(std::vector<std::vector<double> > &mat, std::size_t nrows, std::size_t ncols);


    /* ===========================================================================
    **  Real to Complex.
    ** =========================================================================== */
    static void realToComplex(const double *source, std::complex<double> *target, std::size_t num_samples);


    /* ===========================================================================
    **  Complex to Real.
    ** =========================================================================== */
    static void complexToReal(const std::complex<double> *source, double *target, std::size_t num_samples);


    /* ===========================================================================
    **  Absolute Square.
    ** =========================================================================== */
    static double absoluteSquare(std::complex<double> value);
};
#endif //SPECTROGRAM_H
