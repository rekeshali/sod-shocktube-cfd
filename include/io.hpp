#ifndef IO_CLASS
#define IO_CLASS
#include <fstream>
#include "state.hpp"

class STDIO {
	protected:
		int j, jd, td;
		std::ofstream inputFile;
		std::ofstream stateFile;
	public:
		STDIO(const char *);
		void stateToFile(State&);
		void close(void);
};
#endif
