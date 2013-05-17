#include <stdio.h>
#include <math.h>

#include "Griewank.h"
#include "Util.h"

Griewank::Griewank(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Griewank::~Griewank(){

}

void Griewank::setFnEvals(int c){
	cont = c;	
}

int Griewank::getFnEvals(){
	return cont;	
}

real Griewank::getGap(){
	return (bestValue - minValue);
}

bool Griewank::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Griewank::calc(real *x){
	cont++;
	real value = 0, sum = 0, prod = 1;
	int i;

	for (i =0; i<n; i++){		sum += pow(x[i],2)/4000;
		prod *= cos(x[i]/sqrt((real) i + 1));
	}
	value = sum - prod + 1;

	return value;
}


real Griewank::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Griewank::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
