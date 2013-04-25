#ifndef CEC_ROTATED_WEIERSTRASS_H_
#define CEC_ROTATED_WEIERSTRASS_H_

#include "Funcao.h"

class CECRotatedWeierstrass: public Funcao{
	
	private:
		int n;
		int cont;

		double *o;
		double **M;
		
		int kMax;
		double a,b;
		double sum2;		
		
		long double *calcZ(double *x);

	public:
		CECRotatedWeierstrass(int n);
		virtual ~CECRotatedWeierstrass();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_ROTATED_WEIERSTRASS_H_*/
