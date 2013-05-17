#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

//void Util::setMtRand(MTRand *mtRand) {
//  this->mtRand = mtRand;
//}

real Util::dRand()
{
    return ((real)rand() / ((real)(RAND_MAX)) );
    //return mtRand->rand();
}

void Util::copy(real *xAux, real *x, int n){
    for (int i = 0; i < n; i++) {
        xAux[i] = x[i];
    }
}

// Se x está no intervalo entre 'l' e 'u' retorne true, senao retorne false.
bool Util::feasible(real *x, real *l, real *u, int n)
{
    for (int i = 0; i < n; i++) {
        if ((x[i] < l[i]) || (x[i] > u[i])) {
            return false;
        }
    }

    return true;
}

bool Util::equals(real x1, real x2)
{
    if (fabs(x1 - x2) > 0.000001) {   // FIX: tolerancia fixa
        return false;
    }

    return true;
}

void Util::printX(real *x, int n)
{
    printf("(");
    for (int i = 0; i < n; i++) {
        printf(" %lf", x[i]);
        if (i < n-1){
            printf(",");
        }
    }
    printf(")");
}

real Util::calcNorma(real *x, real *xGrid, int n)
{
    real aux = 0.0, norma;

    for (int i = 0; i < n; i++) {
        aux += pow((xGrid[i]-x[i]), 2);
    }

    norma = sqrt(aux);
    return norma;
}


real Util::calcNorma(real *x, int n)
{
    real aux = 0.0, norma;

    for (int i = 0; i < n; i++) {
        aux += pow(x[i], 2);
    }

    norma = sqrt(aux);
    return norma;
}

real Util::dist(real *x1, real *x2, int n)
{
    real aux = 0.0;

    for (int i = 0; i < n; i++) {
        aux += pow(x2[i]-x1[i], 2);
    }

    return sqrt(aux);
}

real Util::maxreal(real x1, real x2)
{
    return ((x1 > x2) ? x1: x2);
}

real Util::minreal(real x1, real x2)
{
    return ((x1 < x2) ? x1: x2);
}

real Util::dotproduct(real *x1, real *x2, int n)
{
    real aux = 0.0;
    for (int i = 0; i < n; i++) {
        aux += x1[i]*x2[i];
    }
    return aux;
}

void Util::addvector(real *x1, real *x2, int n)
{
    for (int i = 0; i < n; i++){
        x1[i] += x2[i];
    }
}

void Util::subvector(real *x1, real *x2, int n)
{
    for (int i = 0; i < n; i++) {
        x1[i] -= x2[i];
    }
}

real Util::sqr(real x)
{
    return x*x;
}
