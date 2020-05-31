#ifndef COMPRESS_H
#define COMPRESS_H

#include "include/Eigen/Core"

namespace Compress
{
enum DCTFunction : int
{
    Naive_custom = 1,
    Fast_Lee = 2,
    Fast_Fft = 3
};
    Eigen::MatrixXi DCTCompress(const Eigen::MatrixXi &_m, const int f, const int d, DCTFunction _funct);
}

#endif // COMPRESS_H
