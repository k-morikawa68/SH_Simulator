#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "SHEquation.h"
#include "Input.h"

class SecondRungeKutta{
private:
	int Nx;
	int Ny;
	double Dt;
	int NumThread;

	double** u_half;
public:
	~SecondRungeKutta();
	//void Construct(int, int, double, int, double, double, double);
	void Construct(Input&);
	void SetNumThread(int);
	void CalcNext(double**, double**, SHEquation*);
};

#endif
