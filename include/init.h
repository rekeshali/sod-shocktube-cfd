#ifndef SPACEBASE
#define SPACEBASE

class State {
		int jd;
		double * q; // state and eigenvalue vars for all j
		double gam, R;
		static int dims;
// 		void updateFJVars(void);
	public:
		State(int, double, double);
		void init(double *, double *); // fill grid
		// functions for fetching state
		double  q1(int); // rho
		double  q2(int); // rho*u
		double  q3(int); // rho*e0
// 		// functions for fetching useful jacobian eigen vars
// 		double fj1(int); // u
// 		double fj2(int); // a
// 		double fj3(int); // h0 - ua
		// functions for deriving flow props from state
		double rho(int); // rho
		double vel(int); // u
		double nrg(int); // e0
		double bar(int); // P
		double sos(int); // a
		double nth(int); // h0
};

#endif
