/* 
 * Free FFT and convolution (C++)
 * 
 * Copyright (c) 2020 Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/free-small-fft-in-multiple-languages
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include "include/DCTFast/FftRealPair.h"

using std::size_t;
using std::uintmax_t;


// Private function prototypes
static size_t reverseBits(size_t val, int width);


void Fft::transform(Eigen::VectorXd &real, Eigen::VectorXd &imag) {
	size_t n = real.size();
	if (n != imag.size())
		throw std::invalid_argument("Mismatched lengths");
	if (n == 0)
		return;
	else if ((n & (n - 1)) == 0)  // Is power of 2
		transformRadix2(real, imag);
	else  // More complicated algorithm for arbitrary sizes
		transformBluestein(real, imag);
}


void Fft::inverseTransform(Eigen::VectorXd &real, Eigen::VectorXd &imag) {
	transform(imag, real);
}


void Fft::transformRadix2(Eigen::VectorXd &real, Eigen::VectorXd &imag) {
	// Length variables
	size_t n = real.size();
	if (n != imag.size())
		throw std::invalid_argument("Mismatched lengths");
	int levels = 0;  // Compute levels = floor(log2(n))
	for (size_t temp = n; temp > 1U; temp >>= 1)
		levels++;
	if (static_cast<size_t>(1U) << levels != n)
		throw std::domain_error("Length is not a power of 2");
	
	// Trignometric tables
    Eigen::VectorXd cosTable(n / 2);
    Eigen::VectorXd sinTable(n / 2);
	for (size_t i = 0; i < n / 2; i++) {
        cosTable(i) = std::cos(2 * M_PI * i / n);
        sinTable(i) = std::sin(2 * M_PI * i / n);
	}
	
	// Bit-reversed addressing permutation
	for (size_t i = 0; i < n; i++) {
		size_t j = reverseBits(i, levels);
		if (j > i) {
            std::swap(real(i), real(j));
            std::swap(imag(i), imag(j));
		}
	}
	
	// Cooley-Tukey decimation-in-time radix-2 FFT
	for (size_t size = 2; size <= n; size *= 2) {
		size_t halfsize = size / 2;
		size_t tablestep = n / size;
		for (size_t i = 0; i < n; i += size) {
			for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {
				size_t l = j + halfsize;
                double tpre =  real(l) * cosTable(k) + imag(l) * sinTable(k);
                double tpim = -real(l) * sinTable(k) + imag(l) * cosTable(k);
                real(l) = real(j) - tpre;
                imag(l) = imag(j) - tpim;
                real(j) += tpre;
                imag(j) += tpim;
			}
		}
		if (size == n)  // Prevent overflow in 'size *= 2'
			break;
	}
}


void Fft::transformBluestein(Eigen::VectorXd &real, Eigen::VectorXd &imag) {
	// Find a power-of-2 convolution length m such that m >= n * 2 + 1
	size_t n = real.size();
	if (n != imag.size())
		throw std::invalid_argument("Mismatched lengths");
	size_t m = 1;
	while (m / 2 <= n) {
		if (m > SIZE_MAX / 2)
			throw std::length_error("Vector too large");
		m *= 2;
	}
	
	// Trignometric tables
    Eigen::VectorXd cosTable = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd sinTable = Eigen::VectorXd::Zero(n);
	for (size_t i = 0; i < n; i++) {
		uintmax_t temp = static_cast<uintmax_t>(i) * i;
		temp %= static_cast<uintmax_t>(n) * 2;
		double angle = M_PI * temp / n;
        cosTable(i) = std::cos(angle);
        sinTable(i) = std::sin(angle);
	}
	
	// Temporary vectors and preprocessing
    Eigen::VectorXd areal = Eigen::VectorXd::Zero(m);
    Eigen::VectorXd aimag = Eigen::VectorXd::Zero(m);
	for (size_t i = 0; i < n; i++) {
        areal(i) =  real(i) * cosTable(i) + imag(i) * sinTable(i);
        aimag(i) = -real(i) * sinTable(i) + imag(i) * cosTable(i);
	}

    Eigen::VectorXd breal = Eigen::VectorXd::Zero(m);
    Eigen::VectorXd bimag = Eigen::VectorXd::Zero(m);
    breal(0) = cosTable(0);
    bimag(0) = sinTable(0);
	for (size_t i = 1; i < n; i++) {
        breal(i) = breal(m - i) = cosTable(i);
        bimag(i) = bimag(m - i) = sinTable(i);
	}
	
    // Convolution
    Eigen::VectorXd creal = Eigen::VectorXd::Zero(m);
    Eigen::VectorXd cimag = Eigen::VectorXd::Zero(m);
	convolve(areal, aimag, breal, bimag, creal, cimag);
	
	// Postprocessing
	for (size_t i = 0; i < n; i++) {
        real(i) =  creal(i) * cosTable(i) + cimag(i) * sinTable(i);
        imag(i) = -creal(i) * sinTable(i) + cimag(i) * cosTable(i);
	}
}


void Fft::convolve(const Eigen::VectorXd &xvec, const Eigen::VectorXd &yvec, Eigen::VectorXd &outvec) {
	size_t n = xvec.size();
	if (n != yvec.size() || n != outvec.size())
		throw std::invalid_argument("Mismatched lengths");
    Eigen::VectorXd outimag = Eigen::VectorXd::Zero(n);
    convolve(xvec, Eigen::VectorXd(n), yvec, Eigen::VectorXd(n), outvec, outimag);
}


void Fft::convolve(
        const Eigen::VectorXd &xreal, const Eigen::VectorXd &ximag,
        const Eigen::VectorXd &yreal, const Eigen::VectorXd &yimag,
        Eigen::VectorXd &outreal, Eigen::VectorXd &outimag) {
	
	size_t n = xreal.size();
	if (n != ximag.size() || n != yreal.size() || n != yimag.size()
			|| n != outreal.size() || n != outimag.size())
		throw std::invalid_argument("Mismatched lengths");
	
    Eigen::VectorXd xr = xreal;
    Eigen::VectorXd xi = ximag;
    Eigen::VectorXd yr = yreal;
    Eigen::VectorXd yi = yimag;
	transform(xr, xi);
	transform(yr, yi);
	
	for (size_t i = 0; i < n; i++) {
        double temp = xr(i) * yr(i) - xi(i) * yi(i);
        xi(i) = xi(i) * yr(i) + xr(i) * yi(i);
        xr(i) = temp;
	}
	inverseTransform(xr, xi);
	
	for (size_t i = 0; i < n; i++) {  // Scaling (because this FFT implementation omits it)
        outreal(i) = xr(i) / n;
        outimag(i) = xi(i) / n;
	}
}


static size_t reverseBits(size_t val, int width) {
	size_t result = 0;
	for (int i = 0; i < width; i++, val >>= 1)
		result = (result << 1) | (val & 1U);
	return result;
}
