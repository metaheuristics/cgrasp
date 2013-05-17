#include <stdio.h>
#include <math.h>

#include "Rastrigin.h"
#include "Util.h"

Rastrigin::Rastrigin(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Rastrigin::~Rastrigin(){

}

void Rastrigin::setFnEvals(int c){
	cont = c;	
}

int Rastrigin::getFnEvals(){
	return cont;	
}

real Rastrigin::getGap(){
	return (bestValue - minValue);
}

bool Rastrigin::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Rastrigin::calc(real *x){
	cont++;
	real value = 0, pi=3.14159265;
	int i;

	value = 10*n;	for (i=0; i<n; i++)
		value += (pow(x[i],2) - 10*cos(2*pi*x[i]));

	return value;
}


real Rastrigin::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Rastrigin::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
