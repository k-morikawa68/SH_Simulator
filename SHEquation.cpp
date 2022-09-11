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
	fin >> dummy; fin >> a; std::cout << "a: " << a << std::endl;
	fin >> dummy; fin >> b; std::cout << "b: " << b << std::endl;
	fin >> dummy; fin >> c; std::cout << "c: " << c << std::endl;
	fin >> dummy; fin >> d; std::cout << "d: " << d << std::endl;
	fin >> dummy; fin >> e; std::cout << "e: " << e << std::endl;
	std::cout << "∂_t w = -aΔ^2w - bΔw - cw - dw^2 - ew^3" << std::endl;

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
	double term1 = -a * F.Laplacian2(w_old, x, y);
	double term2 = -b * F.Laplacian(w_old, x, y);
	double term3 = -c * w_old[x][y];
	double term4 = -d * w_old[x][y] * w_old[x][y];
	double term5 = -e * w_old[x][y] * w_old[x][y] * w_old[x][y];
	double f = term1 + term2 + term3 + term4 + term5;
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
	std::cout << "∂_t w = -Δ^2w - Δw - α(R(w-(1-Λ)) - R(-w - Λ))" << std::endl;

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

void SH_Type2::Construct(Input& ip){
	std::cout << "ReadParameter ... " << std::endl;

	DirName = ip.DirName;
	std::string fname = DirName + "/input/parameter_type2.txt";
	std::ifstream fin(fname);
	if(!fin){
		std::cout << "Error: cannot open parameter_type2 file." << std::endl;
		exit(1);
	}

	std::string dummy;
	fin >> dummy; fin >> Alpha_a; std::cout << "Alpha_a: " << Alpha_a << std::endl;
	fin >> dummy; fin >> Beta_a; std::cout << "Beta_a: " << Beta_a << std::endl;
	fin >> dummy; fin >> Alpha_b; std::cout << "Alpha_b: " << Alpha_b << std::endl;
	fin >> dummy; fin >> Beta_b; std::cout << "Beta_b: " << Beta_b << std::endl;
	std::cout << "∂_t w = -Δ^2w - Δw - α_a R(w) - β_a R(w)w^2 + α_b R(-w) + β_b R(-w)w^2" << std::endl;

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
double SH_Type2::CalcRHS(double** w_old, int x, int y){
	double term1 = -F.Laplacian2(w_old, x, y);
	double term2 = -F.Laplacian(w_old, x, y);
	//double term3 = -Alpha_a * w_old[x][y];
	//double term4 = -Beta_a * w_old[x][y] * w_old[x][y] * w_old[x][y];
	double term3 = -Alpha_a * F.RampFunc(w_old[x][y], 0.0) - Beta_a * F.RampFunc(w_old[x][y], 0.0) * w_old[x][y] * w_old[x][y];
	double term4 = Alpha_b * F.RampFunc(-w_old[x][y], 0.0) + Beta_b * F.RampFunc(-w_old[x][y], 0.0) * w_old[x][y] * w_old[x][y];
	double f = term1 + term2 + term3 + term4;
	return f;
}
