#ifndef SHEKEL_H_
#define SHEKEL_H_

#include "Funcao.h"

class Shekel: public Funcao{
	private:
		int m, n;
		int cont;
		
	public:
		Shekel(int n, int m);
		virtual ~Shekel();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
		virtual real getGap();

};

#endif /*SHEKEL_H_*/
