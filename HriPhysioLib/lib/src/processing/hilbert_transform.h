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

#ifndef HILBERT_TRANSFORM_H
#define HILBERT_TRANSFORM_H

#include <memory>

#include "pocketfft.h"

class HilbertTransform
{
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

	std::vector<std::complex<double>> input;
	std::vector<std::complex<double>> data;
	std::vector<std::complex<double>> output;

public:
	/* ============================================================================
	**  Main Constructor.
	** ============================================================================ */
	explicit HilbertTransform(std::size_t samples);

	/* ===========================================================================
	**  Destructor.
	** =========================================================================== */
	~HilbertTransform();

	/* ===========================================================================
	**  Process.
	** =========================================================================== */
	void process(const std::vector<double> &source, std::vector<double> &target);

	/* ===========================================================================
	**  Resize.
	** =========================================================================== */
	void resize(std::size_t samples);

private:
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
#endif // HILBERT_TRANSFORM_H
