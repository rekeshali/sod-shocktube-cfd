#ifndef MATRIX
#define MATRIX
class Mat{
	protected:
		int row, col;
		double * data;
	public:
		Mat();
		Mat(int, int);
		void size(int,int);
		void zeros(void);
		double r(void);
		double c(void);
		void p(void);
		void print(void);
		Mat t(void);
		void trans(void);
		Mat operator= (const Mat&);
		Mat operator+ (const Mat&);
		Mat operator- (const Mat&);
		Mat operator* (const Mat&);
		Mat operator= (double*);
		Mat operator&= (double*);
		Mat operator- () const;
		Mat operator* (double);
		Mat operator/ (double);
		Mat operator~ (void);
		double * operator[] (unsigned);
		double & operator() (unsigned, unsigned);
		double operator() (unsigned, unsigned) const;
};
Mat operator* (double, Mat);

#endif

