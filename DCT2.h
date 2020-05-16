#ifndef DCT2_H
#define DCT2_H

#include "include/Eigen/Core"

namespace DCT2
{

Eigen::MatrixXd DCT2(Eigen::MatrixXd &_m);
Eigen::MatrixXd DCT2_mt(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2_mt(Eigen::MatrixXd &_m);

Eigen::MatrixXi DCTCompress(Eigen::MatrixXi &_m, double f, double s);

void DCT(Eigen::VectorXd &_v);
void IDCT(Eigen::VectorXd &_v);

int findParallelSize(int nTest = 5, double dist = 1e-3);
}; // namespace DCT2

#endif
