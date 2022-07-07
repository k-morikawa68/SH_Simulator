#include <iostream>
#include "Simulator.h"

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cout << "Error: the number of values in console command\n";
		std::cout << "Please put the directory name of workspace.\n";
		std::cout << std::endl;
		exit(1);
	}
	std::string dirName = argv[1];
	Simulator Sim(dirName);
	Sim.Initialize();
	Sim.OutputVTK(0);
	Sim.IterateSecondRungeKuttaStep(1);
	std::cout << "Simulation finished." << std::endl;
	Sim.Output();

	return 0;
}
