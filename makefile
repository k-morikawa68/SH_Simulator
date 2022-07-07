CXX = g++
CXXFLAGS = -std=c++11 -fopenmp
OBJS = \
	   main.o\
	   Functions.o\
	   SHEquation.o\
	   Simulator.o\
	   Solver.o\
	   Input.o\

PROGRAM = SwiftHohenberg

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGRAM).out

clean:
	rm -f *.o *.out
