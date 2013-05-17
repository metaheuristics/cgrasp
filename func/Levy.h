#ifndef LEVY_H_
#define LEVY_H_

#include "Funcao.h"

class Levy: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Levy(int n);
		virtual ~Levy();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*LEVY_H_*/
