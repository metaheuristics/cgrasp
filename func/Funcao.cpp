#include "Funcao.h"
#include <limits>

Funcao::Funcao()
{
    cont = 0;
    contGrad = 0;
    bestValue = std::numeric_limits<real>::max();
}

Funcao::~Funcao()
{
}

int Funcao::getGradEvals()
{
    return contGrad;
}

int Funcao::getFnEvals()
{
    return cont;
}

real Funcao::getGap()
{
    return std::numeric_limits<real>::max();
}

void Funcao::setBestValue(real fX)
{
    bestValue = fX;
}

bool Funcao::isNearOptimum(real fBest)
{
    return true;
}

real Funcao::calc(real *x)
{
    return 0.0;
}

real Funcao::calc2(ap::real_1d_array x)
{
    return 0.0;
}

void Funcao::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g)
{
    return;
}
