CXX = g++
FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -c Channel.cpp
	$(CXX) $(FLAGS) -c Soften.cpp
