#ifndef COMPRESS_H
#define COMPRESS_H

#include "include/Eigen/Core"

namespace Compress
{
    Eigen::MatrixXi DCTCompress(const Eigen::MatrixXi &_m, const int f, const int d);
}

#endif // COMPRESS_H
