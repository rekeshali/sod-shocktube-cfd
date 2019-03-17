#include "matrix.hpp"
#include "state.hpp"
#include "solver.hpp"

Solver::Solver(int a, double b, double c, double d){
	// Initializing solver
	dof  = a; dx = b; L = c; CFL = d;
	jd   = int(L/dx);
	time = 0.0;
	// Initializing local point matrices
	qn.size(dof,1);
	q. size(dof,1);
	f. size(dof,1);
	Qn.size(jd,dof);
}

void Solver::timeMarch(State& Q){
	updateDt();
	Q.updateFlux();
	for(j = 1; j < jd-1; j++){
		q &= Q[j];
		// f = stegerW
		qn = q - (dt/(2*dx))*f;
		Q.updateFuture(j, qn);
	}
	// Left B
	// Right B
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
	
}
