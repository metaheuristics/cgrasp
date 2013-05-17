#include <stdio.h>
#include <math.h>

#include "Easom.h"
#include "Util.h"

Easom::Easom(int n){
	cont = 0;
	this->n = n;
	minValue = -1.0;
}

Easom::~Easom(){

}

void Easom::setFnEvals(int c){
	cont = c;	
}

int Easom::getFnEvals(){
	return cont;	
}

real Easom::getGap(){
	return (bestValue - minValue);
}

bool Easom::isNearOptimum(real fBest){
	//real bestValue = -1.0;
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = fabs(minValue)*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Easom::calc(real *x){
	cont++;
 	real fX = 0, pi=3.14159265;
	
	fX = -1.0*cos(x[0])*cos(x[1])*exp(-1.0*pow(x[0] - pi,2) - pow(x[1] - pi,2));
	return fX;

}

real Easom::calc2(ap::real_1d_array x){
	cont++;
 	real fX = 0, pi=3.14159265;
	
	fX = -1.0*cos(x(1))*cos(x(2))*exp(-1.0*pow(x(1) - pi,2) - pow(x(2) - pi,2));
	return fX;
}

void Easom::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){
	contGrad++;
 	real pi=3.14159265;

	// g(1) = cos(y)*(sin(x)-2(pi-x)cos(x))e^(-(pi-x)^2 - (pi-y)^2)
	// g(2) = cos(x)*(sin(y)-2(pi-y)cos(y))e^(-(pi-x)^2 - (pi-y)^2)

	g(1) = cos(x(2))*(sin(x(1))-2*(pi-x(1))*cos(x(1)))*exp(-1.0*pow(pi - x(1),2) - pow(pi - x(2),2));
	g(2) = cos(x(1))*(sin(x(2))-2*(pi-x(2))*cos(x(2)))*exp(-1.0*pow(pi - x(1),2) - pow(pi - x(2),2));

}
