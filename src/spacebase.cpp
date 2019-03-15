#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "matrix.hpp"
#include "spacebase.hpp"
using namespace std;
int Space::dims = 3;

Space::Space(int a, double b, double c){
	// class construction
	jd  = a; gam = b; R	= c;
}

void Space::init(double * L, double * R){
	// initialization of state
	qnew = (double *) malloc(jd*dims*sizeof(double));
	qnow = (double *) malloc(jd*dims*sizeof(double));
	flux = (double *) malloc(jd*dims*sizeof(double));
	qnj.init(3,1); qj.init(3,1); fj.init(3,1);
	for(int j = 0; j < jd; j++){
		if(j <= jd/2){
			qnow[j*dims + 0] = L[0];
			qnow[j*dims + 1] = L[0]*L[1];
			qnow[j*dims + 2] = L[2]/(gam-1) + 0.5*L[0]*L[1]*L[1];
		}else{
			qnow[j*dims + 0] = R[0];
			qnow[j*dims + 1] = R[0]*R[1];
			qnow[j*dims + 2] = R[2]/(gam-1) + 0.5*R[0]*R[1]*R[2];
		}
	}
	updateFlux();
	initA();
}

void Space::updateFuture(int j, Mat qn){
	qnew[j*dims + 0] = qn(0,0);
	qnew[j*dims + 1] = qn(1,0);
	qnew[j*dims + 2] = qn(2,0);

}

void Space::updateBounds(double alpha){
// 	memcpy(qnew, qnow, jd*dims*sizeof(double));
	int jl; int jr = jd-1;
	updateFuture(jl, q(jl) - (f(jl+1) - (A(jl+1)*q(jl+1) - A(jl)*q(jl)*2))*alpha);
	updateFuture(jr, q(jr) - (f(jr-1)*(-1) - (A(jr-1)*q(jr-1) - A(jr)*q(jr)*2))*alpha);
// 	qnew[0] = qnew[dims + 0];
// 	qnew[1] = qnew[dims + 1];
// 	qnew[2] = qnew[dims + 2];
// 	qnew[(jd-1)*dims + 0] = qnew[(jd-2)*dims + 0];
// 	qnew[(jd-1)*dims + 1] = qnew[(jd-2)*dims + 1];
// 	qnew[(jd-1)*dims + 2] = qnew[(jd-2)*dims + 2];
}

void Space::updatePresent(){
	memcpy(qnow, qnew, jd*dims*sizeof(double));
	updateFlux();
}

void Space::updateFlux(){
	for(int j = 0; j < jd; j++){
		flux[j*dims + 0] = q2(j);
		flux[j*dims + 1] = q2(j)*q2(j)/q1(j) + (gam-1)*(q3(j) - q2(j)*q2(j)/(2*q1(j)));
		flux[j*dims + 2] = q2(j)*q3(j)/q1(j) + (gam-1)*(q2(j)*q3(j)/q1(j) - q2(j)*q2(j)*q2(j)/(2*q1(j)*q1(j)));
	}

}

Mat Space::qn(int j){
	qnj.data = qnew + j*dims;
	return qnj;
}

Mat Space::q(int j){
	qj.data = qnow + j*dims;
	return qj;
}

Mat Space::f(int j){
	fj.data = flux + j*dims;
	return fj;
}
// Decomposed Flux Jacobian stuff
void Space::initA(){
	T.init(dims, dims);
	Lam.init(dims,dims);
	Lam.zeros();
	Tinv.init(dims,dims);
}

Mat Space::A(int j){
	double u = vel(j); // useful params
	double a = sos(j);
	double h = nth(j);
	// T
	T(0,0) = 1; T(0,1) = 1; T(0,2) = 1;
	T(1,0) = u-a; T(1,1) = u; T(1,2) = u+a;
	T(2,0) = h-u*a;	T(2,1) = 0.5*u*u; T(2,2) = h-u*a;
	// Lambda
	Lam(0,0) = abs(u-a); Lam(1,1) = u; Lam(2,2) = abs(u+a);
	// Tinv
	double sml = (gam-1)/(a*a);
	Tinv(0,0) =  (u/(4*a))*(2+(gam-1)*u/a); // begin construction
	Tinv(0,1) = -(1/(2*a))*(1+(gam-1)*u/a);
	Tinv(0,2) =  sml/2;
	Tinv(1,0) =  1-sml*u*u/2; 
	Tinv(1,1) =  sml*u; 
	Tinv(1,2) = -sml;
	Tinv(2,0) = -(u/(4*a))*(2-(gam-1)*u/a);
	Tinv(2,1) =  (1/(2*a))*(1-(gam-1)*u/a); 
	Tinv(2,2) =  sml/2;
// 	T.print(); Lam.print(); Tinv.print();
	return T*Lam*Tinv;
}

// double * Space::absA(int j){
// 	return qnow;	
// 
// }
// // pointers to flux and q at j
// double * Space::q(int j){
// 	return qnow + j*dims;
// }
// 
// double * Space::f(int j){
// 	return flux + j*dims;
// }
// getting state values
double Space::q1(int j){
	return qnow[j*dims + 0];
}

double Space::q2(int j){
	return qnow[j*dims + 1];
}

double Space::q3(int j){
	return qnow[j*dims + 2];
}
// getting flux values
double Space::f1(int j){
	return flux[j*dims + 0];
}

double Space::f2(int j){
	return flux[j*dims + 1];
}

double Space::f3(int j){
	return flux[j*dims + 2];
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

void Space::print(ofstream & out){
	for(int j = 0; j < jd; j++){
		out << q1(j) << " " <<
			   q2(j) << " " <<
			   q3(j) << " " <<
			   endl;
	}
}
