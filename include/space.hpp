#ifndef SOLVER
#define SOLVER
#include "matrix.hpp"
class Space {
	protected:
		int jd, dof;
		double dx, dt;
		Mat qn;
		Mat qroe;
		Mat qj, qjp, qjm;
		Mat Aj, Ajp, Ajm;
		Mat fjp, fjm;
	public:
		Space(int, int, double);
		void init(void);
		void cfl(State&, double); 
		void StegerWarming(State&);
		void Roe(State&);
};
#endif
