#include "matrix.hpp"
#include "state.hpp"
#include "solver.hpp"

Solver::Solver(int a, int b, double c, double d){
	jd = a; dof = b; dx = c; dt = d;
	init();
}

void Solver::init(){
	// State
	qn. size(dof,1); // new time
	qj. size(dof,1);
	qjp.size(dof,1);
	qjm.size(dof,1);
	// Jacobian
	Aj. size(dof,dof);
	Ajp.size(dof,dof);
	Ajm.size(dof,dof);
	// Flux
	fjp.size(dof,1);
	fjm.size(dof,1);
}

void Solver::FVS(State & Q){
	Mat F = Q.flux();
	for(int j = 1; j < jd - 1; j++){
		// localize large matrices by point
		// State
		qj  &= Q[ j ];
		qjp &= Q[j+1];
		qjm &= Q[j-1];
		// Jacobian
		Aj  = Q.absA(Q[ j ]);
		Ajp = Q.absA(Q[j+1]);
		Ajm = Q.absA(Q[j-1]);
		// Flux
		fjp &= F[j+1];
		fjm &= F[j-1];
		// Local update
		qn = qj - (dt/(2*dx)) * (fjp - fjm - ( Ajp*qjp -2*Aj*qj + Ajm*qjm ));
		Q.save(j, qn); // Save local update
	}
	// Left boundary
	qn = Q[1];
	Q.save(0, qn);
	// Right boundary
	qn = Q[jd-2];
	Q.save(jd-1, qn);
	// Replace old state
	Q.march();
}
