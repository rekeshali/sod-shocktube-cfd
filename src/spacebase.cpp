#include <cmath>
#include "spacebase.hpp"
int Space::dims = 3;

Space::Space(int a, double b, double c){
	// class construction
	jd  = a; gam = b; R	= c;
}

void Space::init(double * L, double * R){
	// initialization of state
	q = new double[jd*dims];
	f = new double[jd*dims];
	for(int j = 0; j < jd; j++){
		if(j <= jd/2){
			q[j*dims + 0] = L[0];
			q[j*dims + 1] = L[0]*L[1];
			q[j*dims + 2] = L[2]/(gam-1) + 0.5*L[0]*L[1]*L[1];
		}else{
			q[j*dims + 0] = R[0];
			q[j*dims + 1] = R[0]*R[1];
			q[j*dims + 2] = R[2]/(gam-1) + 0.5*R[0]*R[1]*R[2];
		}
	}
	updateFlux();
}

void Space::updateFlux(){
	for(int j = 0; j < jd; j++){
		f[j*dims + 0] = q2(j);
		f[j*dims + 1] = q2(j)*q2(j)/q1(j) + (gam-1)*(q3(j) - q2(j)*q2(j)/(2*q1(j)));
		f[j*dims + 2] = q2(j)*q3(j)/q1(j) + (gam-1)*(q2(j)*q3(j)/q1(j) - q2(j)*q2(j)*q2(j)/(2*q1(j)*q1(j)));
	}

}

// getting state values
double Space::q1(int j){
	return q[j*dims + 0];
}

double Space::q2(int j){
	return q[j*dims + 1];
}

double Space::q3(int j){
	return q[j*dims + 2];
}
// getting flux values
double Space::f1(int j){
	return f[j*dims + 0];
}

double Space::f2(int j){
	return f[j*dims + 1];
}

double Space::f3(int j){
	return f[j*dims + 2];
}
// functions for deriving flow props from state
double Space::rho(int j){
	return q1(j);
}

double Space::vel(int j){
	return q2(j)/q1(j);
}

double Space::nrg(int j){
	return q3(j)/q1(j);
}

double Space::bar(int j){
	return (gam-1)*(q3(j) - 0.5*q2(j)*q2(j)/q1(j));
}

double Space::sos(int j){
	return sqrt(gam*bar(j)/rho(j));
}
		
double Space::nth(int j){
	return nrg(j) + bar(j)/rho(j);
}


