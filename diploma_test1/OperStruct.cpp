#include "OperStruct.h"

#include "../diploma/vector.h"
#include "../diploma/matrix.h"
#include "../diploma/DataOperations.h"

#include <iostream>

using namespace Util;

TEST_F(COperStructTest, addMatrixToVector_validData_ok){

	Vector<int, 2> v = {3, 5};
	Matrix<int, 2, 2> m = {2, 6,
				10, 20};

	Vector<int, 2> v1 = m + v;
	Vector<int, 2> res = { 3 + 2 + 6,
				5 + 10 + 20};
	EXPECT_EQ(res, v1);

}

TEST_F(COperStructTest, multiplyVector_ok){

	Vector<int, 2> v = { 3, 8 };
	Vector<int, 2> v1 = v * 3;
	Vector<int, 2> expect = {9, 24};
	EXPECT_EQ(expect, v1);

}


