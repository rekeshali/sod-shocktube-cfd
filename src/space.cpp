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
	// Initialize scheme specific vars
	if( (strncmp(method,"S",1) == 0) || (strncmp(method,"s",1) == 0) ){ 
		StegerWarmingInit();
	}
	else if( (strncmp(method,"R",1) == 0) || (strncmp(method,"r",1) == 0) ){ 
		RoeInit();
	}
	else if( (strncmp(method,"H",1) == 0) || (strncmp(method,"h",1) == 0) ){
		HLLInit();
	}
}

// Redirect flux splitting function
Mat Space::splitFlux(int j){
	if((j == 0) || (j == (Sod->jd-1))){
		return fb;
	}
	else if( (strncmp(method,"S",1) == 0) || (strncmp(method,"s",1) == 0) ){ 
		return StegerWarmingFlux(j);
	}
	else if( (strncmp(method,"R",1) == 0) || (strncmp(method,"r",1) == 0) ){ 
		return RoeFlux(j);
	}
	else if( (strncmp(method,"H",1) == 0) || (strncmp(method,"h",1) == 0) ){
		return HLLFlux(j);
	}
	else{
		cout << "ERROR: Choose an available flux splitting scheme--";
		cout << "StegerWarming, Roe, or HLL." << endl;
		exit(-1);
	}
}
//###################################################################
//##################### STEGER WARMING ##############################
//###################################################################
void Space::StegerWarmingInit(void){
	// State
	q. size(dof,1);
	qp.size(dof,1);
	qm.size(dof,1);
	// Jacobian
	T. size(dof,dof);
	L. size(dof,dof);
	L. zeros();
	Ti.size(dof,dof);
	A.size(dof,dof);
	Ap.size(dof,dof);
	Am.size(dof,dof);
	// Flux
	fp.size(dof,1);
	fm.size(dof,1);
	fb.size(dof,1);
	fb.zeros();
}

Mat Space::StegerWarmingFlux(int j){
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
	return 0.5*(fp - fm - ( Ap*qp - 2*A*q + Am*qm ));
}
//###################################################################
//######################### ROE METHOD ##############################
//###################################################################
void Space::RoeInit(void){
	// State
	q. size(dof,1);
	qp.size(dof,1);
	qm.size(dof,1);
	qroe.size(dof,1);
	// Jacobian
	T. size(dof,dof);
	L. size(dof,dof);
	L. zeros();
	Ti.size(dof,dof);
	Ap.size(dof,dof);
	Am.size(dof,dof);
	// Flux
	fp.size(dof,1);
	fm.size(dof,1);
	fb.size(dof,1);
	fb.zeros();
}

void Space::RoeAverage(double * ql, double * qr){
	sql = sqrt(ql[0]); sqr = sqrt(qr[0]);
	qroe(0,0) = sql*sqr;
	qroe(1,0) = qroe(0,0)*(sql*vel(ql) + sqr*vel(qr))/(sql + sqr);
	qroe(2,0) = qroe(0,0)*(sql*nrg(ql) + sqr*nrg(qr))/(sql + sqr);
}

Mat Space::RoeFlux(int j){
	// Space
	q  &= Sod->Q[ j ];
	qp &= Sod->Q[j+1];
	qm &= Sod->Q[j-1];
	// Jacobian
	// Left Interface
	RoeAverage(qm[0], q[0]);
	Am = absA(qroe[0]);
	// Right interface
	RoeAverage(q[0], qp[0]);
	Ap = absA(qroe[0]);
	// Flux
	fp &= Sod->F[j+1];
	fm &= Sod->F[j-1];
	return 0.5*(fp - fm - ( Ap*(qp-q) - Am*(q-qm) ));
}
//###################################################################
//######################### HLL METHOD ##############################
//###################################################################
void Space::HLLInit(void){
	// State
	qp.size(dof,1);
	qm.size(dof,1);
	// Flux
	fp.size(dof,1);
	fm.size(dof,1);
	fl.size(dof,1);
	fr.size(dof,1);
	fb.size(dof,1);
	fb.zeros();
}

Mat Space::HLLInterFlux(int l, int r){
	// State
	qm &= Sod->Q[l];
	qp &= Sod->Q[r];
	// Flux
	fl &= Sod->F[l];
	fr &= Sod->F[r];
	// Waves
	Sl = min(vel(qm[0])-sos(qm[0]), vel(qp[0])-sos(qp[0]));
	Sr = min(vel(qm[0])+sos(qm[0]), vel(qp[0])+sos(qp[0]));
	if(Sl > 0){
		return fl;
	}
	else if(Sr < 0){
		return fr;
	}
	else{
		return (fl*Sr - fr*Sl + Sl*Sr*(qp - qm))/(Sr - Sl);
	}
}

Mat Space::HLLFlux(int j){
	// Left interface
	fm = HLLInterFlux(j-1, j);
	// Right interface
	fp = HLLInterFlux(j, j+1);
	return fp - fm;
}
//###################################################################
//###################################################################
//###################################################################
// Decomposed Flux Jacobian
Mat Space::absA(double * q){
    double u = vel(q); // useful params
    double a = sos(q);
    double h = nth(q); //nth(q)
    //////////////////// T
    T(0,0) = 1;
    T(0,1) = 1;
    T(0,2) = 1;
    T(1,0) = u-a;
    T(1,1) = u;
    T(1,2) = u+a;
    T(2,0) = h-u*a;
    T(2,1) = 0.5*u*u;
    T(2,2) = h+u*a;
    /////////////////// Lambda
    L(0,0) = abs(u-a);
    L(1,1) = u;
    L(2,2) = abs(u+a);
    /////////////////// Ti
    double sml = (Sod->gam-1)/(a*a);
    Ti(0,0) =  (u/(4*a))*(2+(Sod->gam-1)*u/a);
    Ti(0,1) = -(1/(2*a))*(1+(Sod->gam-1)*u/a);
    Ti(0,2) =  sml/2;
    Ti(1,0) =  1-sml*u*u/2;
    Ti(1,1) =  sml*u;
    Ti(1,2) = -sml;
    Ti(2,0) = -(u/(4*a))*(2-(Sod->gam-1)*u/a);
    Ti(2,1) =  (1/(2*a))*(1-(Sod->gam-1)*u/a);
    Ti(2,2) =  sml/2;
    return T*L*Ti;
}

// functions for deriving flow props from state
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
    return (Sod->gam-1)*(q[2] - 0.5*q[1]*q[1]/q[0]);
}

double Space::sos(double * q){
    return sqrt(Sod->gam*bar(q)/rho(q));
}

double Space::nth(double * q){
    return nrg(q) + bar(q)/rho(q);
}
