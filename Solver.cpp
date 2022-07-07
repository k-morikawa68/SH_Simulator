#include <iostream>
#include <omp.h>
#include "Solver.h"

void SecondRungeKutta::Construct(Input& ip){
	Nx = ip.Nx;
	Ny = ip.Ny;
	Dt = ip.Dt;
	NumThread = ip.NumThread;
	u_half = new double*[Nx];
	for(int i = 0; i < Nx; i++){
		u_half[i] = new double[Ny];
	}
}

SecondRungeKutta::~SecondRungeKutta(){
	for(int i = 0; i < Nx; i++){
		delete[] u_half[i];
	}
	delete[] u_half;
}

void SecondRungeKutta::SetNumThread(int a){
	NumThread = a;
}
void SecondRungeKutta::CalcNext(double** u_old, double** u, SHEquation* psh){
#pragma omp parallel for num_threads(NumThread)
	for(int i = 0; i < Nx; i++){
#pragma omp parallel for num_threads(NumThread)
		for(int j = 0; j < Ny; j++){
			u_old[i][j] = u[i][j];
		}
	}

	// u(t)を使ってu(t+dt/2)を計算
#pragma omp parallel for num_threads(NumThread)
	for(int i = 0; i < Nx; i++){
#pragma omp parallel for num_threads(NumThread)
		for(int j = 0; j < Ny; j++){
			//double term1 = -Laplacian2(u_old, i, j);
			//double term2 = -Laplacian(u_old, i, j);
			//double term3 = -alpha * (RampFunc(u_old[i][j], (1.0 - Lambda)) - RampFunc(-u_old[i][j], Lambda));
			//double f = term1 + term2 + term3;
			double f = psh->CalcRHS(u_old, i, j);
			u_half[i][j] = u_old[i][j] + f * 0.5 * Dt;
		}
	}

	// u(t+dt/2)を使ってf(t+dt/2)を計算し、これとu(t)を使ってu(t+dt) = u(t) + f(t+dt/2) * dtを計算
#pragma omp parallel for num_threads(NumThread)
	for(int i = 0; i < Nx; i++){
#pragma omp parallel for num_threads(NumThread)
		for(int j = 0; j < Ny; j++){
			//double term1 = -Laplacian2(u_half, i, j);
			//double term2 = -Laplacian(u_half, i, j);
			//double term3 = -alpha * (RampFunc(u_half[i][j], (1.0 - Lambda)) - RampFunc(-u_half[i][j], Lambda));
			//double f_half = term1 + term2 + term3;
			double f_half = psh->CalcRHS(u_half, i, j);
			u[i][j] = u_old[i][j] + f_half * Dt;
		}
	}
}
