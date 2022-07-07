#include <iostream>
#include "Functions.h"

void Functions::Construct(Input& ip){
	Dx = ip.Dx;
	Nx = ip.Nx;
	Ny = ip.Ny;
}

double Functions::Dx2(double** w, int x, int y){
	double result = (w[(x+1)%Nx][y] - w[x][y]) + (w[(x-1+Nx)%Nx][y] - w[x][y]); // periodic boundary condition
	result /= Dx * Dx;
	return result;
} 
double Functions::Dy2(double** w, int x, int y){
	double result = (w[x][(y+1)%Ny] - w[x][y]) + (w[x][(y-1+Ny)%Ny] - w[x][y]); // periodic boundary condition
	result /= Dx * Dx;
	return result;
}
double Functions::Dx4(double** w, int x, int y){
	double tmp[5];
	tmp[0] = w[(x+2)%Nx][y];
	tmp[1] = -4.0 * w[(x+1)%Nx][y];
	tmp[2] = 6.0 * w[x][y];
	tmp[3] = -4.0 * w[(x-1+Nx)%Nx][y];
	tmp[4] = w[(x-2+Nx)%Nx][y];
	double result = 0.0;
	for(int i = 0; i < 5; i++){
		result += tmp[i]; // periodic boundary condition
	}
	result /= Dx * Dx * Dx * Dx;
	return result;
}
double Functions::Dy4(double** w, int x, int y){
	double tmp[5];
	tmp[0] = w[x][(y+2)%Ny];
	tmp[1] = -4.0 * w[x][(y+1)%Ny];
	tmp[2] = 6.0 * w[x][y];
	tmp[3] = -4.0 * w[x][(y-1+Ny)%Ny];
	tmp[4] = w[x][(y-2+Ny)%Ny];
	double result = 0.0;
	for(int i = 0; i < 5; i++){
		result += tmp[i]; // periodic boundary condition
	}
	result /= Dx * Dx * Dx * Dx;
	return result;
}
double Functions::Dx2Dy2(double** w, int x, int y){
	double tmp[9];
	tmp[0] = w[(x+1)%Nx][(y+1)%Ny];
	tmp[1] = -2.0 * w[(x+1)%Nx][y];
	tmp[2] = w[(x+1)%Nx][(y-1+Ny)%Ny];
	tmp[3] = -2.0 * w[x][(y+1)%Ny];
	tmp[4] = 4.0 * w[x][y];
	tmp[5] = -2.0 * w[x][(y-1+Ny)%Ny];
	tmp[6] = w[(x-1+Nx)%Nx][(y+1)%Ny];
	tmp[7] = -2.0 * w[(x-1+Nx)%Nx][y];
	tmp[8] = w[(x-1+Nx)%Nx][(y-1+Ny)%Ny];
	double result = 0.0;
	for(int i = 0; i < 9; i++){
		result += tmp[i]; // periodic boundary condition
	}
	result /= Dx * Dx * Dx * Dx;
	return result;
}

double Functions::Laplacian(double** w, int x, int y){
	double result = Dx2(w, x, y) + Dy2(w, x, y); // periodic boundary condition
	return result;
}

double Functions::Laplacian2(double** w, int x, int y){
	double result = Dx4(w, x, y) + 2.0 * Dx2Dy2(w, x, y) + Dy4(w, x, y); // periodic boundary condition
	return result;
}

double Functions::RampFunc(double w, double a){
	double result;
	if(w < a){
		result = 0.0;
	}else{
		result = w - a;
	}
	return result;
}
