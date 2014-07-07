PROJECT_DIR=../diploma

TEST_INCLUDE_DIR=/usr/local/include

TEST_LIB_DIR=/usr/local/lib
TEST_LIB=gtest

#TESTED_FILES=matrix.cpp vector.cpp main.cpp
TESTED_DIR=../diploma/
#TESTED_FILES_ORIGIN=$(addprefix $(TESTED_DIR), $(TESTED_FILES) )
TEST_SOURCE=matrix_test.cpp main.cpp
#COMPILE_UNITS=$(TESTED_FILES) $(TEST_SOURCE)
#TEST_OBJ=$(COMPILE_UNITS:.cpp=.o)
TEST_OBJ=$(TEST_SOURCE:.cpp=.o)

#%.cpp: $(TESTED_FILES_ORIGIN)
#	cp $(TESTED_FILES_ORIGIN) ./ 

%.o: %.cpp 
	g++ -std=c++11 -pthread -c $^ -I$(PROJECT_DIR) -I$(TEST_INCLUDE_DIR)/include  -L$(TEST_LIB_DIR) -l$(TEST_LIB)

all: $(TEST_OBJ) 
	g++ -g -std=c++11 -pthread $(TEST_OBJ) -lm -o tests -I$(PROJECT_DIR) -I$(TEST_INCLUDE_DIR)/include  -L$(TEST_LIB_DIR) -l$(TEST_LIB)
	./tests

clean:
	rm $(TEST_OBJ)
	rm tests
#	g++ -std=c++11 -pthread main.cpp -I$(PROJECT_DIR) $(PROJECT_SOURCES) -I$(TEST_INCLUDE_DIR)/include  -L$(TEST_LIB_DIR) -l$(TEST_LIB)
