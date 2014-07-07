//#include "../diploma/vector.h"
//#include "../diploma/matrix.h"
//#include "../diploma/SquareMatrix.h"
#include "matrix_test.h"
#include <iostream>
#include <gtest.h>



TEST(FactorialTest, HandlesPositiveInput) {
//	Util::Matrix<int, 1, 1> m;
	EXPECT_EQ(1, 1);
	EXPECT_EQ(2, 1);
}

int main(int argc, char **argv) {
	  ::testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
}

