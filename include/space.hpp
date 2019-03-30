#ifndef SPACE
#define SPACE
#include "matrix.hpp"
#include "shocktube.hpp"
class Space {
	protected:
		ShockTube * Sod;
		const char * method;
		static int dof;
		Mat q, qp, qm;
		Mat A, Ap, Am;
		Mat T, L, Ti;
		Mat f, fp, fm, fb;
		// Vars for Roe average
		Mat qroe;
		double sql, sqr;
		// Vars for HLL
		Mat fl, fr;
		double Sl, Sr;
	public:
		void spatialScheme(ShockTube&, const char *);
		Mat absA(double *);
		// All purpose flux splitter calls others
		Mat splitFlux(int);
		// StegerWarming
		void StegerWarmingInit(void);
		Mat StegerWarmingFlux(int);
		// Roe Method
		void RoeInit(void);
		void RoeAverage(double *, double *);
		Mat RoeFlux(int);
		// HLL Method
		void HLLInit(void);
		Mat HLLInterFlux(int, int);
		Mat HLLFlux(int);
	    // functions for deriving flow props from state
        double rho(double *); // rho
        double vel(double *); // u
        double nrg(double *); // e0
        double bar(double *); // P
        double sos(double *); // a
        double nth(double *); // h0
};
#endif
