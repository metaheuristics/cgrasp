#ifndef __PARSPHERE_H
#define __PARSPHERE_H

#include "Funcao.h"

class ParSphere : public Funcao
{
 private:
    int n;
    int cont;

 public:
    ParSphere(int n);
    virtual ~ParSphere();
    virtual int getFnEvals();
    void setFnEvals(int c);
    virtual bool isNearOptimum(real fBest);
    virtual real calc(real *x);
    virtual real getGap();
    virtual real calc2(ap::real_1d_array x);
    virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif                   // __PARSPHERE_H
