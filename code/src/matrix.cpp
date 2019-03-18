#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "matrix.hpp"
using namespace std;
// Construction //
Mat::Mat(){
	size(0,0);
}

Mat::Mat(int a, int b){
	size(a, b);
}

void Mat::size(int a, int b){
	row = a;
	col = b;
	data = (double *) malloc(row*col*sizeof(double));
}

// Basic features //
double Mat::r(){
	return row;
}

double Mat::c(){
	return col;
}

void Mat::p(){
	print();
}

void Mat::print(){
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			printf("%5.2f ", data[i*col + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Mat::zeros(){
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			data[i*col + j] = 0;
		}
	}
}

Mat Mat::t(){
	return ~*this;
}

void Mat::trans(){
	if(col == 1 || row == 1){
	}else{
		double * ndata = (double *) malloc(row*col*sizeof(double));
		for(int i = 0; i < row; i ++){
			for(int j = 0; j < col; j ++){
				ndata[j*row + i] = data[i*col +j];
			}
		}
		free(data);
		data = ndata;
	}
	int buf = row;
	row = col;
	col = buf;
}

// Operator Overloading //
// Matrix return
Mat Mat::operator= (const Mat& param){ // Matrix = Matrix overwrite
	if((row == param.row) && (col == param.col)){
		memcpy(data, param.data, row*col*sizeof(double));
	}else{
		free(data);
		row = param.row; col = param.col;
		data = (double *) malloc(row*col*sizeof(double));
		memcpy(data, param.data, row*col*sizeof(double));
	}
	return *this;
}

Mat Mat::operator= (double* param){ // copies data from operated matrix
	memcpy(data, param, row*col*sizeof(double));
	return *this;
}

Mat Mat::operator&= (double* param){ // points data to operated matrix
	data = param;
	return *this;
}

Mat Mat::operator+ (const Mat& param){
	if((row != param.row) && (col != param.col)){
		cout << "ERROR: Dimension mismatch during matrix addition." << endl;
		exit(-1);
	}
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j] + param.data[i*col+j];
		}
	}
	return temp;	
}

Mat Mat::operator- (const Mat& param){
	if((row != param.row) && (col != param.col)){
		cout << "ERROR: Dimension mismatch during matrix subtraction." << endl;
		exit(-1);
	}
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j] - param.data[i*col+j];
		}
	}
	return temp;
}

Mat Mat::operator* (const Mat& param){
	if(col != param.row){
		cout << "ERROR: Dimension mismatch during matrix multiply." << endl;
		exit(-1);
	}
	Mat temp(row, param.col);
	temp.zeros();
	for(int i = 0; i < temp.row; i ++){
		for(int j = 0; j < temp.col; j ++){
			for(int k = 0; k < param.row; k++){
				temp.data[i*temp.col + j] += data[i*col + k]*param.data[k*param.col + j];
			}
		}
	}
	return temp;	
}

Mat Mat::operator~ (){
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j];
		}
	}
	temp.trans();
	return temp;
}

Mat Mat::operator* (double param){
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j]*param;
		}
	}
	return temp;	
}

Mat Mat::operator/ (const double param){
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j]/param;
		}
	}
	return temp;	
}


Mat operator* (double param, Mat x){
	Mat temp(x.r(), x.c());
	return x*param;
}

Mat Mat::operator- () const{ // Negate entries
	Mat temp(row,col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp(i,j) = -this->data[i*col+j];
		}
	}
	return temp;
}
// Value returns
double * Mat::operator[] (unsigned i){
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
		exit(-1);
	}
	return data + i*col;
}

double & Mat::operator() (unsigned i, unsigned j){
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
		exit(-1);
	}else if(j >= col){
		cout << "ERROR: Second index exceeds bound." << endl;
		exit(-1);
	}
	return data[i*col + j];
}

double Mat::operator() (unsigned i, unsigned j) const{
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
		exit(-1);
	}else if(j >= col){
		cout << "ERROR: Second index exceeds bound." << endl;
		exit(-1);
	}
	return data[i*col + j];
}
