#ifndef FUNCAO_H_
#define FUNCAO_H_

#include "ap.h"
#include "real.h"

class Funcao
{
 protected:
    int cont;
    int contGrad;
    real minValue;
    real bestValue;

 public:
    static const int ROSENBROCK         = 1;
    static const int ZAKHAROV           = 2;
    static const int SUMSQUARES         = 3;
    static const int BRANIN             = 4;
    static const int EASOM              = 5;
    static const int GOLDSTEINPRICE     = 6;
    static const int SHEKEL             = 7;
    static const int HARTMANN           = 8;
    static const int SHUBERT            = 9;
    static const int BEALE              = 10;
    static const int BOOTH              = 11;
    static const int BOHACHEVSKY        = 12;
    static const int HUMP               = 13;
    static const int MATYAS             = 14;
    static const int SCHWEFEL           = 15;
    static const int COLVILLE           = 16;
    static const int PERM               = 17;
    static const int PERM0              = 18;
    static const int POWERSUM           = 19;
    static const int GRIEWANK           = 20;
    static const int RASTRIGIN          = 21;
    static const int TRID               = 22;
    static const int POWELL             = 23;
    static const int DIXONPRICE         = 24;
    static const int ACKLEY             = 25;
    static const int LEVY               = 26;
    static const int SPHERE             = 27;
    static const int SHIFTEDSPHERE      = 28;
    static const int SHIFTEDSCHWEFEL    = 29;
    static const int SHIFTEDSCHWEFELN   = 30;
    static const int ROTATEDRASTRIGIN   = 31;
    static const int ROTATEDWEIERSTRASS = 32;
    static const int ROTATEDEXPSCAFFERS = 33;

    // versoes paralelas das funcoes objetivo
    static const int PAR_SPHERE         = 101;


    // metodos
    Funcao();
    virtual ~Funcao();
    virtual real calc(real *x);
    virtual real calc2(ap::real_1d_array x);
    virtual void calcGrad(ap::real_1d_array &x, ap::real_1d_array &g);
    virtual bool isNearOptimum(real fBest);
    virtual int getFnEvals();
    virtual int getGradEvals();
    virtual real getGap();

    void setBestValue(real fX);
};

#endif /*FUNCAO_H_*/
