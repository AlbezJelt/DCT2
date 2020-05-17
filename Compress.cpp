#include "include/Eigen/Core"
#include "Compress.h"
#include "DCT2.h"

#include <iostream>
#include <vector>
#include <cmath>

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
    if(!(d>=0 && d<(2*f-2))) {
        std::cout << "Your input is: f = " << f << ", d = " << d << std::endl;
        std::cout << "d is not correct. It must be d = (2f - 2)" << std::endl
                  << std::endl;
        return _m;
    }

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
//#pragma omp parallel for
    for (iter = indices.begin(); iter < indices.end(); iter++)
    {
        Eigen::MatrixXd block = out.block(iter->first, iter->second, f, f);

        //DCT2
        Eigen::MatrixXd test_after_DCT2 = DCT2::DCT2_mt(block);
        std::cout << "Print of block" << std::endl;
        std::cout << test_after_DCT2 << std::endl
                  << std::endl;

        //Taglio le frequenze
        for(int i = 0; i<test_after_DCT2.cols(); i++)
        {
            for(int j = 0; j<test_after_DCT2.rows(); j++) {
                if(i + j >= d) {
                    test_after_DCT2(i, j) = 0;
                }
            }
        }

        std::cout << "Print of block with frequencesies cut" << std::endl;
        std::cout << test_after_DCT2 << std::endl
                  << std::endl;

        // IDCT2
        Eigen::MatrixXd testDCT2_after_IDCT2 = DCT2::IDCT2_mt(test_after_DCT2);
        std::cout << "Print IDCT2" << std::endl;
        std::cout << testDCT2_after_IDCT2 << std::endl
                  << std::endl;

        //Troncare double in int
        for(int i=0; i<testDCT2_after_IDCT2.cols(); i++){
            for(int j=0; j<testDCT2_after_IDCT2.rows(); j++) {
                testDCT2_after_IDCT2(i,j) = round(testDCT2_after_IDCT2(i,j));
            }
        }
        std::cout << "Print IDCT2 double2int" << std::endl;
        std::cout << testDCT2_after_IDCT2 << std::endl
                  << std::endl;

        out.block(iter->first, iter->second, f, f) = testDCT2_after_IDCT2;
        std::cout << "Print out" << std::endl;
        std::cout << out << std::endl
                  << std::endl;
    }
    return out.cast<int>().eval();
}
