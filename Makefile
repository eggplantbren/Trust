CXX = g++
FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -c Channel.cpp
	$(CXX) $(FLAGS) -c Soften.cpp
	ar rcs libTrust.a *.o
	$(CXX) -I . $(FLAGS) -c Tests/channel_serialisation.cpp
	$(CXX) -L . -o Tests/channel_serialisation channel_serialisation.o -lTrust
