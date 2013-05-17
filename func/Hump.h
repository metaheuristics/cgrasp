#ifndef HUMP_H_
#define HUMP_H_

#include "Funcao.h"

class Hump: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Hump(int n);
		virtual ~Hump();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /* HUMP_H_*/
