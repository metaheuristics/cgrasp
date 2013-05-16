#ifndef CEC_SHIFTED_SCHWEFEL_H_
#define CEC_SHIFTED_SCHWEFEL_H_

#include "Funcao.h"

class CECShiftedSchwefel: public Funcao{
	
	private:
		int n;
		int cont;
		
		double *o;

	public:
		CECShiftedSchwefel(int n);
		virtual ~CECShiftedSchwefel();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(double fBest);				
		virtual double calc(double *x);
		virtual double getGap();
		virtual double calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_SHIFTED_SPHERE_H_*/
