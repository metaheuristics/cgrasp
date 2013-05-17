#ifndef __SPHERE_GPU_H
#define __SPHERE_GPU_H

#include "real.h"

bool init_gpu(int n);
void finalize_gpu();
real sphere_gpu(real *x);

#endif                             // __SPHERE_GPU_H
