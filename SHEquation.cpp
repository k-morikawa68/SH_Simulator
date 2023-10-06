#include <iostream>
#include <fstream>
#include "SHEquation.h"
#include <cmath>

void SHEquation::Construct(Input& ip){
}
double SHEquation::CalcRHS(double** w_old, int x, int y){
	return 0.0;
}
double SHEquation::CalcRHS_NL(double** w_old, int x, int y){
	return 0.0;
}
int SHEquation::GetType(){
	return Type;
}
double SHEquation::GetEnergy(){
	return Energy;
}
void SHEquation::CalcEnergy(double** w){
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

	Type = 0;
	Nx = ip.Nx;
	Ny = ip.Ny;
	Dx = ip.Dx;
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
double SH_Type0::CalcRHS_NL(double** w_old, int x, int y){
	double term3 = -c * w_old[x][y];
	double term4 = -d * w_old[x][y] * w_old[x][y];
	double term5 = -e * w_old[x][y] * w_old[x][y] * w_old[x][y];
	double f = term3 + term4 + term5;
	return f;
}
void SH_Type0::CalcEnergy(double** w){
	double eng = 0.0;
	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			double dudx = (w[(i+1)%Nx][j] - w[(i-1+Nx)%Nx][j]) / Dx * 0.5;
			double dudy = (w[i][(j+1)%Ny] - w[i][(j-1+Ny)%Ny]) / Dx * 0.5;
			double term1 = 0.5 * a * pow(F.Laplacian(w, i, j), 2);
			double term2 = -0.5 * b * (pow(dudx, 2) + pow(dudy, 2));
			double term3 = 0.5 * c * pow(w[i][j], 2);
			double term4 = d * pow(w[i][j], 3) / 3.0;
			double term5 = 0.25 * e * pow(w[i][j], 4);
			eng +=  term1 + term2 + term3 + term4 + term5;
		}
	}
	Energy = eng;
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

	Type = 1;
	Nx = ip.Nx;
	Ny = ip.Ny;
	Dx = ip.Dx;
	std::cout << "done." << std::endl;
}

double SH_Type1::CalcRHS(double** w_old, int x, int y){
	double term1 = -F.Laplacian2(w_old, x, y);
	double term2 = -F.Laplacian(w_old, x, y);
	double term3 = -Alpha * (F.RampFunc(w_old[x][y], (1.0 - Lambda)) - F.RampFunc(-w_old[x][y], Lambda));
	double f = term1 + term2 + term3;
	return f;
}
double SH_Type1::CalcRHS_NL(double** w_old, int x, int y){
	double term3 = -Alpha * (F.RampFunc(w_old[x][y], (1.0 - Lambda)) - F.RampFunc(-w_old[x][y], Lambda));
	double f = term3;
	return f;
}
void SH_Type1::CalcEnergy(double** w){
	double eng = 0.0;
	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			double dudx = (w[(i+1)%Nx][j] - w[(i-1+Nx)%Nx][j]) / Dx * 0.5;
			double dudy = (w[i][(j+1)%Ny] - w[i][(j-1+Ny)%Ny]) / Dx * 0.5;
			double term1 = 0.5 * pow(F.Laplacian(w, i, j), 2);
			double term2 = -0.5 * (pow(dudx, 2) + pow(dudy, 2));
			double term3 = 0.5 * Alpha * (pow(F.RampFunc(w[i][j], (1.0-Lambda)), 2) + pow(F.RampFunc(-w[i][j], Lambda), 2));
			eng +=  term1 + term2 + term3;
		}
	}
	Energy = eng;
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

	Type = 2;
	Nx = ip.Nx;
	Ny = ip.Ny;
	Dx = ip.Dx;
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
double SH_Type2::CalcRHS_NL(double** w_old, int x, int y){
	double term3 = -Alpha_a * F.RampFunc(w_old[x][y], 0.0) - Beta_a * F.RampFunc(w_old[x][y], 0.0) * w_old[x][y] * w_old[x][y];
	double term4 = Alpha_b * F.RampFunc(-w_old[x][y], 0.0) + Beta_b * F.RampFunc(-w_old[x][y], 0.0) * w_old[x][y] * w_old[x][y];
	double f = term3 + term4;
	return f;
}
void SH_Type2::CalcEnergy(double** w){
	double eng = 0.0;
	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			double dudx = (w[(i+1)%Nx][j] - w[(i-1+Nx)%Nx][j]) / Dx * 0.5;
			double dudy = (w[i][(j+1)%Ny] - w[i][(j-1+Ny)%Ny]) / Dx * 0.5;
			double term1 = 0.5 * pow(F.Laplacian(w, i, j), 2);
			double term2 = -0.5 * (pow(dudx, 2) + pow(dudy, 2));
			double term3 = 0.5 * (Alpha_a * pow(F.RampFunc(w[i][j], 0.0), 2) + Alpha_b * pow(F.RampFunc(-w[i][j], 0.0), 2));
			double term4 = 0.25 * (Beta_a * pow(F.RampFunc(w[i][j], 0.0), 4) + Beta_b * pow(F.RampFunc(-w[i][j], 0.0), 4));
			eng +=  term1 + term2 + term3 + term4;
		}
	}
	Energy = eng;
}
