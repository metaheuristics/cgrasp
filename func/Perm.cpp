#include <stdio.h>
#include <math.h>

#include "Perm.h"
#include "Util.h"

Perm::Perm(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Perm::~Perm(){

}

void Perm::setFnEvals(int c){
	cont = c;	
}

int Perm::getFnEvals(){
	return cont;	
}

real Perm::getGap(){
	return (bestValue - minValue);
}

bool Perm::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Perm::calc(real *x){
	cont++;	
	real value = 0, beta = 0.5, sum = 0;
	int k, i;

	for (k=0;k<4;k++){
		sum = 0;
		for (i=0;i<4;i++)
			sum += (pow((real) i+1,(real) k+1) + beta)*(pow(x[i]/(i+1),k+1) - 1);

	      value += pow(sum,2);
	}

	return value;
}


real Perm::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Perm::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
