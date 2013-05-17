#ifndef TELEMENT_H_
#define TELEMENT_H_

#include <math.h>

#include "real.h"
#include "Funcao.h"

class TlElement
{
 private:
    int n;
    int fX;
    real *x;
    int mFv;
    int mR;
    int m;

    real IFv;
    real IR;

 public:

    TlElement(real *x, int n, int fX);
    virtual ~TlElement();

    real *getX();
    int getFx();

    void setX(real *x, int fX);
};

#endif /*TLELEMENT_H*/
