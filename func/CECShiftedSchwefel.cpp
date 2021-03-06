#include <stdio.h>
#include <math.h>

#include "CECShiftedSchwefel.h"
#include "Util.h"

CECShiftedSchwefel::CECShiftedSchwefel(int n){
		
	real o[100] = { 3.5626700e+001, -8.2912300e+001, -1.0642300e+001, -8.3581500e+001, 8.3155200e+001, 4.7048000e+001, -8.9435900e+001, -2.7421900e+001,  7.6144800e+001, -3.9059500e+001,  4.8885700e+001, -3.9828000e+000, -7.1924300e+001,  6.4194700e+001, -4.7733800e+001, -5.9896000e+000, -2.6282800e+001, -5.9181100e+001,  1.4602800e+001, -8.5478000e+001, -5.0490100e+001, 9.2400000e-001,  3.2397800e+001,  3.0238800e+001, -8.5094900e+001,  6.0119700e+001, -3.6218300e+001, -8.5883000e+000, -5.1971000e+000,  8.1553100e+001, -2.3431600e+001, -2.5350500e+001, -4.1248500e+001,  8.8018000e+000, -2.4222200e+001, -8.7980700e+001,  7.8047300e+001, -4.8052800e+001,  1.4017700e+001, -3.6640500e+001,  1.2216800e+001,  1.8144900e+001, -6.4564700e+001, -8.4849300e+001, -7.6608800e+001, -1.7042000e+000, -3.6076100e+001,  3.7033600e+001,  1.8443100e+001, -6.4359000e+001, -3.9369200e+001, -1.7714000e+001,  3.0198500e+001, -1.8548300e+001,  9.6866000e+000,  8.2600900e+001, -4.5525600e+001,  5.1443000e+000,  7.4204000e+001,  6.6810300e+001, -6.3470400e+001,  1.3032900e+001, -5.6878000e+000,  2.9527100e+001, -4.3530000e-001, -2.6165200e+001, -6.6847000e+000, -8.0229100e+001, -2.9581500e+001,  8.2042200e+001,  7.7177000e+001, -1.1277000e+001,  3.2075900e+001, -2.6858000e+000,  8.1509600e+001,  6.4077000e+001, -2.6129400e+001, -8.4782000e+001, -6.2876800e+001, -3.7635500e+001,  7.6891600e+001,  5.3417000e+001, -2.5331100e+001, -3.8070200e+001, -8.4173800e+001, -1.1224600e+001, -8.3461900e+001, -1.7550800e+001, -3.6528500e+001,  8.9552800e+001,  2.5879400e+001,  6.8625200e+001,  5.5796800e+001, -2.9597500e+001, -5.8097600e+001,  6.5741300e+001, -8.8703000e+000, -5.3281000e+000,  7.4066100e+001,  4.0338000e+000 };

	cont = 0;
	minValue = -450.0;

	this->n = n;
	this->o = new real[100];
	memcpy(this->o, o, sizeof(o));

	//printf("Sizeof de o = %d - %d\n", sizeof(o), sizeof(this->o));
}

CECShiftedSchwefel::~CECShiftedSchwefel(){
	//delete []o;
}

void CECShiftedSchwefel::setFnEvals(int c){
	cont = c;	
}

int CECShiftedSchwefel::getFnEvals(){
	return cont;	
}

real CECShiftedSchwefel::getGap(){
	return (bestValue - minValue);
}

bool CECShiftedSchwefel::isNearOptimum(real fBest){
	real deltaValue =	fabs(fBest - minValue);
	real equation;
	
	equation = fabs(minValue*0.0001 + 0.000001);	

	//printf("\tEquation = %lf - DeltaValue = %lf \n", equation, deltaValue);		
	if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
		return true;
	} 

	return false;
}

real CECShiftedSchwefel::calc(real *x){
	cont++;  
	real z;	
	real value,sum=0;
	int i, j;

	//printf("Inicio... \n");	
	for (i = 0; i < n; i++){
		z = 0.0;
		for (j = 0; j <= i; j++){
			z += x[j] - o[j];			
		}
		sum += z*z;//pow(z, 2);
	}
	
	value = sum - 450.0;

	//printf("Fim... \n");	
	return value;
}


real CECShiftedSchwefel::calc2(ap::real_1d_array x){
	return -1.0;
}


void CECShiftedSchwefel::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g){

}
