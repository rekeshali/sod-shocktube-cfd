#include <cmath>
#include <cstdlib>
#include <cstring>
#include "matrix.hpp"
#include "state.hpp"

State::State(int a, int b, double c, double d){
	// class construction
	jd = a; dof = b; gam = b; R = c; // space + properties
	// Initialize flux and jacobian matrices
	size(jd, dof); // size for Q
	Qn.size(jd, dof);
	F.size(jd, dof);
	T.size(dof, dof);
	Lam.size(dof,dof); 
	Lam.zeros();
	Ti.size(dof,dof);
}

void State::init(double * L, double * R){
	// initialization of state
	for(int j = 0; j < jd; j++){
		if(j <= jd/2){
			ic2q(Mat::operator[](j), L);
		}else{
			ic2q(Mat::operator[](j), R);
		}
	}
}

void State::ic2q(double * qi, double * ic){
	if(dof == 3){
		qi[0] = ic[0];
		qi[1] = ic[0]*ic[1];
		qi[2] = ic[2]/(gam-1) + 0.5*ic[0]*ic[1]*ic[1];
	}
}

void State::updateFlux(){
	for(int j = 0; j < jd; j++){
		q2flx(F[j], Mat::operator[](j));
	}
}

void State::q2flx(double * f, double * q){
		f[0] = q[1];
		f[1] = q[1]*q[1]/q[0] + (gam-1)*(q[2] - q[1]*q[1]/(2*q[0]));
		f[2] = q[1]*q[2]/q[0] + (gam-1)*(q[1]*q[2]/q[0] - q[1]*q[1]*q[1]/(2*q[0]*q[0]));
}

void State::updateFuture(int j, Mat qn){
	Qn(j, 0) = qn(0,0);
	Qn(j, 1) = qn(1,0);
	Qn(j, 2) = qn(2,0);

}

void State::updatePresent(){
	memcpy(data, Qn[0], jd*dof*sizeof(double));
}
// Decomposed Flux Jacobian
Mat State::absA(double * q){
	double u = vel(q); // useful params
	double a = sos(q);
	double h = nth(q);
	//////////////////// T
	T(0,0) = 1; 
	T(0,1) = 1; 
	T(0,2) = 1;
	T(1,0) = u-a; 
	T(1,1) = u; 
	T(1,2) = u+a;
	T(2,0) = h-u*a;	
	T(2,1) = 0.5*u*u; 
	T(2,2) = h-u*a;
	/////////////////// Lambda
	Lam(0,0) = abs(u-a); 
	Lam(1,1) = u; 
	Lam(2,2) = abs(u+a);
	/////////////////// Ti
	double sml = (gam-1)/(a*a);
	Ti(0,0) =  (u/(4*a))*(2+(gam-1)*u/a); // begin construction
	Ti(0,1) = -(1/(2*a))*(1+(gam-1)*u/a);
	Ti(0,2) =  sml/2;
	Ti(1,0) =  1-sml*u*u/2; 
	Ti(1,1) =  sml*u; 
	Ti(1,2) = -sml;
	Ti(2,0) = -(u/(4*a))*(2-(gam-1)*u/a);
	Ti(2,1) =  (1/(2*a))*(1-(gam-1)*u/a); 
	Ti(2,2) =  sml/2;
// 	T.print(); Lam.print(); Ti.print();
	return T*Lam*Ti;
}

// // functions for deriving flow props from state
double State::rho(double * q){
	return q[0];
}

double State::vel(double * q){
	return q[1]/q[0];
}

double State::nrg(double * q){
	return q[2]/q[0];
}

double State::bar(double * q){
	return (gam-1)*(q[2] - 0.5*q[1]*q[1]/q[0]);
}

double State::sos(double * q){
	return sqrt(gam*bar(q)/rho(q));
}
		
double State::nth(double * q){
	return nrg(q) + bar(q)/rho(q);
}
