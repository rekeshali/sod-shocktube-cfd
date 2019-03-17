#include <cmath>
#include <cstring>
#include "matrix.hpp"
#include "space.hpp"
#include "shocktube.hpp"
#include <iostream>
using namespace std;

int Space::dof = 3;

void Space::spatialScheme(ShockTube& a, const char * b){
	Sod = &a;
	method = b;
	gam = Sod->gam;
	// Shocktube
	q. size(dof,1);
	qp.size(dof,1);
	qm.size(dof,1);
	// Jacobian
	T. size(dof,dof);
	L. size(dof,dof);
	L. zeros();
	Ti.size(dof,dof);
	A. size(dof,dof);
	Ap.size(dof,dof);
	Am.size(dof,dof);
	// Flux
	fp.size(dof,1);
	fm.size(dof,1);
}
// Redirect flux splitting function
Mat Space::splitFlux(int j){
	if( strncmp(method,"StegerWarming",6) == 0){
		return StegerWarming(j);
	}
	else if( strncmp(method,"Roe",3) == 0){
		return StegerWarming(j);
	}
	else if( strncmp(method,"HLL",3) == 0){
		return StegerWarming(j);
	}
	else{
		cout << "ERROR: Choose an available flux splitting scheme--StegerWarming, Roe, or HLL." << endl;
		exit(-1);
	}
}
//##################### STEGER WARMING ##############################
Mat Space::StegerWarming(int j){
	// Space
	q  &= Sod->Q[ j ];
	qp &= Sod->Q[j+1];
	qm &= Sod->Q[j-1];
	// Jacobian
	A  = absA(Sod->Q[ j ]);
	Ap = absA(Sod->Q[j+1]);
	Am = absA(Sod->Q[j-1]);
	// Flux
	fp &= Sod->F[j+1];
	fm &= Sod->F[j-1];
	return fp - fm - ( Ap*qp - 2*A*q + Am*qm );
}

// Decomposed Flux Jacobian
Mat Space::absA(double * q){
    double u = vel(q); // useful params
    double a = sos(q);
    double h = nth(q);
// 	cout << "asfd" << endl;
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
    L(0,0) = abs(u-a);
    L(1,1) = u;
    L(2,2) = abs(u+a);
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
//     T.print(); L.print(); Ti.print();
    return T*L*Ti;
}

// // functions for deriving flow props from state
double Space::rho(double * q){
    return q[0];
}

double Space::vel(double * q){
    return q[1]/q[0];
}

double Space::nrg(double * q){
    return q[2]/q[0];
}

double Space::bar(double * q){
    return (gam-1)*(q[2] - 0.5*q[1]*q[1]/q[0]);
}

double Space::sos(double * q){
    return sqrt(gam*bar(q)/rho(q));
}

double Space::nth(double * q){
    return nrg(q) + bar(q)/rho(q);
}
