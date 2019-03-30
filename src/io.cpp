#include <fstream>
#include "shocktube.hpp"
#include "io.hpp"
using namespace std;

STDIO::STDIO(const char * fname){
	stateFile.open(fname);
	jd = 0; frames = 0;
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
	frames++;
}

void STDIO::close(double cputime){
	stateFile << "# " << frames << " " << jd << " " << cputime << endl;
}

