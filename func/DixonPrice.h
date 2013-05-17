#ifndef DIXONPRICE_H_
#define DIXONPRICE_H_

#include "Funcao.h"

class DixonPrice: public Funcao{
	private:
		int n;
		int cont;
		
	public:
		DixonPrice(int n);
		virtual ~DixonPrice();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);

};

#endif /* DIXONPRICE_H_ */
