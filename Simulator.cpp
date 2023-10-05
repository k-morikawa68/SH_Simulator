#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Simulator.h"

Simulator::Simulator(std::string dirName){
	DirName = dirName;
	IP.ReadInputFile(DirName);
	SH_Type = IP.SH_Type;
	Nx = IP.Nx;
	Ny = IP.Ny;
	NumIteration = IP.NumIteration;
	OutputStep = IP.OutputStep;
	InputInitMode = IP.InputInitMode;
	InputInitFileName = IP.InputInitFileName;

	switch(SH_Type){
		case 0:
			pSH = new SH_Type0;
			break;
		case 1:
			pSH = new SH_Type1;
			break;
		case 2:
			pSH = new SH_Type2;
	}
	pSH->Construct(IP);
}

Simulator::~Simulator(){
	delete pSH;
	for(int i = 0; i < Nx; i++){
		delete[] u[i];
		delete[] u_old[i];
	}
	delete[] u;
	delete[] u_old;
}

void Simulator::ReadInitFile(){
	std::string fname = DirName + "/input/" + InputInitFileName;
	std::ifstream fin(fname);
	if(!fin){
		std::cout << "Error: cannot open init file." << std::endl;
		exit(1);
	}
	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			fin >> u[i][j]; 
		}
	}
}

void Simulator::Initialize(){
	std::cout << "Initialize ... " << std::endl;
	//std::random_device rnd;
	//int rand_seed = rnd();
	int rand_seed = 20220425;
	mt.seed(rand_seed);
	std::cout << "Random seed = " << rand_seed << std::endl;
	std::uniform_real_distribution<> RAND_R(-0.001, 0.001);

	u = new double*[Nx];
	u_old = new double*[Nx];
	for(int i = 0; i < Nx; i++){
		u[i] = new double[Ny];
		u_old[i] = new double[Ny];
	}

	// Setting the initial value of u
	if(InputInitMode == 0){
		for(int i = 0; i < Nx; i++){
			for(int j = 0; j < Ny; j++){
				u[i][j] = RAND_R(mt);
			}
		}
	}else if(InputInitMode == 1){
		ReadInitFile();
	}

	SRK.Construct(IP);

	std::cout << "done." << std::endl;
}

void Simulator::OutputVTK(int step){
	std::stringstream ss_u;
	ss_u << "d" << std::setw(9) << std::setfill('0') << step << ".vtk";
	std::string fname = ss_u.str();
	fname = DirName + "/" + fname;
	std::ofstream fout(fname);
	fout << "# vtk DataFile Version 3.0\n";
	fout << "SwiftHohenberg\n";
	fout << "ASCII\n";
	fout << "DATASET STRUCTURED_POINTS\n";
	fout << "DIMENSIONS " << Nx << " " << Ny << " " << 1 << "\n";
	fout << "ORIGIN " << 0 << " " << 0 << " " << 0 << "\n";
	fout << "SPACING " << 1 << " " << 1 << " " << 1 << "\n";
	fout << "POINT_DATA " << Nx * Ny << "\n";
	fout << "SCALARS u float\n";
	fout << "LOOKUP_TABLE default\n";
	for(int y = 0; y < Ny; y++){
		for(int x = 0; x < Nx; x++){
			fout << (float)u[x][y] << "\n";
		}
	}
	fout.close();
}

void Simulator::Output(){
	std::string fname = "result.dat";
	fname = DirName + "/" + fname;
	std::ofstream fout(fname);
	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			fout << u[i][j] << " ";
		}
		fout << "\n";
	}
	fout.close();
}

void Simulator::IterateSecondRungeKuttaStep(int startStep){
	int endStep = startStep - 1 + NumIteration;
	for(int i = startStep; i <= endStep; i++){
		SRK.CalcNext(u_old, u, pSH);
		if(i % OutputStep == 0){
			OutputVTK(i);
		}
	}
}
