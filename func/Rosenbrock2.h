#ifndef ROSENBROCK_H_
#define ROSENBROCK_H_

#include "Funcao.h"

class Rosenbrock2: public Funcao{
	private:
		int n;
		int cont;
		int contGrad;
		
	public:
		Rosenbrock2(int n);
		virtual ~Rosenbrock2();

		void setFnEvals(int c);
		virtual int getFnEvals();
		virtual int getGradEvals();
		virtual real getGap();

		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
		
};

#endif /*ROSENBROCK_H_*/
