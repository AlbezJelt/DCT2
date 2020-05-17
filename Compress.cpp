#include "include/Eigen/Core"
#include "Compress.h"

#include <vector>

/**
    @brief Compressing function

    Compress a bitmap image using DCT2 with blocking and frequency cutting

    @param Eigen::MatrixXi &_m A valid Eigen::MatrixXi obtained from a bitmap image
    @param double f Block size to apply DCT2
    @param double d Frequency cut threshold

    @return Eigen::MatrixXi compressed
*/
Eigen::MatrixXi Compress::DCTCompress(const Eigen::MatrixXi &_m, const int f, const int d)
{
    Eigen::MatrixXd out = _m.cast<double>();
    out.conservativeResize(f*trunc(out.rows()/f), f*trunc(out.cols()/f));

    //Phase 1: calculate indices for blocking
    std::vector<std::pair<int, int>> indices;
    for(int i = 0; i<out.cols(); i+=f)
    {
        for(int k = 0; k<out.rows(); k+=f)
            indices.push_back(std::pair<int,int>(i, k));
    }

    //Phase 2: apply DCT2 on all calculated blocks
    std::vector<std::pair<int, int>>::iterator iter;
#pragma omp parallel for
    for (iter = indices.begin(); iter < indices.end(); iter++)
    {
        Eigen::MatrixXd block = out.block(iter->first, iter->second, f, f);

        //DCT2

        //Taglio le frequenze

        // IDCT2

        //Troncare double in int

        out.block(iter->first, iter->second, f, f) = block;
    }
    return out.cast<int>().eval();
}
