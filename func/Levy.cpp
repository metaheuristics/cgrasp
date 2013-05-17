#include <stdio.h>
#include <math.h>

#include "Levy.h"
#include "Util.h"

Levy::Levy(int n){
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Levy::~Levy(){

}

void Levy::setFnEvals(int c){
	cont = c;	
}

int Levy::getFnEvals(){
	return cont;	
}

real Levy::getGap(){
	return (bestValue - minValue);
}

bool Levy::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Levy::calc(real *x){
	cont++;	
	real value = 0, pi=3.14159265;
	real yi;
	int i;

	yi = 1 + (x[0] - 1)/4;
	value += pow(sin(pi*yi),2);

	for (i=1;i<29;i++){
		yi = 1 + (x[i] - 1)/4;
		value += pow(yi - 1,2)*(1 + 10*pow(sin(pi*yi + 1),2));
    }

	yi = 1 + (x[29] - 1)/4;
	value += pow(yi - 1,2)*(1 + 10*pow(sin(2*pi*yi),2));

	return value;
}


real Levy::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Levy::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
