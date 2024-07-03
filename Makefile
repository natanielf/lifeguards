SHELL    = /bin/sh
CXX      = g++
CXXFLAGS = -Wall
RM       = rm -f

TARGETS = lifeguards

all : $(TARGETS)
.PHONY : all

lifeguards : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o lifeguards

clean :
	$(RM) $(TARGETS) *.o
.PHONY : clean
