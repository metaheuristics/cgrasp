#include <stdio.h>
#include <math.h>

#include "ParSphere.h"
#include "Util.h"

#include "sphere_gpu.h"


// implementacao dos metodos

ParSphere::ParSphere(int n) : n(n)
{
    this->cont = 0;
    this->minValue = 0.0;
}

ParSphere::~ParSphere()
{
}

void ParSphere::setFnEvals(int c)
{
    this->cont = c;
}

int ParSphere::getFnEvals()
{
    return this->cont;
}

bool ParSphere::isNearOptimum(real fBest)
{
    real deltaValue = fabs(fBest - minValue);
    real equation = minValue * 0.0001 + 0.000001;

    if (deltaValue < equation || Util::equals(deltaValue, equation)) {
        return true;
    }

    return false;
}

real ParSphere::calc(real *x)
{
    cont++;
    return sphere_gpu(x);
}

real ParSphere::getGap()
{
    return bestValue - minValue;
}

real ParSphere::calc2(ap::real_1d_array x)
{
    cont++;
    return 0.0;   // TODO: fix
}

void ParSphere::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g)
{
    contGrad++;

    for (int i = 0; i < n; ++i) {
        g(i+1) = 2 * x(i+1);
    }
}
