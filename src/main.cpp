#include <ctime>
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
	int nframes = 75; // number of snapshots printed
	int cputi, cputt = 0; // beginning timer
	while(EE.timeElapsed() < T){
		cputi = clock(); // begin timer
		EE.timeMarch();  // moves forward one time step
		cputt += clock() - cputi; // end timer
		if(EE.timeElapsed() > IO.frames*T/nframes){ // prints nframs times
			IO.stateToFile(Sod);
		}
	}
	// print number of frames, grid points, cpu time, and close file
	IO.close(double(cputt)/CLOCKS_PER_SEC); 	
	return 0;
}
