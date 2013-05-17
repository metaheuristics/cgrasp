#ifndef MATYAS_H_
#define MATYAS_H_

#include "Funcao.h"

class Matyas: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Matyas(int n);
		virtual ~Matyas();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*MATYAS_H_*/
