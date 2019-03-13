#include <iostream>
#include <cmath>
#include "spacebase.hpp"
using namespace std;

int main(){
	double dx = 0.005;
	double L = 1;
	double T = 0.2;
	double R = 1;
	double gam = 1.4;
	double CFL = 0.5;

	int jd = int(L/dx);

	double ICL[3] = {1.0, 0.0, 1.0};
	double ICR[3] = {0.125, 0.0, 0.1};

	Space q(jd, gam, R);
	q.init(ICL, ICR);

// 	for(int j = 0; j < jd; j++){
// 		cout << j << " " << q.rho(j) << " " << q.vel(j) << " " << q.bar(j) << endl;
// 	}
	return 0;
}
