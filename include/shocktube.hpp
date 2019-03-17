#ifndef SHOCKTUBE
#define SHOCKTUBE
#include "matrix.hpp"
class ShockTube {
		static int dof;
		void q2flx(double *, double *); // convert q to flux
		void ic2q(double *, double *); // convert ICs to qs
	public:
		int jd;
		Mat Q, F;
		double dx, L, gam, R;
		ShockTube(double, double, double, double);
		void fillTube(double *, double *); // fill state
		void updateFlux(void); // update fluxes
		// functions for deriving flow props from state
		double rho(double *); // rho
		double vel(double *); // u
		double nrg(double *); // e0
		double bar(double *); // P
		double sos(double *); // a
		double nth(double *); // h0
};
#endif
