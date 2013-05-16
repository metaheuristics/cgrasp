#ifndef TABULIST_H_
#define TABULIST_H_

#include <math.h>

#include "Funcao.h"
#include "TlElement.h"

class TabuList{
	
	private:
		int n;		
		int length;
		int numElements;
		
		double nMax;
		double nMin;
		double uMax;
		double uMin;

		TlElement **list;
					
	public:
		
		TabuList(int length, int n);
		virtual ~TabuList();
		
		int getNumberElements();
		int getLength();	
		double *getX(int i);
		TlElement *getElement(int i);
		
		bool isSemiTR(double *xSTR, double *x, double rSTR);
		bool isAnySemiTR(double *x, double rSTR);

		void insertElement(double *x, int n, int fX);
		
		bool isInList(double *x, int n);
		void clear();	
};

#endif /*TABU_LIST_H*/
