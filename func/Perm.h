#ifndef PERM_H_
#define PERM_H_

#include "Funcao.h"

class Perm: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Perm(int n);
		virtual ~Perm();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*PERM_H_*/
