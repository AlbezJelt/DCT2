#include "include/Eigen/Core"
#include "DCT2.h"

#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

Eigen::MatrixXd DCT2::DCT2_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// DCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        DCT(row);
        out.row(i) = row;
    }

// DCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        DCT(col);
        out.col(i) = col;
    }

    return out;
}

Eigen::MatrixXd DCT2::DCT2(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // DCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        DCT(row);
        out.row(i) = row;
    }

    // DCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        DCT(col);
        out.col(i) = col;
    }
    return out;
}

Eigen::MatrixXd DCT2::IDCT2_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// IDCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        IDCT(row);
        out.row(i) = row;
    }

// IDCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        IDCT(col);
        out.col(i) = col;
    }

    return out;
}

Eigen::MatrixXd DCT2::IDCT2(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // IDCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        IDCT(row);
        out.row(i) = row;
    }

    // IDCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        IDCT(col);
        out.col(i) = col;
    }
    return out;
}

void DCT2::DCT(Eigen::VectorXd &_v)
{

    const Eigen::VectorXd _v_copy = _v;
    const int N = _v.size();
    double ak = 1.0 / sqrt(N);
    double ck = 0;

    for (int k = 0; k < N; k++)
    {
        ck = 0;
        for (int i = 0; i < N; i++)
        {
            ck += cos((2.0 * i + 1.0) * k * M_PI / (2.0 * N)) * _v_copy(i);
        }
        _v(k) = ak * ck;
        if (k == 0)
        {
            ak = sqrt(2.0) / sqrt(N);
        }
    }
}

void DCT2::IDCT(Eigen::VectorXd &_c)
{
    const Eigen::VectorXd _c_copy = _c;
    const int N = _c.size();
    double ak = 0;
    double vi = 0;

    for (int i = 0; i < N; i++)
    {
        vi = 0;
        ak = 1.0 / sqrt(N);
        for (int k = 0; k < N; k++)
        {
            vi += cos((2.0 * i + 1.0) * k * M_PI / (2.0 * N)) * _c_copy(k) * ak;
            if (k == 0)
            {
                ak = sqrt(2.0) / sqrt(N);
            }
        }
        _c(i) = vi;
    }
}

int DCT2::findParallelSize(int nTest, double dist)
{

    std::chrono::_V2::system_clock::time_point t1;
    std::chrono::_V2::system_clock::time_point t2;
    int64_t duration;
    int64_t duration_parallel;

    double distance = 1;
    int nwhile = 0;
    double mean = 100;
    int check = 0;

    while (check < nTest)
    {
        bool min = true;
        int diag = 2;
        int internal_check = 0;
        while (internal_check < 10)
        {

            std::default_random_engine gen(time(0));
            std::uniform_int_distribution<> dis(0, 255);
            Eigen::MatrixXd test2 = Eigen::MatrixXd::NullaryExpr(diag, diag, [&]() { return dis(gen); });

            t1 = std::chrono::high_resolution_clock::now();
            Eigen::MatrixXd out = DCT2::DCT2(test2);
            Eigen::MatrixXd out_2 = DCT2::IDCT2(out);
            t2 = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

            t1 = std::chrono::high_resolution_clock::now();
            Eigen::MatrixXd outpar = DCT2::DCT2_mt(test2);
            Eigen::MatrixXd outpar_2 = DCT2::IDCT2_mt(outpar);
            t2 = std::chrono::high_resolution_clock::now();
            duration_parallel = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

            if (duration > duration_parallel)
            {
                ++internal_check;
            }
            else
            {
                internal_check = 0;
                ++diag;
            }
        }

        ++nwhile;
        double tmp_mean = mean;
        mean = ((mean * nwhile) + (diag + 1)) / (nwhile + 1);
        if (abs(mean - tmp_mean) < dist)
        {
            ++check;
        }
        else
        {
            check = 0;
        }
    }

    return (int) trunc(mean);
}

Eigen::MatrixXi DCT2::DCTCompress(Eigen::MatrixXi &_m, double f, double s)
{
    Eigen::MatrixXi out;
    return out;
}
