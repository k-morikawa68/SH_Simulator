#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>

class Input{
public:
	std::string DirName;
	int SH_Type;

	double Dt;
	double Dx;
	int Nx;
	int Ny;

	int NumIteration;
	int OutputStep;

	int NumThread;

	int InputInitMode;
	std::string InputInitFileName;

	void ReadInputFile(std::string);
};

#endif
