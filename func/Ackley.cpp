#include <stdio.h>
#include <math.h>

#include "Ackley.h"
#include "Util.h"

Ackley::Ackley(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Ackley::~Ackley(){

}

void Ackley::setFnEvals(int c){
	cont = c;	
}

int Ackley::getFnEvals(){
	return cont;	
}

real Ackley::getGap(){
	return (bestValue - minValue);
}

bool Ackley::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Ackley::calc(real *x){
	cont++;
	real value, sum1=0, sum2=0, pi=3.14159265;
	int i;
	real value1, value2, value3;

	for (i = 0; i < n; i++)
		sum1 += pow(x[i], (real) 2);

	for (i = 0; i < n; i++)
    	sum2 += cos(2 * pi * x[i]);
	
	value1 = -20*exp((real) (-0.2* (real) sqrt((real) sum1/n)));
	value2 = - exp((real) (sum2/n));
	value3 =  20 + exp((real) 1);
	
	value = value1 + value2 + value3;

	return value;
}


real Ackley::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Ackley::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
