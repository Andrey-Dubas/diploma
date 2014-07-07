#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <gtest/gtest.h>
#include "../diploma/matrix.h"

class CTestMatrix: public ::testing::Test 
{
    void determinant_2_validData_ok();
};


using namespace Util;

TEST_F(CTestMatrix, determinant_2_valid_data_ok)
{
Matrix<float, 2, 2> m = {1, 2, 
3, 4};
}

#endif // MATRIX_TEST_H
