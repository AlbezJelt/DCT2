#ifndef DCT2FAST_H
#define DCT2FAST_H

#include "include/Eigen/Core"

namespace DCT2Fast {

Eigen::MatrixXd DCT2Lee(Eigen::MatrixXd &_m);
Eigen::MatrixXd DCT2Lee_mt(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2Lee(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2Lee_mt(Eigen::MatrixXd &_m);


Eigen::MatrixXd DCT2Fast(Eigen::MatrixXd &_m);
Eigen::MatrixXd DCT2Fast_mt(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2Fast(Eigen::MatrixXd &_m);
Eigen::MatrixXd IDCT2Fast_mt(Eigen::MatrixXd &_m);

}

#endif // DCT2FAST_H
