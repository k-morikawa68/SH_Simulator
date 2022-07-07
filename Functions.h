#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Input.h"

class Functions{
private:
	double Dx; // Dy = Dx
	int Nx; // 周期境界の場合、端の値の計算に用いる
	int Ny; // 周期境界の場合、端の値の計算に用いる
public:
	void Construct(Input&);
	double Laplacian(double**, int, int);
	double Laplacian2(double**, int, int);
	double RampFunc(double, double);
	double Dx2(double**, int, int);
	double Dy2(double**, int, int);
	double Dx4(double**, int, int);
	double Dy4(double**, int, int);
	double Dx2Dy2(double**, int, int);
};

#endif
