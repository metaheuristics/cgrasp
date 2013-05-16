#ifndef TELEMENT_H_
#define TELEMENT_H_

#include <math.h>

#include "Funcao.h"

class TlElement{
	
	private:
		int n;		
		int fX;
		double *x;
		int mFv;
		int mR;
		int m;
		
		double IFv;
		double IR;
	
	public:
		 		
		TlElement(double *x, int n, int fX);
		virtual ~TlElement();
				
		double *getX();
		int getFx();

		void setX(double *x, int fX);	

};

#endif /*TLELEMENT_H*/
