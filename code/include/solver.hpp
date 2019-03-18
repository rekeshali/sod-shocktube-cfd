#ifndef SOLVER
#define SOLVER
#include "matrix.hpp"
#include "shocktube.hpp"
#include "space.hpp"
class Solver {
	protected:
		Mat Qn;
		Mat qn, q, f;
		ShockTube * Sod;
		Space Spatial;
		int j, jd;
		static int dof;
		double L, time;
		double uc, ucmax;
		double dx, dt, CFL;
	public:
		Solver(ShockTube&, double, const char *);
		void timeMarch();
		double timeElapsed(void);
		void updateDt(void);
		void updateFuture(void);
		void updatePresent(void);
};
#endif
