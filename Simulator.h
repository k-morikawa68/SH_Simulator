#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <string>
#include <random>
#include "Input.h"
#include "SHEquation.h"
#include "Solver.h"

class Simulator{
private:
	Input IP;
	std::mt19937 mt;
	std::string DirName;
	int SH_Type;
	int Nx;
	int Ny;
	int NumIteration;
	int OutputStep;
	int InputInitMode;
	std::string InputInitFileName;
	double** u;
	double** u_old;
	SHEquation* pSH;
	SecondRungeKutta SRK;
public:
	Simulator(std::string);
	~Simulator();
	void ReadInitFile();
	void Initialize();
	void IterateSecondRungeKuttaStep(int);
	void OutputVTK(int);
	void Output();
};

#endif
