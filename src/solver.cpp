#include <cmath>
#include "matrix.hpp"
#include "shocktube.hpp"
#include "solver.hpp"
#include "space.hpp"
#include <iostream>
using namespace std;
int Solver::dof = 3;

Solver::Solver(ShockTube& a, double b, const char * c){
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
	Spatial.spatialScheme(*Sod, c);
}

// Explicit Euler solver
void Solver::timeMarch(){
	updateDt();		   // new dt
	Sod->updateFlux(); // new fluxes
	for(j = 0; j < jd; j++){
		q &= Sod->Q[j];			  // local present state
		f = Spatial.splitFlux(j); // flux splitting
		qn = q - (dt/dx)*f;		  // local future state
		updateFuture();			  // save local future state to global
	}
	updatePresent(); // move glabal future to glabal present
	time += dt;		 // increase time elapsed
}

double Solver::timeElapsed(){
	return time;
}

void Solver::updateDt(){
	// Keeps dt in line with CFL
	// uc = |u| + a
	ucmax = 0;
	for(j = 0; j < jd; j++){
		uc = abs(Sod->vel(Sod->Q[j]))
			 + Sod->sos(Sod->Q[j]);
		if(uc > ucmax){
			ucmax = uc;
		}
	}
	dt = CFL*dx/ucmax;
}

void Solver::updateFuture(){
	Qn(j,0) = qn(0,0);
	Qn(j,1) = qn(1,0);
	Qn(j,2) = qn(2,0);
}

void Solver::updatePresent(){
	memcpy(Sod->Q[0], Qn[0], jd*dof*sizeof(double));	
}
