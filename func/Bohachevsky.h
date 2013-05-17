#ifndef BOHACHEVSKY_H_
#define BOHACHEVSKY_H_

#include "Funcao.h"

class Bohachevsky: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Bohachevsky(int n);
		virtual ~Bohachevsky();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*BOHACHEVSKY_H_*/
