CXX = clang++
CXX_FLAGS = -g -std=c++1z -Wall -Wextra -pedantic

all: descentAlgorithmExecute

descentAlgorithmExecute: descentAlgorithmExecute.o descentAlgorithm.o 
	$(CXX) -o descentAlgorithmExecute descentAlgorithmExecute.o descentAlgorithm.o

descentAlgorithm.o: descentAlgorithm.cpp descentAlgorithm.hpp 
	$(CXX) $(CXX_FLAGS) -c descentAlgorithm.cpp

descentAlgorithmExecute.o: descentAlgorithmExecute.cpp descentAlgorithm.hpp 
	$(CXX) $(CXX_FLAGS) -c descentAlgorithmExecute.cpp

clean:
	rm -rf descentAlgorithmExecute *.o 