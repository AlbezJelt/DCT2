#include "include/DCT2.h"
#include "include/Eigen/Core"
#include "include/Compress.h"
#include "include/test.h"
#include "include/DCTFast/DCT2Fast.h"

#include <iostream>
#include <chrono>
#include <random>
#include <assert.h>
#include <stdio.h>
#include <fstream>


void test::test_project_matrix()
{
    Eigen::MatrixXd test(8, 8);
    test << 231,32,233,161,24,71,140,245
            ,247,40,248,245,124,204,36,107
            ,234,202,245,167,9,217,239,173
            ,193,190,100,167,43,180,8,70
            ,11,24,210,177,81,243,8,112
            ,97,195,203,47,125,114,165,181
            ,193,70,174,167,41,30,127,245
            ,87,149,57,192,65,129,178,228;

    Eigen::MatrixXd test_after_DCT2 = DCT2::DCT2_mt(test);
    Eigen::MatrixXd testDCT2_after_IDCT2 = DCT2::IDCT2_mt(test_after_DCT2);

    assert(test.isApprox(testDCT2_after_IDCT2));
}

void test::compare_DCT2_algorithms()
{
    double dist = 100;

    std::ofstream outCSV;

    std::string strCol = "DCT2_algorithm,";
    std::string strCustom = "Custom,";
    std::string strFast = "Fast,";
    std::string strLee = "Lee,";
    int round = 5;

    std::mt19937 gen(11764244);
    std::uniform_real_distribution<double> dis(INT_MIN, INT_MAX);

    for(size_t i = 8; i<=4096; i*=2)
    {
        int internal_check = 0;

        if (i==512)
            dist = 500;
        if (i==4096)
            round = 2;

        double meanDurationCustom = 0;
        double meanDurationFast = 0;
        double meanDurationLee = 0;
        int n = 0;

        std::chrono::_V2::steady_clock::time_point start =  std::chrono::_V2::steady_clock::now();

        while(internal_check<round)
        {
            Eigen::MatrixXd test = Eigen::MatrixXd::NullaryExpr(i,i,[&](){return dis(gen);});

            std::chrono::_V2::system_clock::time_point t1;
            std::chrono::_V2::system_clock::time_point t2;

            double durationCustom = 0;
            double durationFast = 0;
            double durationLee = 0;

            n++;

            //DCT2 Custom version
            {
                t1 = std::chrono::high_resolution_clock::now();
                Eigen::MatrixXd test_after_DCT2_custom = DCT2::DCT2_mt(test);
                t2 = std::chrono::high_resolution_clock::now();

                durationCustom = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000;

            }

            //DCT2 Fast version
            {
                t1 = std::chrono::high_resolution_clock::now();
                Eigen::MatrixXd test_after_DCT2_fast = DCT2Fast::DCT2Fast_mt(test);
                t2 = std::chrono::high_resolution_clock::now();

                durationFast = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000;

            }

            //DCT2 Lee version
            {
                try {
                    t1 = std::chrono::high_resolution_clock::now();
                    Eigen::MatrixXd test_after_DCT2_lee = DCT2Fast::DCT2Lee_mt(test);
                    t2 = std::chrono::high_resolution_clock::now();

                    durationLee = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000;

                } catch (const std::exception &e) {}
            }

            double tmp_meanDurationCustom = meanDurationCustom;
            double tmp_meanDurationFast = meanDurationFast;
            double tmp_meanDurationLee = meanDurationLee;

            meanDurationCustom = tmp_meanDurationCustom + ((durationCustom - tmp_meanDurationCustom) / n);
            meanDurationFast = tmp_meanDurationFast + ((durationFast - tmp_meanDurationFast) / n);
            meanDurationLee = tmp_meanDurationLee + ((durationLee - tmp_meanDurationLee) / n);

            if (std::chrono::_V2::steady_clock::now() - start > std::chrono::seconds(3600))
                break;

            if ((abs(meanDurationCustom - tmp_meanDurationCustom) < dist) &
                    (abs(meanDurationFast - tmp_meanDurationFast) < dist) &
                    (abs(meanDurationLee - tmp_meanDurationLee) < dist))
            {
                ++internal_check;
            }
            else
            {
                internal_check = 0;
            }
        } //end While

        strCol = strCol + std::to_string(i) + ",";
        strCustom = strCustom + std::to_string(meanDurationCustom) + ",";
        strFast = strFast + std::to_string(meanDurationFast) + ",";
        strLee = strLee + std::to_string(meanDurationLee) + ",";

        std::cout << i << ":" << n << std::endl;
    } // end For
       
    outCSV.open("Results.csv");
    outCSV << strCol.substr(0, strCol.size() - 1) + '\n';
    outCSV << strCustom.substr(0, strCustom.size() - 1) + '\n';
    outCSV << strFast.substr(0, strFast.size() - 1) + '\n';
    outCSV << strLee.substr(0, strLee.size() - 1) + '\n';

}


