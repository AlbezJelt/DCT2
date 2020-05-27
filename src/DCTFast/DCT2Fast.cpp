#include "include/DCTFast/DCT2Fast.h"
#include "include/DCTFast/FastDctFft.h"
#include "include/DCTFast/FastDctLee.h"


Eigen::MatrixXd DCT2Fast::DCT2Fast(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // DCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctFft::transform(row);
        out.row(i) = row;
    }

    // DCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctFft::transform(col);
        out.col(i) = col;
    }
    return out;
}

Eigen::MatrixXd DCT2Fast::DCT2Fast_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// DCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctFft::transform(row);
        out.row(i) = row;
    }

// DCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctFft::transform(col);
        out.col(i) = col;
    }

    return out;
}

Eigen::MatrixXd DCT2Fast::DCT2Lee(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // DCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctLee::transform(row);
        out.row(i) = row;
    }

    // DCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctLee::transform(col);
        out.col(i) = col;
    }
    return out;
}

Eigen::MatrixXd DCT2Fast::DCT2Lee_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// DCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctLee::transform(row);
        out.row(i) = row;
    }

// DCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctLee::transform(col);
        out.col(i) = col;
    }

    return out;
}


Eigen::MatrixXd DCT2Fast::IDCT2Fast(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // DCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctFft::inverseTransform(row);
        out.row(i) = row;
    }

    // DCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctFft::inverseTransform(col);
        out.col(i) = col;
    }
    return out;
}

Eigen::MatrixXd DCT2Fast::IDCT2Fast_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// DCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctFft::inverseTransform(row);
        out.row(i) = row;
    }

// DCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctFft::inverseTransform(col);
        out.col(i) = col;
    }

    return out;
}

Eigen::MatrixXd DCT2Fast::IDCT2Lee(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

    // DCT su righe
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctLee::inverseTransform(row);
        out.row(i) = row;
    }

    // DCT su colonne
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctLee::inverseTransform(col);
        out.col(i) = col;
    }
    return out;
}

Eigen::MatrixXd DCT2Fast::IDCT2Lee_mt(Eigen::MatrixXd &_m)
{
    Eigen::MatrixXd out = _m;

// DCT su righe
#pragma omp parallel for
    for (int i = 0; i < out.rows(); i++)
    {
        Eigen::VectorXd row = out.row(i);
        FastDctLee::inverseTransform(row);
        out.row(i) = row;
    }

// DCT su colonne
#pragma omp parallel for
    for (int i = 0; i < out.cols(); i++)
    {
        Eigen::VectorXd col = out.col(i);
        FastDctLee::inverseTransform(col);
        out.col(i) = col;
    }

    return out;
}
