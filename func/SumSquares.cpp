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

real SumSquares::getGap(){
	return (bestValue - minValue);
}


bool SumSquares::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = fabs(minValue)*0.0001 + 0.000001;	
	//equation = fabs(bestValue)*0.0001 + 0.01;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real SumSquares::calc(real *x){
	real som1 = 0.0;
	real fx = 0.0; 
	cont++;
	
	for (int i = 0; i < n; i++){		som1 += (i+1)*(x[i]*x[i]);
	}

	//printf("Som1 = %lf - Som2 = %lf \n", som1, som2);
	fx = som1;
	return fx;
}

real SumSquares::calc2(ap::real_1d_array x){
	real som1 = 0.0;
	real fx = 0.0; 
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
