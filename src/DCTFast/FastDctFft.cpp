/*
 * Fast discrete cosine transform algorithms (C++)
 * 
 * Copyright (c) 2017 Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/fast-discrete-cosine-transform-algorithms
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

#include <algorithm>
#include <cmath>
#include <cstddef>
#include "include/DCTFast/FastDctFft.h"
#include "include/DCTFast/FftRealPair.h"

using std::size_t;

// DCT type II, unscaled
void FastDctFft::transform(Eigen::VectorXd &vec) {
	size_t len = vec.size();
	size_t halfLen = len / 2;
    Eigen::VectorXd real(len);
	for (size_t i = 0; i < halfLen; i++) {
        real(i) = vec(i * 2);
        real(len - 1 - i) = vec(i * 2 + 1);
	}
	if (len % 2 == 1)
        real(halfLen) = vec(len - 1);
    vec = Eigen::VectorXd::Zero(len);
	Fft::transform(real, vec);
	for (size_t i = 0; i < len; i++) {
		double temp = i * M_PI / (len * 2);
        vec(i) = (real(i) * std::cos(temp) + vec(i) * std::sin(temp)) / (len / 2.0);
    }
}


// DCT type III, unscaled
void FastDctFft::inverseTransform(Eigen::VectorXd &vec) {
	size_t len = vec.size();
	if (len > 0)
        vec(0) /= 2;
    Eigen::VectorXd real(len);
	for (size_t i = 0; i < len; i++) {
		double temp = i * M_PI / (len * 2);
        real(i) = vec(i) * std::cos(temp);
        vec(i) *= -std::sin(temp);
	}
	Fft::transform(real, vec);
	
	size_t halfLen = len / 2;
	for (size_t i = 0; i < halfLen; i++) {
        vec(i * 2 + 0) = real(i);
        vec(i * 2 + 1) = real(len - 1 - i);
	}
	if (len % 2 == 1)
        vec(len - 1) = real(halfLen);
}
