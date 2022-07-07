#include <iostream>
#include <fstream>
#include "Input.h"

void Input::ReadInputFile(std::string dirName){
	DirName = dirName;
	std::cout << "ReadInputFile ... " << std::endl;
	std::string fname = DirName + "/input/input.txt";
	std::ifstream fin(fname);
	if(!fin){
		std::cout << "Error: cannot open input file." << std::endl;
		exit(1);
	}
	std::string dummy;
	fin >> dummy; fin >> SH_Type; std::cout << "SH_Type: " << SH_Type << std::endl;

	fin >> dummy; fin >> Dt; std::cout << "Dt: " << Dt << std::endl;
	fin >> dummy; fin >> Dx; std::cout << "Dx: " << Dx << std::endl;

	fin >> dummy; fin >> Nx; std::cout << "Nx: " << Nx << std::endl;
	fin >> dummy; fin >> Ny; std::cout << "Ny: " << Ny << std::endl;

	fin >> dummy; fin >> NumIteration; std::cout << "NumIteration: " << NumIteration << std::endl;
	fin >> dummy; fin >> OutputStep; std::cout << "OutputStep: " << OutputStep << std::endl;

	fin >> dummy; fin >> NumThread; std::cout << "NumThread: " << NumThread << std::endl;

	fin >> dummy; fin >> InputInitMode; std::cout << "InputInitMode: " << InputInitMode << std::endl;
	fin >> dummy; fin >> InputInitFileName; std::cout << "InputInitFileName: " << InputInitFileName << std::endl;

	std::string check;
	fin >> check;
	if(check != "End"){
		std::cout << "Error: invalid input file." << std::endl;
		exit(1);
	}
	fin.close();
	std::cout << "done." << std::endl;
}
