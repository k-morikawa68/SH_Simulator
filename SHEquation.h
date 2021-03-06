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
	double Alpha;
	double Beta;
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

#endif
