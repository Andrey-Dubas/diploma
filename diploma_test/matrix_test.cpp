#include "matrix_test.h"

using namespace Util;

TEST_F(CTestMatrix, division_4_ok){

	Matrix<float, 3, 3> m =	   {40., 50., 8.,
								6., 52., 8.,
								7., 13., 19.};
	Matrix<float, 3, 3> one(Matrix<float, 3, 3>::IDENTITY);
	auto reverse = one / m;
	auto identity = reverse * m;
	EXPECT_EQ(one, identity);
}


TEST_F(CTestMatrix, division_2_ok){
	Matrix<float, 2, 2> m = {1, 2, 3, 4};
	Matrix<float, 2, 2> one = {1, 0, 0, 1};
	auto m1 = one / m;
	EXPECT_EQ( m * m1, one);
}


TEST_F(CTestMatrix, div_3_zeroDeterminant){
	Matrix<float, 3, 3> m = {0, 0, 0,
				0, 0, 0,
				0, 0, 0};

	Matrix<float, 3, 3> m1 = { 0, 0, 0, 
		0, 0, 0, 
		0, 0, 0};
	
	EXPECT_ANY_THROW({
		auto m2 = m1 / m;
	});
}

TEST_F(CTestMatrix, minor_2_validData_ok){
	Matrix<int, 2, 2> m = {1, 2, 3, 4};
	int det = m._minor(0, 1).determinant();
	EXPECT_EQ(3, det);
}

TEST_F(CTestMatrix, minor_3_validData_ok){

}

TEST_F(CTestMatrix, determinant_2_valid_data_ok)
{
    Matrix<float, 2, 2> m = {1, 2, 3, 4};
    float res = m.determinant();
    EXPECT_EQ(-2.0f, res);
}

TEST_F(CTestMatrix, determinant_3_valid_data_ok)
{
    Matrix<float, 3, 3> m = { 
				  4 , -34, 56, 
	    		  -4 ,  3 , 9,
    			  -24, -14, 4};
    float res = m.determinant();
    ASSERT_EQ(res, 14520);
}

TEST_F(CTestMatrix,  multiply_3_validData_ok)
{
		Matrix<int, 3, 3> m1 = { 
					4, 65, 3 ,
					56 , 10, 45,
					34 , 3 , 7};
		Matrix<int, 3, 3> m2 = {
					2  , 34, 7,
					3  , 5 , 3,
					1  , 4 , 3};
		Matrix<int, 3, 3> m3 = m1 * m2;

		Matrix<int, 3, 3> result = {
					206, 473 , 232,
					187, 2134, 557,
					84 , 1199, 268};
		Matrix<int, 3, 3> m4(m3);
		ASSERT_EQ(m4, result);
}

TEST_F(CTestMatrix, multiplyMixed_ok)
{
	Util::Matrix<float, 1, 2> m1 = {1, 3};
	Util::Matrix<float, 3, 1> m2 = {1, 2, 3};
	Util::Matrix<float, 2, 3> res = m1 * m2;

	Util::Matrix<float, 2, 3> compareTo= {1, 2, 3, 3, 6, 9};
	ASSERT_EQ(compareTo, res);

	Util::Matrix<float, 2, 4> m3 = {5, 3, 7, 4, 5, 8, 3, 9 };
	Util::Matrix<float, 3, 2> m4 = {12, 4, 2, 7, 5, 8};
	Util::Matrix<float, 4, 3> compr = { 81, 35, 34,
										112, 48, 46,
										116, 60, 74,
										99, 57, 78};
	auto ret = m3 * m4;
	ASSERT_EQ(compr, ret);
	
}

TEST_F(CTestMatrix, elemAccess_3_outOfArray_exception){
	Matrix<int, 3, 3> m(Matrix<int, 3, 3>::ZERO);
	
	EXPECT_ANY_THROW({
		m[3][0];	
	});
}

