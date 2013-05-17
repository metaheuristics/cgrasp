// real.h
// Define numeros de ponto-flutuante de maneira condicional (float/double)

#ifndef __REAL_H
#define __REAL_H

#ifdef REAL_FLOAT
typedef float real;
#else
typedef double real;
#endif

#endif                   // __REAL_H
