#ifndef ACKLEY_H_
#define ACKLEY_H_

#include "Funcao.h"

class Ackley: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Ackley(int n);
		virtual ~Ackley();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*ACKLEY_H_*/
