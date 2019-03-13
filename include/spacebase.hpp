#ifndef INIT
#define INIT

class Space {
		int jd;
		double *q, *f; // state and flux vectors
		double gam, R;
		static int dims;
		void updateFlux(void); // update fluxes with current state
// 		void updateFJVars(void);
	public:
		Space(int, double, double);
		void init(double *, double *); // fill state and flux grid with IC's
		// functions for fetching state
		double  q1(int); // rho
		double  q2(int); // rho*u
		double  q3(int); // rho*e0
		// functions for fetching flux
		double  f1(int);
		double  f2(int);
		double  f3(int);
		// functions for deriving flow props from state
		double rho(int); // rho
		double vel(int); // u
		double nrg(int); // e0
		double bar(int); // P
		double sos(int); // a
		double nth(int); // h0
};

#endif
