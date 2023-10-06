#include <iostream>
#include <omp.h>
#include "Solver.h"
#include <cmath>

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

#pragma omp parallel for num_threads(NumThread)
	for(int i = 0; i < Nx; i++){
#pragma omp parallel for num_threads(NumThread)
		for(int j = 0; j < Ny; j++){
			double f = psh->CalcRHS(u_old, i, j);
			u_half[i][j] = u_old[i][j] + f * 0.5 * Dt;
		}
	}

#pragma omp parallel for num_threads(NumThread)
	for(int i = 0; i < Nx; i++){
#pragma omp parallel for num_threads(NumThread)
		for(int j = 0; j < Ny; j++){
			double f_half = psh->CalcRHS(u_half, i, j);
			u[i][j] = u_old[i][j] + f_half * Dt;
		}
	}
}

