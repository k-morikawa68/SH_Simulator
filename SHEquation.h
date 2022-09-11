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
public:
	virtual void Construct(Input&);
	virtual double CalcRHS(double**, int, int);
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
};

class SH_Type1 : public SHEquation{
private:
	double Alpha;
	double Lambda;
public:
	void Construct(Input&);
	double CalcRHS(double**, int, int);
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
};

#endif
