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
		stateFile << Sod.Q(j,0) << " ";
		stateFile << Sod.Q(j,1) << " ";
		stateFile << Sod.Q(j,2) << endl;
	}
	td++;
}

void STDIO::close(){
	stateFile << td << " " << jd << endl;
}

