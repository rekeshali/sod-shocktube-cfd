#include <iostream>
#include <fstream>
#include <cmath>
#include "io.hpp"
#include "matrix.hpp"
#include "shocktube.hpp"
#include "solver.hpp"
using namespace std;
int main(){
	double dx = 0.005;
	double dt = 0.0005;
	double L = 1;
	double T = 0.2;
	double R = 1;
	double gam = 1.4;
	double CFL = 0.5;
	int jd = int(L/dx);
	int td = int(T/dt);

	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};

	ShockTube Sod(dx, L, gam, R);
	Sod.fillTube(ICL, ICR);

	STDIO IO("out");
	IO.stateToFile(Sod);

	Solver EESW(Sod, CFL, "Roe");

	while(EESW.timeElapsed() < T){
		EESW.timeMarch();
		IO.stateToFile(Sod);
	}
	IO.close();
	return 0;
}
