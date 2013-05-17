#ifndef HARTMANN_H_
#define HARTMANN_H_

#include "Funcao.h"

class Hartmann: public Funcao{
	private:
		int m, n;
		int cont;
		
		real func43(real *x);
		real func46(real *x);
		
	public:
		Hartmann(int n, int m);
		virtual ~Hartmann();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
		virtual real getGap();

};

#endif /*Hartmann_H_*/
