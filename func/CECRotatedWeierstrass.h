#ifndef CEC_ROTATED_WEIERSTRASS_H_
#define CEC_ROTATED_WEIERSTRASS_H_

#include "Funcao.h"

class CECRotatedWeierstrass: public Funcao{
	
	private:
		int n;
		int cont;

		real *o;
		real **M;
		
		int kMax;
		real a,b;
		real sum2;		
		
		real *calcZ(real *x);

	public:
		CECRotatedWeierstrass(int n);
		virtual ~CECRotatedWeierstrass();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_ROTATED_WEIERSTRASS_H_*/
