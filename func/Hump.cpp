#include <stdio.h>
#include <math.h>

#include "Hump.h"
#include "Util.h"

Hump::Hump(int n){
	cont = 0;
	this->n = n;
	//minValue = -1.03162801;
	minValue = 0.0;
}

Hump::~Hump(){

}

void Hump::setFnEvals(int c){
	cont = c;	
}

int Hump::getFnEvals(){
	return cont;	
}

real Hump::getGap(){
	return (bestValue - minValue);
}

bool Hump::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = minValue*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Hump::calc(real *x){
	cont++;  
	real value;

	//y=1.0316285+4*x(1)^2-2.1*x(1)^4+x(1)^6/3+x(1)*x(2)-4*x(2)^2+4*x(2)^4;

	//value = (4 - 2.1*pow(x[0],2) + pow(x[0],4)/3)*pow(x[0],2) + x[0]*x[1] + (-4 + 4*pow(x[1],2))*pow(x[1],2);
	value = 1.0316285 + 4.0*pow(x[0],2) -2.1*pow(x[0], 4)+ pow(x[0],6)/3 + x[0]*x[1] - 4*pow(x[1], 2) + 4*pow(x[1],4);	
	
	return value;
}


real Hump::calc2(ap::real_1d_array x){
	real y = 0.0;	
	return y;

}


void Hump::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
