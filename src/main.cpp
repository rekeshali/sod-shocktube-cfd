#include <iostream>
#include <fstream>
#include <cmath>
#include "io.hpp"
#include "matrix.hpp"
#include "shocktube.hpp"
#include "solver.hpp"
using namespace std;
int main(){
	int nframes = 50;
	double dx  = 0.01;
	double L   = 1;
	double T   = 0.2;
	double R   = 1;
	double gam = 1.4;
	double CFL = 0.5;

	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};

	ShockTube Sod(dx, L, gam, R);
	Sod.fillTube(ICL, ICR);

	STDIO IO("out");
	IO.stateToFile(Sod);

	Solver EE(Sod, CFL, "H");

	while(EE.timeElapsed() < T){
		EE.timeMarch();
		if(EE.timeElapsed() > IO.td*T/nframes){
			IO.stateToFile(Sod);
		}
	}
	IO.close();
	return 0;
}
