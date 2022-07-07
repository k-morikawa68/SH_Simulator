#include <iostream>
#include <fstream>
#include "SHEquation.h"

void SHEquation::Construct(Input& ip){

}
double SHEquation::CalcRHS(double** w_old, int x, int y){
	return 0.0;
}

void SH_Type0::Construct(Input& ip){
	std::cout << "ReadParameter ... " << std::endl;

	DirName = ip.DirName;
	std::string fname = DirName + "/input/parameter_type0.txt";
	std::ifstream fin(fname);
	if(!fin){
		std::cout << "Error: cannot open parameter_type0 file." << std::endl;
		exit(1);
	}

	std::string dummy;
	fin >> dummy; fin >> Alpha; std::cout << "Alpha: " << Alpha << std::endl;
	fin >> dummy; fin >> Beta; std::cout << "Beta: " << Beta << std::endl;

	std::string check;
	fin >> check;
	if(check != "End"){
		std::cout << "Error: invalid parameter file." << std::endl;
		exit(1);
	}
	fin.close();

	F.Construct(ip);
	std::cout << "done." << std::endl;
}
double SH_Type0::CalcRHS(double** w_old, int x, int y){
	double term1 = -F.Laplacian2(w_old, x, y);
	double term2 = -F.Laplacian(w_old, x, y);
	double term3 = -Alpha * w_old[x][y];
	double term4 = -Beta * w_old[x][y] * w_old[x][y] * w_old[x][y];
	double f = term1 + term2 + term3 + term4;
	return f;
}

void SH_Type1::Construct(Input& ip){
	std::cout << "ReadParameter ... " << std::endl;
	DirName = ip.DirName;
	std::string fname = DirName + "/input/parameter_type1.txt";
	std::ifstream fin(fname);
	if(!fin){
		std::cout << "Error: cannot open parameter_type1 file." << std::endl;
		exit(1);
	}
	std::string dummy;
	fin >> dummy; fin >> Alpha; std::cout << "Alpha: " << Alpha << std::endl;
	fin >> dummy; fin >> Lambda; std::cout << "Lambda: " << Lambda << std::endl;

	std::string check;
	fin >> check;
	if(check != "End"){
		std::cout << "Error: invalid parameter file." << std::endl;
		exit(1);
	}
	fin.close();

	F.Construct(ip);
	std::cout << "done." << std::endl;
}

double SH_Type1::CalcRHS(double** w_old, int x, int y){
	double term1 = -F.Laplacian2(w_old, x, y);
	double term2 = -F.Laplacian(w_old, x, y);
	double term3 = -Alpha * (F.RampFunc(w_old[x][y], (1.0 - Lambda)) - F.RampFunc(-w_old[x][y], Lambda));
	double f = term1 + term2 + term3;
	return f;
}
