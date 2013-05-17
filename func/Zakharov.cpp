#include <stdio.h>
#include <math.h>
#include "Zakharov.h"
#include "Util.h"


Zakharov::Zakharov(int n){
	contGrad = 0;	
	cont = 0;
	this->n = n;
	minValue = 0.0;
}

Zakharov::~Zakharov(){

}

void Zakharov::setFnEvals(int c){
	cont = c;	
	contGrad = 0;
}

int Zakharov::getFnEvals(){
	return cont;	
}

int Zakharov::getGradEvals(){
	return contGrad;	
}

real Zakharov::getGap(){
	return (bestValue - minValue);
}

bool Zakharov::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = fabs(bestValue)*0.0001 + 0.000001;	
//	equation = fabs(bestValue)*0.0001 + 0.01;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real Zakharov::calc(real *x){
	real som1 = 0.0, som2 = 0.0;
	real fx = 0.0; 
	cont++;

	for (int i = 0; i < n; i++){		som1 += x[i]*x[i];
		som2 += 0.5*x[i]*(real(i+1));
	}

	//printf("Som1 = %lf - Som2 = %lf \n", som1, som2);
	fx = som1 + pow(som2, 2) + pow(som2,4);
	return fx;
}

real Zakharov::calc2(ap::real_1d_array x){
	real som1 = 0.0, som2 = 0.0;
	real fx = 0.0; 
	cont++;

	for (int i = 1; i <= n; i++){		som1 += x(i)*x(i);
		som2 += 0.5*x(i)*(real)i;
	}

	//printf("Som1 = %lf - Som2 = %lf \n", som1, som2);
	fx = som1 + pow(som2, 2) + pow(som2,4);
	return fx;
}


void Zakharov::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){
	real som = 0.0;
	contGrad++;
	
	for (int i = 1; i <= n; i++){		som += 0.5*x(i)*(real)i;
	}

	for (int i = 1; i < n; i++){
		//	g(i)= 2*x(i) + 2*som*(0.5*(real)i) + 4*pow(som,3)*(0.5*(real)i);
		g(i) = 2*x(i) + som*(real)i + 2*(real)i*pow(som,3);
	}
}
