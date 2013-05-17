#include <stdio.h>
#include <math.h>

#include "Beale.h"
#include "Util.h"

Beale::Beale(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Beale::~Beale(){

}

void Beale::setFnEvals(int c){
	cont = c;	
}

int Beale::getFnEvals(){
	return cont;	
}

real Beale::getGap(){
	return (bestValue - minValue);
}

bool Beale::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Beale::calc(real *x){
	cont++;	
	real value,value1,value2,value3;

	value1 = pow(1.5 - x[0]*(1 -x[1]),2);
	value2 = pow(2.25 -x[0]*(1 - pow(x[1],2)),2);
	value3 = pow(2.625 - x[0]*(1 - pow(x[1],3)),2);
	value = value1 + value2 + value3;

	return value;
}


real Beale::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;
}


void Beale::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
