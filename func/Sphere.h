#ifndef SPHERE_H_
#define SPHERE_H_

#include "Funcao.h"

class Sphere: public Funcao
{
 private:
    int n;
    int cont;

 public:
    Sphere(int n);
    virtual ~Sphere();
    virtual int getFnEvals();
    void setFnEvals(int c);
    virtual bool isNearOptimum(real fBest);
    virtual real calc(real *x);
    virtual real getGap();
    virtual real calc2(ap::real_1d_array x);
    virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
};

#endif /*SPHERE_H_*/
