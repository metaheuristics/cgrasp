#ifndef MGRASP_H_
#define MGRASP_H_

#include <math.h>

#include "Dts.h"
#include "Funcao.h"
#include "MersenneTwister.h"
#include "TabuList.h"
#include "lbfgs.h"
#include "ap.h"

#include "real.h"

#include <list>
#define DEBUG_LEVEL0_ 0
#define DEBUG_LEVEL1_ 1
#define DEBUG_LEVEL2_ 2
#define DEBUG_LEVEL3_ 3
#define DEBUG_LEVEL4_ 4


class MGrasp
{
 private:
    int n;
    real *l, *u;
    real hs, he;
    real plo;

    Funcao *func;

    int contIter;
    real fBest;
    real *xBest;

    MTRand *mtRand;
    int debug;

    Dts *dts;

    int    evals[7];
    real gaps[7];
    int indexGap;

 protected:

 public:
    static const int MAX_ITERACOES = 20;
    static const real GOLDEN_RATIO = 1.61803399;

    real *getXBest();
    real *getGaps();
    bool   stopCriteria();
    int    randSelectElement(std::list<int> rcl);
    void   unifRandom(real *xAux);
    real linearSearch(real *x, int i, real *gI, real h);
    real goldenSearch(real *x, int i, real *gI, real h);

    void perturbe(real *x, real h);

    void randSelectElementBh(real *x, real *xBestAux, real h);
    bool constructGreedyRandom(real *x, real h);
    //bool localImprovement(real *x, real h);
    bool localImprovementTS(real *x, real *fXAux, real h);
    bool localImprovement(real *x, real *fX, real h);

    bool verifyGap(real fX, int maxEvals);
    bool start(bool hibrid, int m, int maxEvals);

    void setDebugLevel(int dbglvl)           {   this->debug = dbglvl;   }

    MGrasp(int n, real* l, real *u, Funcao *f, real hs, real he, real plo);
    virtual ~MGrasp();
};

#endif /*MGRASP_H_*/
