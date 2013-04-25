#ifndef SUMSQUARES_H_
#define SUMSQUARES_H_

#include "Funcao.h"
#include "Util.h"

class SumSquares: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		SumSquares(int n);
		virtual ~SumSquares();

		void setFnEvals(int c);
		virtual int getFnEvals();
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /*SumSquares_H_*/
