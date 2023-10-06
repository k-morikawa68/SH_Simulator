#ifndef _SHEQUATION_H_
#define _SHEQUATION_H_

#include <string>
#include "Input.h"
#include "Functions.h"

class SHEquation{
private:
protected:
	std::string DirName;
	Functions F;
	int Type;
	double Energy;
	int Nx, Ny;
	double Dx;
public:
	virtual void Construct(Input&);
	virtual double CalcRHS(double**, int, int);
	virtual double CalcRHS_NL(double**, int, int);
	int GetType();
	double GetEnergy();
	virtual void CalcEnergy(double**);
};

class SH_Type0 : public SHEquation{
private:
	double a;
	double b;
	double c;
	double d;
	double e;
public:
	void Construct(Input&);
	double CalcRHS(double**, int, int);
	double CalcRHS_NL(double**, int, int);
	void CalcEnergy(double**);
};

class SH_Type1 : public SHEquation{
private:
public:
	double Alpha;
	double Lambda;
	void Construct(Input&);
	double CalcRHS(double**, int, int);
	double CalcRHS_NL(double**, int, int);
	void CalcEnergy(double**);
};

class SH_Type2 : public SHEquation{
private:
	double Alpha_a;
	double Beta_a;
	double Alpha_b;
	double Beta_b;
public:
	void Construct(Input&);
	double CalcRHS(double**, int, int);
	double CalcRHS_NL(double**, int, int);
	void CalcEnergy(double**);
};

#endif
