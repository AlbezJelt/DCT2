#include "DCT2.h"
#include "include/Eigen/Core"

#include <iostream>
#include <chrono>
#include <random>

void test_project_matrix()
{
  Eigen::MatrixXd test(8, 8);
  test << 231, 247, 234, 193, 11, 97, 193, 87,
      32, 40, 202, 190, 24, 195, 70, 149,
      233, 248, 245, 100, 210, 203, 174, 57,
      161, 245, 167, 167, 177, 47, 167, 192,
      24, 124, 9, 43, 81, 125, 41, 65,
      71, 204, 217, 180, 243, 114, 30, 129,
      140, 36, 239, 8, 8, 165, 127, 178,
      245, 107, 173, 70, 112, 181, 245, 228;

  test = test.transpose().eval();

  Eigen::MatrixXd test_after_DCT2 = DCT2::DCT2_mt(test);
  Eigen::MatrixXd testDCT2_after_IDCT2 = DCT2::IDCT2_mt(test_after_DCT2);

  std::cout << test << std::endl
            << std::endl;
  std::cout << test_after_DCT2 << std::endl
            << std::endl;
  std::cout << testDCT2_after_IDCT2 << std::endl
            << std::endl;
}

int main()
{
  //std::cout << "Optimal parallel size: " << DCT2::findParallelSize() << std::endl << std::endl;
  test_project_matrix();
  return 0;
}

