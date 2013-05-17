#include <stdio.h>
#include <math.h>

#include "PowerSum.h"
#include "Util.h"

PowerSum::PowerSum(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

PowerSum::~PowerSum(){

}

void PowerSum::setFnEvals(int c){
	cont = c;	
}

int PowerSum::getFnEvals(){
	return cont;	
}

real PowerSum::getGap(){
	return (bestValue - minValue);
}

bool PowerSum::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real PowerSum::calc(real *x){
	cont++;	
	real value = 0, sum = 0;
	int i, k;
	real b[4] = {8,18,44,114};

	for (k=0;k<4;k++){
		sum = 0;
		for (i=0;i<4;i++)
			sum += pow(x[i],k+1);
		value += pow(sum - b[k],2);
	}

	return value;
}


real PowerSum::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void PowerSum::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
