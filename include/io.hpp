#ifndef IO_CLASS
#define IO_CLASS
#include <fstream>
#include "shocktube.hpp"

class STDIO {
	protected:
		int j, jd, td;
		std::ofstream inputFile;
		std::ofstream stateFile;
	public:
		STDIO(const char *);
		void stateToFile(ShockTube&);
		void close(void);
};
#endif
