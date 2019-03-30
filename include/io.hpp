#ifndef IO_CLASS
#define IO_CLASS
#include <fstream>
#include "shocktube.hpp"

class STDIO {
	protected:
		std::ofstream inputFile;
		std::ofstream stateFile;
	public:
		int j, jd, frames;
		STDIO(const char *);
		void stateToFile(ShockTube&);
		void close(double);
};
#endif
