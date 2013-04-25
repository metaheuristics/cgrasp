#include <stdio.h>
#include <math.h>
#include "SumSquares.h"

SumSquares::SumSquares(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

SumSquares::~SumSquares(){

}

void SumSquares::setFnEvals(int c){
	cont = c;	
}

int SumSquares::getFnEvals(){
	return cont;	
}

double SumSquares::getGap(){
	return (bestValue - minValue);
}


bool SumSquares::isNearOptimum(double fBest){
	double deltaValue =	fabs(fBest - minValue);
	double equation;
	
	equation = fabs(minValue)*0.0001 + 0.000001;	
	//equation = fabs(bestValue)*0.0001 + 0.01;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

double SumSquares::calc(double *x){
	double som1 = 0.0;
	double fx = 0.0; 
	cont++;
	
	for (int i = 0; i < n; i++){		som1 += (i+1)*(x[i]*x[i]);
	}

	//printf("Som1 = %lf - Som2 = %lf \n", som1, som2);
	fx = som1;
	return fx;
}

double SumSquares::calc2(ap::real_1d_array x){
	double som1 = 0.0;
	double fx = 0.0; 
	cont++;
	
	for (int i = 0; i < n; i++){		som1 += (i+1)*(x(i+1)*x(i+1));
	}

	//printf("Som1 = %lf - Som2 = %lf \n", som1, som2);
	fx = som1;
	return fx;
}


void SumSquares::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){
	contGrad++;  
	int i;

	for (i = 0; i < n; i++)
		g(i+1) = 2*(i+1)*x(i+1); 

}
