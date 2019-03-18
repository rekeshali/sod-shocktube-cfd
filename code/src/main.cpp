#include <iostream>
#include "io.hpp"
#include "matrix.hpp"
#include "shocktube.hpp"
#include "solver.hpp"
using namespace std;
int main(int argc, char **argv){
	// Program arguments
	char * method  = argv[1];
	double dx	   = atof(argv[2]);
	double CFL	   = atof(argv[3]);
	char * outfile = argv[4];
	// Other params are hardcoded because
	// they are classic Sod ShockTube values
	double L   = 1;
	double T   = 0.2;
	double R   = 1;
	double gam = 1.4;
	// Sod Shocktube classic initial conditions
	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};
	// ShockTube object contain state and flux
	ShockTube Sod(dx, L, gam, R);
	Sod.fillTube(ICL, ICR);
	// Printing object
	STDIO IO(outfile);
	IO.stateToFile(Sod); // Initial print
	// Explicit Euler solver with choice of CFL
	// and method. Does work on ShockTube object.
	Solver EE(Sod, CFL, method);
	// Let the solver run until all time elapses
	int nframes = 40; // number of snapshots
	while(EE.timeElapsed() < T){
		EE.timeMarch(); // moves forward one time step
		if(EE.timeElapsed() > IO.td*T/nframes){ // prints nframs times
			IO.stateToFile(Sod);
		}
	}
	IO.close(); // prints number of tsteps and grid points
	return 0;
}
