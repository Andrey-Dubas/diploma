
TEST_INCLUDE_DIR=/usr/local/include

TEST_LIB_DIR=/usr/local/lib
TEST_LIB=gtest

TEST_SOURCE=main.cpp matrix_test.cpp OperStruct.cpp KalmanTest.cpp 
TEST_OBJ=$(TEST_SOURCE:.cpp=.o)

%.o: %.cpp 
	g++ -std=c++11 -pthread -c $^ -I$(TEST_INCLUDE_DIR) -L$(TEST_LIB_DIR) -l$(TEST_LIB)

all: $(TEST_OBJ) 
	g++ -g -std=c++11 -pthread $(TEST_OBJ) -lm -o tests -I$(TEST_INCLUDE_DIR) -L$(TEST_LIB_DIR) -l$(TEST_LIB)
	./tests

clean:
	rm $(TEST_OBJ)
	rm tests
