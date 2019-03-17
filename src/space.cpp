#include <cmath>
#include "matrix.hpp"
#include "state.hpp"
#include "space.hpp"

Space::Space(int a, int b, double c){
	jd = a; dof = b; dx = c;
	init();
}

void Space::init(){
	// State
	qn. size(dof,1); // new time
	qj. size(dof,1);
	qjp.size(dof,1);
	qjm.size(dof,1);
	qroe.size(dof,1);
	// Jacobian
	Aj. size(dof,dof);
	Ajp.size(dof,dof);
	Ajm.size(dof,dof);
	// Flux
	fjp.size(dof,1);
	fjm.size(dof,1);
}

void Space::StegerWarming(State & Q){
	Q.updateFlux();
	dt = 0.0005;
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
		fjp &= Q.F[j+1];
		fjm &= Q.F[j-1];
		// Local update
		qn = qj - (dt/(2*dx)) * (fjp - fjm - ( Ajp*qjp -2*Aj*qj + Ajm*qjm ));
		Q.updateFuture(j, qn); // Save local update
	}
	// Left boundary
	qn = Q[1];
	Q.updateFuture(0, qn);
	// Right boundary
	qn = Q[jd-2];
	Q.updateFuture(jd-1, qn);
	// Replace old state
	Q.updatePresent();
}

void Space::Roe(State & Q){
// 	Q.updateFlux();
// 	for(int j = 1; j < jd - 1; j++){
// 		// localize large matrices by point
// 		// State
// 		qj  &= Q[ j ];
// 		qjp &= Q[j+1];
// 		qjm &= Q[j-1];
// 		qroe(0,0) = sqrt(qjp(0,0)*qjm(0,0));
// 		qroe(1,0) = qroe(0,0)*( sqrt(qjp(0,0))*qjp(1,0)/qjp(0,0) + 
// 								sqrt(qjm(0,0))*qjm(1,0)/qjm(0,0) )/
// 								(sqrt(qjm(0,0)) + sqrt(qjp(0,0)));
// 
// 		qroe(2,0) = qroe(1,0)*( sqrt(qjp(0,0))*qjp(2,0)/qjp(1,0) + 
// 								sqrt(qjm(0,0))*qjm(2,0)/qjm(1,0) )/
// 								(sqrt(qjm(0,0)) + sqrt(qjp(0,0)));
// 		// Jacobian
// 		Aj  = Q.absA(qroe[0]);
// 		// Flux
// 		fjp &= F[j+1];
// 		fjm &= F[j-1];
// 		// Local update
// 		qn = qj - (dt/(2*dx)) * (fjp - fjm - Aj*( qjp - qjm ));
// 		Q.updateFuture(j, qn); // Save local update
// 	}
	// Left boundary
	qn = Q[1];
	Q.updateFuture(0, qn);
	// Right boundary
	qn = Q[jd-2];
	Q.updateFuture(jd-1, qn);
	// Replace old state
	Q.updatePresent();
}
