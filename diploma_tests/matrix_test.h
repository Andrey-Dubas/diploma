#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include "gtest/gtest.h"
#include "matrix_test.h"
#include "../diploma/matrix.h"
#include <iostream>

#include "gtest/internal/gtest-internal.h"
#include "gtest/internal/gtest-string.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest-message.h"
#include "gtest/gtest-param-test.h"
#include "gtest/gtest-printers.h"
#include "gtest/gtest_prod.h"
#include "gtest/gtest-test-part.h"
#include "gtest/gtest-typed-test.h"

class CTestMatrix: public ::testing::Test {
    void determinant_2_validData_ok();
    void determinant_3_validData_ok();
	// methon undef test _ tested scenario _ expected result
	
    	

    void inverse();

};




//#include <matrix.h>



TEST_F(CTestMatrix, determinant_2_valid_data_ok)
{
	
    Matrix<float, 2> m = {1, 2, 
	    		  3, 4};
    std::cout << m;
    float res = m.determinant();
    EXPECT_EQ(res, -2.0f);
}

TEST_F(CTestMatrix, determinant_3_valid_data_ok)
{
	
    Matrix<float, 3> m = { 4 , -34, 56 
	    		  -4 ,  3 , 9,
    			  -24, -14, 4};
    std::cout << m;
    float res = m.determinant();
    //ASSERT_EQ(res, 14520);
}

#endif // MATRIX_TEST_H
