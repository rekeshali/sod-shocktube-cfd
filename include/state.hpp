#ifndef SPACE
#define SPACE
#include <fstream>
#include "matrix.hpp"
class State: public Mat {
	friend class Mat;
		int jd, dof;
		double gam, R;
		Mat Qn, T, Lam, Ti;
		void q2flx(double *, double *); // convert q to flux
		void ic2q(double *, double *); // convert ICs to qs
	public:
		Mat F;
		State(int, int, double, double);
		void init(double *, double *); // fill state
		void updateFlux(void); // update fluxes
		void updateFuture(int, Mat);
		void updateBounds(double);
		void updatePresent(void);
		void print(std::ofstream&);
		Mat  absA(double *);

		// functions for fetching state
// 		double  q1(int); // rho
// 		double  q2(int); // rho*u
// 		double  q3(int); // rho*e0
// 		// functions for fetching flux
// 		double  f1(int); // rho*u
// 		double  f2(int); // rho*u^2 + P
// 		double  f3(int); // rho*u*h0
// 		// functions for deriving flow props from state
		double rho(double *); // rho
		double vel(double *); // u
		double nrg(double *); // e0
		double bar(double *); // P
		double sos(double *); // a
		double nth(double *); // h0
};
#endif
