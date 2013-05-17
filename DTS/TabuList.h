#ifndef TABULIST_H_
#define TABULIST_H_

#include <math.h>

#include "real.h"
#include "Funcao.h"
#include "TlElement.h"

class TabuList
{
 private:
    int n;
    int length;
    int numElements;

    real nMax;
    real nMin;
    real uMax;
    real uMin;

    TlElement **list;

 public:

    TabuList(int length, int n);
    virtual ~TabuList();

    int getNumberElements();
    int getLength();
    real *getX(int i);
    TlElement *getElement(int i);

    bool isSemiTR(real *xSTR, real *x, real rSTR);
    bool isAnySemiTR(real *x, real rSTR);

    void insertElement(real *x, int n, int fX);

    bool isInList(real *x, int n);
    void clear();
};

#endif /*TABU_LIST_H*/
