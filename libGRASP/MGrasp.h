#ifndef MGRASP_H_
#define MGRASP_H_

#include <math.h>

#include "Dts.h"
#include "Funcao.h"
#include "MersenneTwister.h"
#include "TabuList.h"
#include "lbfgs.h"
#include "ap.h"

#include <list>
#define DEBUG_LEVEL0_ 0
#define DEBUG_LEVEL1_ 1
#define DEBUG_LEVEL2_ 2
#define DEBUG_LEVEL3_ 3
#define DEBUG_LEVEL4_ 4


class MGrasp{

 private:
    int n;
    double *l, *u;
    double hs, he;
    double plo;

    Funcao *func;

    int contIter;
    double fBest;
    double *xBest;

    MTRand *mtRand;
    int debug;

    Dts *dts;

    int *evals;
    double *gaps;
    int indexGap;

 protected:

 public:
    static const int MAX_ITERACOES = 20;
    static const double GOLDEN_RATIO = 1.61803399;

    double *getXBest();
    double *getGaps();
    bool   stopCriteria();
    int    randSelectElement(std::list<int> rcl);
    void   unifRandom(double *xAux);
    double linearSearch(double *x, int i, double *gI, double h);
    double goldenSearch(double *x, int i, double *gI, double h);

    void perturbe(double *x, double h);

    void randSelectElementBh(double *x, double *xBestAux, double h);
    bool constructGreedyRandom(double *x, double h);
    //bool localImprovement(double *x, double h);
    bool localImprovementTS(double *x, double *fXAux, double h);
    bool localImprovement(double *x, double *fX, double h);

    bool verifyGap(double fX, int maxEvals);
    bool start(bool hibrid, int m, int maxEvals);

    MGrasp(int n, double* l, double *u, Funcao *f, double hs, double he, double plo);
    virtual ~MGrasp();
};

#endif /*MGRASP_H_*/
