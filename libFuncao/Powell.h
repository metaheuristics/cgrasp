#ifndef POWELL_H_
#define POWELL_H_

#include "Funcao.h"

class Powell: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		Powell(int n);
		virtual ~Powell();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /*POWELL_H_*/
