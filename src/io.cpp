#include <iostream>
#include <fstream>
#include "shocktube.hpp"
#include "io.hpp"
using namespace std;

STDIO::STDIO(const char * fname){
	stateFile.open(fname);
	jd = 0; td = 0;
}

void STDIO::stateToFile(ShockTube& Sod){
	if(jd == 0){
		jd = Sod.Q.r();
	}
	for(j = 0; j < jd; j++){
		stateFile << Sod.rho(Sod.Q[j]) << " ";
		stateFile << Sod.vel(Sod.Q[j]) << " ";
		stateFile << Sod.bar(Sod.Q[j]) << endl;
	}
	td++;
}

void STDIO::close(){
	stateFile << td << " " << jd << endl;
}

