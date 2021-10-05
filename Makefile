CXX = g++
FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -c Channel.cpp
	$(CXX) $(FLAGS) -c Database.cpp
	$(CXX) $(FLAGS) -c Soften.cpp
	$(CXX) $(FLAGS) -c Support.cpp
	ar rcs libTrust.a *.o
	$(CXX) -I . $(FLAGS) -c Tests/channel_serialisation.cpp
	$(CXX) -I . $(FLAGS) -c Tests/support_serialisation.cpp
	$(CXX) -L . -o Tests/channel_serialisation channel_serialisation.o -lTrust
	$(CXX) -L . -o Tests/support_serialisation support_serialisation.o -lTrust
