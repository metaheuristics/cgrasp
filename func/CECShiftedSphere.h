#ifndef CEC_SHIFTED_SPHERE_H_
#define CEC_SHIFTED_SPHERE_H_

#include "Funcao.h"

class CECShiftedSphere: public Funcao{
	
	private:
		int n;
		int cont;
		
		real *o;

	public:
		CECShiftedSphere(int n);
		virtual ~CECShiftedSphere();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);


};

#endif /* CEC_SHIFTED_SPHERE_H_*/
