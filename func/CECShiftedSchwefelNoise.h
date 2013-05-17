#ifndef CEC_SHIFTED_SCHWEFEL_NOISE_H_
#define CEC_SHIFTED_SCHWEFEL_NOISE_H_

# define SIMPLE_SPRNG
# include "sprng/include/sprng.h"
# define SEED 01234567

#include "Funcao.h"

class CECShiftedSchwefelNoise: public Funcao{
	
	private:
		int n;
		int cont;
		
		real *o;
		
		// Variable declarations for the random number generator 
		int rndcalcflag;
		real rndx1, rndx2;

		// Function declarations for the random number generator 
		void randomize();		
		real randomperc();
		real randomnormaldeviate();

	public:
		CECShiftedSchwefelNoise(int n);
		virtual ~CECShiftedSchwefelNoise();
		virtual int getFnEvals();
		void setFnEvals(int c);
		virtual bool isNearOptimum(real fBest);				
		virtual real calc(real *x);
		virtual real getGap();
		virtual real calc2(ap::real_1d_array x);
		virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /* CEC_SHIFTED_SCHWEFEL_NOISE_H_*/
