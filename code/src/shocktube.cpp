#include <cmath>
#include "matrix.hpp"
#include "shocktube.hpp"

int ShockTube::dof = 3;

ShockTube::ShockTube(double a, double b, double c, double d){
	// class construction
	dx = a; L = b; gam = c; R = d; // space + properties
	jd = int(L/dx);
	// ShockTube holds its state and flux
	Q.size(jd, dof);
	F.size(jd, dof);
}

void ShockTube::fillTube(double * L, double * R){
	// initialization of state
	for(int j = 0; j < jd; j++){
		if(j <= jd/2){
			ic2q(Q[j], L);
		}else{
			ic2q(Q[j], R);
		}
	}
}

void ShockTube::ic2q(double * qi, double * ic){
	if(dof == 3){
		qi[0] = ic[0];
		qi[1] = ic[0]*ic[1];
		qi[2] = ic[2]/(gam-1) + 0.5*ic[0]*ic[1]*ic[1];
	}
}

void ShockTube::updateFlux(){
	for(int j = 0; j < jd; j++){
		q2flx(F[j], Q[j]);
	}
}

void ShockTube::q2flx(double * f, double * q){
		f[0] = q[1];
		f[1] = q[1]*q[1]/q[0] + (gam-1)*(q[2] - q[1]*q[1]/(2*q[0]));
		f[2] = q[1]*q[2]/q[0] + (gam-1)*(q[1]*q[2]/q[0] - q[1]*q[1]*q[1]/(2*q[0]*q[0]));
}

// // functions for deriving flow props from state
double ShockTube::rho(double * q){
	return q[0];
}

double ShockTube::vel(double * q){
	return q[1]/q[0];
}

double ShockTube::nrg(double * q){
	return q[2]/q[0];
}

double ShockTube::bar(double * q){
	return (gam-1)*(q[2] - 0.5*q[1]*q[1]/q[0]);
}

double ShockTube::sos(double * q){
	return sqrt(gam*bar(q)/rho(q));
}
		
double ShockTube::nth(double * q){
	return nrg(q) + bar(q)/rho(q);
}
