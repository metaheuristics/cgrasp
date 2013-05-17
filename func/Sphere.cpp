#include <stdio.h>
#include <math.h>

#include "Sphere.h"
#include "Util.h"

Sphere::Sphere(int n)
{
    cont = 0;
    this->n = n;
    minValue = 0.0;
}

Sphere::~Sphere()
{
}

void Sphere::setFnEvals(int c)
{
    cont = c;
}

int Sphere::getFnEvals()
{
    return cont;
}

real Sphere::getGap()
{
    return (bestValue - minValue);
}

bool Sphere::isNearOptimum(real fBest)
{
    real deltaValue = fabs(fBest - minValue);
    real equation;

    equation = minValue*0.0001 + 0.000001;
    if ((deltaValue < equation) || (Util::equals(deltaValue, equation))){
        return true;
    }

    return false;
}

real Sphere::calc(real *x)
{
    cont++;
    real value,sum=0;
    int i;

    for (i = 0; i < n; i++)
        sum += pow(x[i],(real) 2);

    value = sum;

    return value;
}


real Sphere::calc2(ap::real_1d_array x)
{
    cont++;
    real value,sum=0;
    int i;

    for (i = 0; i < n; i++)
        sum += pow(x(i+1),(real) 2);

    value = sum;

    return value;
}


void Sphere::calcGrad(ap::real_1d_array &x, ap::real_1d_array &g)
{
    contGrad++;
    int i;

    for (i = 0; i < n; i++)
        g(i+1) = 2*x(i+1);
}
