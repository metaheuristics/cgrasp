#include <stdio.h>
#include <math.h>


#include "CECShiftedSphere.h"
#include "Util.h"

CECShiftedSphere::CECShiftedSphere(int n){
		
	real o[100] = { -3.9311900e+001,  5.8899900e+001, -4.6322400e+001, -7.4651500e+001, -1.6799700e+001, -8.0544100e+001, -1.0593500e+001,  2.4969400e+001,  8.9838400e+001,  9.1119000e+000, -1.0744300e+001, -2.7855800e+001, -1.2580600e+001,  7.5930000e+000,  7.4812700e+001,  6.8495900e+001, -5.3429300e+001,  7.8854400e+001, -6.8595700e+001,  6.3743200e+001,  3.1347000e+001, -3.7501600e+001,  3.3892900e+001, -8.8804500e+001, -7.8771900e+001, -6.6494400e+001,  4.4197200e+001,  1.8383600e+001,  2.6521200e+001,  8.4472300e+001,  3.9176900e+001, -6.1486300e+001, -2.5603800e+001, -8.1182900e+001,  5.8695800e+001, -3.0838600e+001, -7.2672500e+001,  8.9925700e+001, -1.5193400e+001, -4.3337000e+000,  5.3430000e+000,  1.0560300e+001, -7.7726800e+001,  5.2085900e+001,  4.0394400e+001,  8.8332800e+001, -5.5830600e+001,  1.3181000e+000,  3.6025000e+001, -6.9927100e+001, -8.6279000e+000, -5.6894400e+001,  8.5129600e+001,  1.7673600e+001,  6.1529000e+000, -1.7695700e+001, -5.8953700e+001,  3.0356400e+001,  1.5920700e+001, -1.8008200e+001,  8.0641100e+001, -4.2391200e+001,  7.6277600e+001, -5.0165200e+001, -7.3573600e+001,  2.8336900e+001, -5.7990500e+001, -2.2732700e+001,  5.2026900e+001,  3.9259900e+001,  1.0867900e+001,  7.7820700e+001,  6.6039500e+001, -5.0066700e+001,  5.5706300e+001,  7.3714100e+001,  3.8529600e+001, -5.6786500e+001, -8.9647700e+001,  3.7957600e+001,  2.9472000e+001, -3.5464100e+001, -3.1786800e+001,  7.7323500e+001,  5.4790600e+001, -4.8279400e+001,  7.4271400e+001,  7.2610300e+001,  6.2964000e+001, -1.4144600e+001,  2.0492300e+001,  4.6589700e+001, -8.3602100e+001, -4.6480900e+001,  8.3737300e+001, -7.9661100e+001,  2.4347900e+001, -1.7230300e+001,  7.2340400e+001, -3.6402200e+001 };

	cont = 0;
	minValue = -450.0;

	this->n = n;
	this->o = new real[100];
	memcpy(this->o, o, sizeof(o));

	//printf("Sizeof de o = %d - %d\n", sizeof(o), sizeof(this->o));
	
}

CECShiftedSphere::~CECShiftedSphere(){
	//delete []o;
}

void CECShiftedSphere::setFnEvals(int c){
	cont = c;	
}

int CECShiftedSphere::getFnEvals(){
	return cont;	
}

real CECShiftedSphere::getGap(){
	return (bestValue - minValue);
}

bool CECShiftedSphere::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = fabs(minValue*0.0001 + 0.000001);	

	//printf("\tEquation = %lf - DeltaValue = %lf \n", equation, deltaValue);		
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real CECShiftedSphere::calc(real *x){
	cont++;  
	real value,sum=0;
	int i;

	for (i = 0; i < n; i++){
		sum += pow(x[i]-o[i],(real) 2);
	}
	
	value = sum - 450.0;
	return value;
}


real CECShiftedSphere::calc2(ap::real_1d_array x){
	cont++;  
	real value,sum=0;
	int i;

	for (i = 1; i <= n; i++){
		sum += pow(x(i)-o[i-1],(real) 2);
	}
	
	value = sum - 450.0;
	return value;

	return -1;
}


void CECShiftedSphere::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){
	contGrad++;
	for (int i = 1; i <= n; i++){
		g(i) = 2*(x(i)-o[i-1]);  
		//printf("g(%d) = %lf \n", i, g(i));
	 }

}
