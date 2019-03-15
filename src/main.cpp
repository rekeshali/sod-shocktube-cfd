#include <iostream>
#include <fstream>
#include <cmath>
#include "matrix.hpp"
#include "spacebase.hpp"
using namespace std;

int main(){
	double dx = 0.005;
	double dt = 0.0001;
	double L = 1;
	double T = 0.2;
	double R = 1;
	double gam = 1.4;
	double CFL = 0.5;

	int jd = int(L/dx);
	int td = int(T/dt);

	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};

	Space sod(jd, gam, R);
	sod.init(ICL, ICR);

	ofstream myfile ("out");
	myfile << td+1 << " " << jd << endl;
	sod.print(myfile);
	int jj, tt, ti;
	jj = 101;
	tt = 10;
	ti = 1;
// 	sod.updateBounds();
	for(int t = 0; t < td; t++){
		if(t%ti == 0 && t < tt){
			cout << "Time=" << t << endl;
			cout << "states" << endl;
			sod.qn(jj).print();
			sod.q(jj).print();
			cout << "fluxes" << endl;
			sod.f(jj).print();
			sod.f(jj-1).print();
			cout << "jacobian" << endl;
			sod.A(jj).print();
			sod.T.print();
			sod.Lam.print();
			sod.Tinv.print();
			cout << sod.vel(jj) << " " <<
				sod.sos(jj) << " " << 
				sod.nth(jj) << endl;
		}
		for(int j = 1; j < jd-1; j ++){
			sod.updateFuture(j, sod.q(j) - ((sod.f(j+1) - sod.f(j-1))/(2*dx) - 
				(sod.A(j+1)*sod.q(j+1) - sod.A(j)*sod.q(j)*2 + sod.A(j-1)*sod.q(j-1)/(2*dx)))*dt);
// 			sod.updateFuture(j, sod.q(j) - (sod.f(j) - sod.f(j-1))*(dt/dx));
			if(t%ti == 0 && t < tt){
				if(j == jj){
					cout << "After time step:" << endl;
					sod.qn(j).print();
					sod.q(j).print();
					(sod.q(j) - (sod.f(j) - sod.f(j-1))*(dt/dx)).print();
				}	
			}
		}
		sod.updateBounds(dt/(2*dx));
		sod.updatePresent();
		if(t%ti == 0 && t < tt){
			cout << "After update:" << endl;
			sod.qn(jj).print();
			sod.q(jj).print();
			(sod.q(jj) - (sod.f(jj) - sod.f(jj-1))*(dt/dx)).print();
		}
		sod.print(myfile);
	}
	myfile.close();
// 	for(int j = 0; j < jd; j++){
// 		cout << j << " " << q.rho(j) << " " << q.vel(j) << " " << q.bar(j) << endl;
// 	}
	return 0;
}
