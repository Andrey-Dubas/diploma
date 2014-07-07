
#ifndef OPER_TEST_H
#define OPER_TEST_H

#include "gtest/gtest.h"


class COperStructTest: public ::testing::Test{
	void addMatrixToVector_validData_ok();
	void multiplyVector_ok();
};

#endif // OPER_TEST_H
