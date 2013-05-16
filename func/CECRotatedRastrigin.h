#ifndef CEC_ROTATED_RASTRIGIN_H_
#define CEC_ROTATED_RASTRIGIN_H_

#include "Funcao.h"

class CECRotatedRastrigin: public Funcao{
	
	private:
		int n;
		int cont;
		
		long double *o;
		long double **M;

		long double *calcZ(double *x);

	public:
		CECRotatedRastrigin(int n);
		virtual ~CECRotatedRastrigin();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_ROTATED_RASTRIGIN_H_*/
