#ifndef DTS_H_
#define DTS_H_

#include <math.h>

#include "Funcao.h"
#include "TabuList.h"
#include "MersenneTwister.h"

#include <list>
#define DEBUG_LEVEL1_ 1
#define DEBUG_LEVEL2_ 2
#define DEBUG_LEVEL3_ 3
#define DEBUG_LEVEL4_ 4


class Dts{
	
	private:
		int n;
		double *l, *u;
		double hs, he;
				
		double rTR, rSTR;
		Funcao *func;
		TabuList *tl;
		int debug;
		
		double *calcCentroide(double *x, double *dMax);
		
	public:
		static const double GOLDEN_RATIO = 1.61803399;

	 	double *goldenSearch(double *x, double *v, double *fXAux, double h, bool *imprL);

		bool neighborhoodSearch(double *x, double *fXAux, double h, double *dir);
		bool localSearch(double *x, double *fXAux, double h, double *dir);		
		bool explorationSearch(double *x, double *fXAux, double h);
		//void perturbe(double *x, double h);
		void perturbe(double *x, double *xBestAux, double h);

		Dts(int n, double* l, double *u, Funcao *f, double hs, double he);
		virtual ~Dts();
};

#endif /*DTS_H_*/

