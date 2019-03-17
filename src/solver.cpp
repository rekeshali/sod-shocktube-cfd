#include "matrix.hpp"
#include "shocktube.hpp"
#include "solver.hpp"
#include "space.hpp"
#include <iostream>
using namespace std;
int Solver::dof = 3;

Solver::Solver(ShockTube& a, double b){
	// Initializing solver
	Sod  = &a;
	CFL  = b;
	jd   = Sod->jd;
	dx   = Sod->dx;
	time = 0.0;
	// Initialize future state
	Qn.size(jd,dof);
	// Initialize local state/flux
	qn.size(dof,1);
	q. size(dof,1);
	f. size(dof,1);
	// Initialize space discretizer
	Spatial.spatialScheme(*Sod, "StegerWarming");
}

void Solver::timeMarch(){
	updateDt();
	Sod->updateFlux();
	for(j = 1; j < jd-1; j++){
		q &= Sod->Q[j];
		f = Spatial.splitFlux(j);
		qn = q - (dt/(2*dx))*f;
		updateFuture();
	}
	// Left B
	j = 0;
	qn = Sod->Q[1];
	updateFuture();
	// Right B
	j = jd - 1;
	qn = Sod->Q[jd-2];
	updateFuture();
	updatePresent();
	time += dt;
}

double Solver::timeElapsed(){
	return time;
}

void Solver::updateDt(){
	// ucmax = something;
	// dt = CFL*dx/abs(ucmax);
	dt = 0.0005;
}

void Solver::updateFuture(){
	Qn(j,0) = qn(0,0);
	Qn(j,1) = qn(1,0);
	Qn(j,2) = qn(2,0);
}

void Solver::updatePresent(){
	memcpy(Sod->Q[0], Qn[0], jd*dof*sizeof(double));	
}
