#include <stdio.h>
#include <math.h>

#include "Matyas.h"
#include "Util.h"

Matyas::Matyas(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Matyas::~Matyas(){

}

void Matyas::setFnEvals(int c){
	cont = c;	
}

int Matyas::getFnEvals(){
	return cont;	
}

real Matyas::getGap(){
	return (bestValue - minValue);
}

bool Matyas::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Matyas::calc(real *x){
	cont++;	
	real value = 0;

	value = 0.26*(pow(x[0],2) + pow(x[1],2)) - 0.48*x[0]*x[1];

	return value;
}


real Matyas::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Matyas::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
