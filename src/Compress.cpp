#include "include/Eigen/Core"
#include "include/Compress.h"
#include "include/DCT2.h"
#include "include/DCTFast/DCT2Fast.h"

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
Eigen::MatrixXi Compress::DCTCompress(const Eigen::MatrixXi &_m, const int f, const int d, DCTFunction _funct)
{
    if(!(f<=_m.rows() && f<=_m.cols()))
        throw std::runtime_error(std::string("F must be <=image.width() and image.height()"));

    if (_funct == Fast_Lee && (f <= 0 || (f & (f - 1))) != 0)
        throw std::domain_error("Lee version can be used only on power of 2 value of F");

    Eigen::MatrixXd out = _m.cast<double>();
    out.conservativeResize(f*trunc(out.rows()/f), f*trunc(out.cols()/f));

    //Phase 1: calculate indices for blocking
    std::vector<std::pair<int, int>> indices;
    for(int i = 0; i<out.rows(); i+=f)
    {
        for(int k = 0; k<out.cols(); k+=f)
            indices.push_back(std::pair<int,int>(i, k));
    }

    //Phase 2: apply DCT2 on all calculated blocks
    std::vector<std::pair<int, int>>::iterator iter;

    switch (_funct) {
    case Naive_custom:
#pragma omp parallel for
        for (iter = indices.begin(); iter < indices.end(); iter++)
        {
            Eigen::MatrixXd block = out.block(iter->first, iter->second, f, f);

            //DCT2
            Eigen::MatrixXd block_after_DCT2 = DCT2::DCT2_mt(block);

            //Frequency cut
            for(int i = 0; i<block_after_DCT2.cols(); i++)
            {
                for(int j = 0; j<block_after_DCT2.rows(); j++) {
                    if(i + j >= d) {
                        block_after_DCT2(j, i) = 0;
                    }
                }
            }

            // IDCT2
            Eigen::MatrixXd block_after_IDCT2 = DCT2::IDCT2_mt(block_after_DCT2);

            out.block(iter->first, iter->second, f, f) = block_after_IDCT2;
        }
        break;
    case Fast_Lee:
#pragma omp parallel for
        for (iter = indices.begin(); iter < indices.end(); iter++)
        {
            Eigen::MatrixXd block = out.block(iter->first, iter->second, f, f);

            //DCT2
            Eigen::MatrixXd block_after_DCT2 = DCT2Fast::DCT2Lee_mt(block);

            //Frequency cut
            for(int i = 0; i<block_after_DCT2.cols(); i++)
            {
                for(int j = 0; j<block_after_DCT2.rows(); j++) {
                    if(i + j >= d) {
                        block_after_DCT2(j, i) = 0;
                    }
                }
            }

            // IDCT2
            Eigen::MatrixXd block_after_IDCT2 = DCT2Fast::IDCT2Lee_mt(block_after_DCT2);

            out.block(iter->first, iter->second, f, f) = block_after_IDCT2;
        }
        break;
    case Fast_Fft:
#pragma omp parallel for
        for (iter = indices.begin(); iter < indices.end(); iter++)
        {
            Eigen::MatrixXd block = out.block(iter->first, iter->second, f, f);

            //DCT2
            Eigen::MatrixXd block_after_DCT2 = DCT2Fast::DCT2Fast_mt(block);

            //Frequency cut
            for(int i = 0; i<block_after_DCT2.cols(); i++)
            {
                for(int j = 0; j<block_after_DCT2.rows(); j++) {
                    if(i + j >= d) {
                        block_after_DCT2(j, i) = 0;
                    }
                }
            }

            // IDCT2
            Eigen::MatrixXd block_after_IDCT2 = DCT2Fast::IDCT2Fast_mt(block_after_DCT2);

            out.block(iter->first, iter->second, f, f) = block_after_IDCT2;
        }
        break;
    }

    //Truncate double
    for(int i=0; i<out.cols(); i++){
        for(int j=0; j<out.rows(); j++) {
            out(j,i) = round(out(j,i));
            if (out(j,i) > 255)
            {
                out(j,i) = 255;
            } else if (out(j,i) < 0) {
                out(j,i) = 0;
            }
        }
    }

    return out.cast<int>().eval();
}
