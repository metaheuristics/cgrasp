#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "real.h"
#include "TlElement.h"
#include "Util.h"


TlElement::TlElement(real *x, int n, int fX)
{
    this->n = n;
    this->fX = fX;
    this->x = new real[n];
    Util::copy(this->x, x, n);
}

TlElement::~TlElement()
{
    delete []x;
}

real *TlElement::getX()
{
    return x;
}

int TlElement::getFx()
{
    return fX;
}

void TlElement::setX(real *x, int fX)
{
    this->n = n;
    this->fX = fX;
    this->x = new real[n];
    Util::copy(this->x, x, n);
}
