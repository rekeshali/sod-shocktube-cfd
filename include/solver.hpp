#ifndef SOLVER
#define SOLVER
class Solver {
	protected:
		Mat Qn, F;
		Mat qn, q, f;
		int j, jd, dof;
		double L, time;
		double dx, dt, ucmax, CFL;
	public:
		Solver(int, double, double, double);
		void timeMarch(State&);
		double timeElapsed(void);
		void updateDt(void);
		void updateFuture(void);
		void updatePresent(void);

};
#endif
