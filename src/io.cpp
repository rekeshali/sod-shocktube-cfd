#include <iostream>
#include <fstream>
#include "state.hpp"
#include "io.hpp"
using namespace std;

STDIO::STDIO(const char * fname){
	stateFile.open(fname);
	jd = 0; td = 0;
}

void STDIO::stateToFile(State& Q){
	if(jd == 0){
		jd = Q.r();
	}
	for(j = 0; j < jd; j++){
		stateFile << Q(j,0) << " ";
		stateFile << Q(j,1) << " ";
		stateFile << Q(j,2) << endl;
	}
	td++;
}

void STDIO::close(){
	stateFile << td << " " << jd << endl;
}

