#ifndef SPACE
#define SPACE
#include <fstream>
#include "matrix.hpp"
class Space {
		int jd;
		double * qnew, * qnow, * flux; // new state, state, flux
		double gam, R;
		static int dims;
		Mat qnj, qj, fj;
		void updateFlux(void); // update fluxes with current state
		void initA(void);
// 		void updateFJVars(void);
	public:
		Space(int, double, double);
		void init(double *, double *); // fill state and flux grid with IC's
		void updateFuture(int, Mat);
		void updateBounds(double);
		void updatePresent(void);
		void print(std::ofstream&);
		Mat T, Lam, Tinv;
// 		double * absA(int);
		Mat qn(int); // pointers to data in space
		Mat q(int);
		Mat f(int);
		Mat A(int);
// 		double *q(int); // points to q1 at j 
// 		double *f(int); // points to f1 at j
// 		double *A(int); // points to jacobian for j
		// functions for fetching state
		double  q1(int); // rho
		double  q2(int); // rho*u
		double  q3(int); // rho*e0
		// functions for fetching flux
		double  f1(int); // rho*u
		double  f2(int); // rho*u^2 + P
		double  f3(int); // rho*u*h0
		// functions for deriving flow props from state
		double rho(int); // rho
		double vel(int); // u
		double nrg(int); // e0
		double bar(int); // P
		double sos(int); // a
		double nth(int); // h0
};
#endif
