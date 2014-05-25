PROJECT_DIR=../diploma

TEST_INCLUDE_DIR=/usr/local/include

TEST_LIB_DIR=/usr/local/lib
TEST_LIB=gtest

#PROJECT_SOURCES=matrix.cpp matrix.cpp vector.cpp
PROJECT_SOURCES=

all:
	g++ --std=c++11 -pthread main.cpp matrix_test.cpp -o matrix_test.out -I$(PROJECT_DIR) $(PROJECT_SOURCES) -I$(TEST_INCLUDE_DIR)/include  -L$(TEST_LIB_DIR) -l$(TEST_LIB)
