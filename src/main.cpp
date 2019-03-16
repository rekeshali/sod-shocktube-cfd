#include <iostream>
#include <fstream>
#include <cmath>
// #include "io.hpp"
#include "matrix.hpp"
#include "state.hpp"
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
	int dof = 3;
	int jd = int(L/dx);
	int td = int(T/dt);

	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};

	State Q(jd, dof, gam, R);
	Q.init(ICL, ICR);

	ofstream myfile ("out");
	myfile << td+1 << " " << jd << endl;
	for (int j = 0; j < jd; j ++){
		myfile << Q(j,0) << " " << Q(j,1) << " " << Q(j,2) << endl;
	}
	int jj, tt, ti;
	jj = 101;
	tt = 10;
	ti = 1;
// 	File myfile(jd, td);	
	Solver sod(jd, dof, dx, dt);	
	for(int t = 0; t < td; t++){
		sod.FVS(Q);
		for (int j = 0; j < jd; j ++){
			myfile << Q(j,0) << " " << Q(j,1) << " " << Q(j,2) << endl;
		}
// 		myfile.out(Q);
	}

	myfile.close();
	return 0;
}
