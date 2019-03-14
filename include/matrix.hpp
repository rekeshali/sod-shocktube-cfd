#ifndef MATRIX
#define MATRIX
class Mat{
		int row, col;
	public:
		Mat();
		Mat(int, int);
		double * data;
		void init(int,int);
		void print(void);
		void zeros(void);
		void transpose(void);
		Mat operator= (const Mat&);
		Mat operator+ (const Mat&);
		Mat operator- (const Mat&);
		Mat operator* (const Mat&);
		Mat operator* (const double);
		Mat operator/ (const double);
		Mat operator~ (void);
		double * operator[] (unsigned);
		double & operator() (unsigned, unsigned);
		double operator() (unsigned, unsigned) const;
};
#endif

