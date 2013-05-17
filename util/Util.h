#ifndef UTIL_H_
#define UTIL_H_

#include "real.h"
#include "MersenneTwister.h"
#include <string.h>

class Util{
 private:
    MTRand *mtRand;

 public:
    Util();
    virtual ~Util();

    //static void setMtRand(MTRand *mtRand2);
    static real dRand();

    static void copy(real *xAux, real *x, int n);
    static real calcNorma(real *x, real *xGrid, int n);
    static real calcNorma(real *x, int n);
    static real dist(real *x1, real *x2, int n);

    static bool feasible(real *x, real *l, real *u, int n);
    static bool equals(real x1, real x2);
    static void printX(real *x, int n);

    static real maxreal(real x1, real x2);
    static real minreal(real x1, real x2);
    static real dotproduct(real *x1, real *x2, int n);
    static real sqr(real x1);
    static void addvector(real *x1, real *x2, int n);
    static void subvector(real *x1, real *x2, int n);


};

#endif
