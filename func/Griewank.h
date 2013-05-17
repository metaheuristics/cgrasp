#ifndef GRIEWANK_H_
#define GRIEWANK_H_

#include "Funcao.h"

class Griewank: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Griewank(int n);
		virtual ~Griewank();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*GRIEWANK_H_*/
