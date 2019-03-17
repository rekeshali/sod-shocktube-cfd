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
		Mat fp, fm;
		double gam;
	public:
		void spatialScheme(ShockTube&, const char *);
		Mat absA(double *);
		// All purpose flux splitter calls others
		Mat splitFlux(int);
		// StegerWarming
		Mat StegerWarming(int);
	    // functions for deriving flow props from state
        double rho(double *); // rho
        double vel(double *); // u
        double nrg(double *); // e0
        double bar(double *); // P
        double sos(double *); // a
        double nth(double *); // h0
};
#endif

