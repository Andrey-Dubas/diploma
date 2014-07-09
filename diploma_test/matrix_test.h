#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include "gtest/gtest.h"
#include "../diploma/vector.h"
#include "../diploma/matrix.h"
#include <iostream>

class CTestMatrix: public ::testing::Test {
	
	void minor_2_validData_ok();
	void minor_3_validData_ok();

    void determinant_2_validData_ok();
    void determinant_3_validData_ok();
	// methon undef test _ tested scenario _ expected result
	//
	void multiply_3_validData_ok();

	void elemAccess_3_outOfArray_exception();
	
    void inverse();

    void division_3_ok();
    void division_2_ok();
	
    void div_3_zeroDeterminant();

};





#endif // MATRIX_TEST_H
