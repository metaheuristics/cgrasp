#include <stdio.h>
#include <math.h>

#include "Schwefel.h"
#include "Util.h"

Schwefel::Schwefel(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Schwefel::~Schwefel(){

}

void Schwefel::setFnEvals(int c){
	cont = c;	
}

int Schwefel::getFnEvals(){
	return cont;	
}

real Schwefel::getGap(){
	return (bestValue - minValue);
}

bool Schwefel::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Schwefel::calc(real *x){
	cont++;
	real value = 0;
	int i;

	value = 418.9829*n;
	for (i=0;i<n;i++)
		value += -1*x[i]*sin(sqrt(fabs(x[i])));

	return value;
}


real Schwefel::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Schwefel::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
