#include <stdio.h>
#include <math.h>

#include "GoldsteinPrice.h"
#include "Util.h"
#include "ap.h"


GoldsteinPrice::GoldsteinPrice(int n){
	cont = 0;
	this->n = n;
	minValue = 3.0;
}

GoldsteinPrice::~GoldsteinPrice(){

}

void GoldsteinPrice::setFnEvals(int c){
	cont = c;	
}

int GoldsteinPrice::getFnEvals(){
	return cont;	
}

double GoldsteinPrice::getGap(){
	return (bestValue - minValue);
}

bool GoldsteinPrice::isNearOptimum(double fBest){
	//double bestValue = 3.0;
	double deltaValue =	fabs(fBest - minValue);
	double equation;
	
	equation = fabs(minValue)*0.0001 + 0.000001;	
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

double GoldsteinPrice::calc(double *x){
	cont++;
	long double fX;

	fX = (1 + pow(x[0] + x[1] +1,2)*(19 -14*x[0] + 3*pow(x[0],2) -14*x[1] + 6*x[0]*x[1] + 3*pow(x[1],2))) *
          (30 + pow(2*x[0] - 3*x[1],2)*(18 - 32*x[0] + 12*pow(x[0],2) +48*x[1] - 36*x[0]*x[1] + 27*pow(x[1],2)));
	
	return fX; 
}

double GoldsteinPrice::calc2(ap::real_1d_array x){
	cont++;
	long double fX;

	fX = (1 + pow(x(1) + x(2) +1,2)*(19 -14*x(1) + 3*pow(x(1),2) -14*x(2) + 6*x(1)*x(2) + 3*pow(x(2),2))) *
          (30 + pow(2*x(1) - 3*x(2),2)*(18 - 32*x(1) + 12*pow(x(1),2) +48*x(2) - 36*x(1)*x(2) + 27*pow(x(2),2)));
	
	return fX;
}


void GoldsteinPrice::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){
/*	
  contGrad++;

	// Numerical calculations of gradients
  const double step = 1e-6;
  double fX, fXplus;
  int i;

  ap::real_1d_array xlocal(2);

  for(i = 0; i <= 1; i++ ) 
	xlocal(i+1) = x(i+1);

  fX = calc2(xlocal);
 
  for(i = 1 ; i>=0; --i) {
	xlocal(i+1) += step;
	//Fplus = Objective_Goldstein_Price( xlocal );
	fXPlus = calc2(xlocal);
	xlocal(i+1) -= step; // original x value
	g(i) = (fXplus-fX)/step;
  }
*/
}


