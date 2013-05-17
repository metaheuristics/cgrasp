#ifndef DTS_H_
#define DTS_H_

#include <math.h>

#include "Funcao.h"
#include "TabuList.h"
#include "MersenneTwister.h"
#include "real.h"

#include <list>
#define DEBUG_LEVEL1_ 1
#define DEBUG_LEVEL2_ 2
#define DEBUG_LEVEL3_ 3
#define DEBUG_LEVEL4_ 4


class Dts
{
 private:
    int n;
    real *l, *u;
    real hs, he;

    real rTR, rSTR;
    Funcao *func;
    TabuList *tl;
    int debug;

    real *calcCentroide(real *x, real *dMax);

 public:
    static const real GOLDEN_RATIO = 1.61803399;

    real *goldenSearch(real *x, real *v, real *fXAux, real h, bool *imprL);

    bool neighborhoodSearch(real *x, real *fXAux, real h, real *dir);
    bool localSearch(real *x, real *fXAux, real h, real *dir);
    bool explorationSearch(real *x, real *fXAux, real h);
    //void perturbe(real *x, real h);
    void perturbe(real *x, real *xBestAux, real h);

    Dts(int n, real* l, real *u, Funcao *f, real hs, real he);
    virtual ~Dts();
};

#endif /*DTS_H_*/
