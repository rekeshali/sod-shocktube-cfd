#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "matrix.hpp"
using namespace std;

Mat::Mat(){
}

Mat::Mat(int a, int b){
	init(a, b);
}

void Mat::init(int a, int b){
	row = a;
	col = b;
	data = (double *) malloc(row*col*sizeof(double));
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

void Mat::transpose(){
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

Mat Mat::operator= (const Mat& param){
	data = param.data;
	return *this;
}

Mat Mat::operator+ (const Mat& param){
	Mat temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			temp.data[i*col+j] = data[i*col+j] + param.data[i*col+j];
		}
	}
	return temp;	
}

Mat Mat::operator- (const Mat& param){
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
	temp.transpose();
	return temp;
}

Mat Mat::operator* (const double param){
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

double * Mat::operator[] (unsigned i){
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
	}
	return data + i*col;
}

double & Mat::operator() (unsigned i, unsigned j){
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
	}else if(j >= col){
		cout << "ERROR: Second index exceeds bound." << endl;
	}
	return data[i*col + j];
}

double Mat::operator() (unsigned i, unsigned j) const{
	if(i >= row){
		cout << "ERROR: First index exceeds bound." << endl;
	}else if(j >= col){
		cout << "ERROR: Second index exceeds bound." << endl;
	}
	return data[i*col + j];
}
