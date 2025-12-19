CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=gnu++98 -ggdb3

all: circles

circles: main.o point.o circle.o
	$(CXX) $(CXXFLAGS) -o circles main.o point.o circle.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

