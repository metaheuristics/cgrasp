#ifndef CEC_ROTATED_EXP_SCAFFERS_H_
#define CEC_ROTATED_EXP_SCAFFERS_H_

#include "Funcao.h"

class CECRotatedExpScaffers: public Funcao{
	
	private:
		int n;
		int cont;

		double *o;
		double **M;
		
		long double *calcZ(double *x);
		double calcF(double a, double b);

	public:
		CECRotatedExpScaffers(int n);
		virtual ~CECRotatedExpScaffers();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_ROTATED_EXP_SCAFFERS_H_*/
