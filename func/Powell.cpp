#include <stdio.h>
#include <math.h>

#include "Powell.h"
#include "Util.h"

Powell::Powell(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Powell::~Powell(){

}

void Powell::setFnEvals(int c){
	cont = c;	
}

int Powell::getFnEvals(){
	return cont;	
}

real Powell::getGap(){
	return (bestValue - minValue);
}

bool Powell::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Powell::calc(real *x){
	cont++;
	real value;

	value = pow(x[0] + 10*x[1],2) + 5*pow(x[2]-x[3],2) + pow(x[1] - 2*x[2],4) + 10*pow(x[0]-x[3],4);
	return value;
}


real Powell::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Powell::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
