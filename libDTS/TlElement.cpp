#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "TlElement.h"
#include "Util.h"


 TlElement::TlElement(double *x, int n, int fX){
 	this->n = n;
	this->fX = fX;	
	this->x = new double[n];
	Util::copy(this->x, x, n);
 }

 TlElement::~TlElement(){
 	delete []x;
 }

 double *TlElement::getX(){
	return x;
 }

 int TlElement::getFx(){
	return fX;
 }

 void TlElement::setX(double *x, int fX){
 	this->n = n;
	this->fX = fX;	
	this->x = new double[n];
	Util::copy(this->x, x, n);
 }

		
