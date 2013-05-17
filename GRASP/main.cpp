#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>

#include "MGrasp.h"
#include "Funcao.h"
#include "MersenneTwister.h"
#include "Util.h"
#include "Dts.h"
#include "lbfgs.h"
#include "real.h"

#include "Rosenbrock2.h"
#include "Zakharov.h"
#include "SumSquares.h"
#include "Branin.h"
#include "Easom.h"
#include "GoldsteinPrice.h"
#include "Shekel.h"
#include "Hartmann.h"
#include "Shubert.h"
#include "Beale.h"
#include "Booth.h"
#include "Bohachevsky.h"
#include "Hump.h"
#include "Matyas.h"
#include "Schwefel.h"

#include "Colville.h"
#include "Perm.h"
#include "Perm0.h"
#include "PowerSum.h"
#include "Griewank.h"
#include "Rastrigin.h"
#include "Trid.h"
#include "Powell.h"
#include "DixonPrice.h"
#include "Ackley.h"
#include "Levy.h"
#include "Sphere.h"
/*#include "CECShiftedSphere.h"
#include "CECShiftedSchwefel.h"
#include "CECShiftedSchwefelNoise.h"
#include "CECRotatedRastrigin.h"
#include "CECRotatedWeierstrass.h"
#include "CECRotatedExpScaffers.h"*/

#include "ap.h"

#define PURO    0
#define HIBRIDO 1
#define BFGS    2

int64_t getMilisegundos()
{
    struct timeval tempo;
    gettimeofday(&tempo, NULL);
    return (int64_t) tempo.tv_sec * 1000 + tempo.tv_usec / 1000;
 }


MGrasp *initMGrasp(int iFuncNum, int n, Funcao **func)
{
    int m;
    real *u, *l;
    real hs, he, plo;
    l = new real[n];
    u = new real[n];
    MGrasp *mgrasp;

    plo = 0.7;
    switch(iFuncNum) {
    case Funcao::ROSENBROCK:
        hs = 1.0;
        he = 0.1;
        if (n == 20) {
            hs = 0.1;
            he = 0.05;
        }

        for (int i =0; i < n; i++) {
            l[i] = -5.0;
            u[i] = 10.0;
        }
        *func = new Rosenbrock2(n);
        break;

    case Funcao::ZAKHAROV:
        hs = 1.0;
        //hs = 2.0;
        if (n <= 5)
            he = 0.5;
        else if (n >=20) {
            hs = 5.0;
            //hs = 5.0;
            he = 0.05;
        }
        else{
            he = 0.005;
        }

        for (int i =0; i < n; i++) {
            l[i] = -5.0;
            u[i] = 10.0;
        }
        *func = new Zakharov(n);
        break;

    case Funcao::SUMSQUARES:
        hs = 1.0;
        he = 0.5;
        for (int i =0; i < n; i++) {
            l[i] = -5.0;
            u[i] = 10.0;
        }
        *func = new SumSquares(n);
        break;

    case Funcao::BRANIN:
        hs = 1.0;
        he = 0.001;
        //hs = 0.1;
        //he = 0.05;
        l[0] = -5; l[1] = 0;
        u[0] = 10; u[1] = 15;
        *func = new Branin(n);
        break;

    case Funcao::GOLDSTEINPRICE:
        hs = 1.0;
        he = 1.0;
        //he = 0.05;
        for (int i =0; i < n; i++) {
            l[i] = -2.0;
            u[i] = 2.0;
        }
        *func = new GoldsteinPrice(n);
        break;

    case Funcao::EASOM:
        hs = 1.0;
        he = 0.1;

        for (int i =0; i < n; i++) {
            l[i] = -100.0;
            u[i] = 100.0;
        }
        *func = new Easom(n);
        break;

    case Funcao::SHEKEL:
        m = n;
        n = 4;
        delete []l;
        delete []u;

        l = new real[n];
        u = new real[n];

        hs = 1.0;
        he = 0.5;
        //hs = 0.1;
        //he = 0.05;
        for (int i = 0; i < n; i++) {
            l[i] = 0.0;
            u[i] = 10.0;
        }
        *func = new Shekel(n,m);
        break;

    case Funcao::HARTMANN:
        //hs = 0.1;
        //he = 0.001;

        if (n == 3) {
            hs = 0.5;
            he = 0.001;
        }
        else if (n == 6) {
            //he = 0.05;
            hs = 0.1;
            he = 0.01;
        }

        for (int i =0; i < n; i++) {
            l[i] = 0.0;
            u[i] = 1.0;
        }
        *func = new Hartmann(n,4);
        break;

    case Funcao::SHUBERT:
        hs = 1.0;
        he = 0.01;
        //hs = 0.1;
        //he = 0.05;
        for (int i =0; i < n; i++) {
            l[i] = -10.0;
            u[i] = 10.0;
        }
        *func = new Shubert(n);
        break;

    case Funcao::BEALE:
        hs = 1.0;
        he = 0.5;
        for (int i =0; i < n; i++) {
            l[i] = -4.5;
            u[i] = 4.5;
        }
        *func = new Beale(n);
        break;

    case Funcao::BOOTH:
        hs = 1.0;
        he = 0.5;
        for (int i =0; i < n; i++) {
            l[i] = -10.0;
            u[i] = 10.0;
        }
        *func = new Booth(n);
        break;

    case Funcao::BOHACHEVSKY:
        hs = 1.0;
        he = 0.5;
        for (int i =0; i < n; i++) {
            l[i] = -50.0;
            u[i] = 100.0;
        }
        *func = new Bohachevsky(n);
        break;

    case Funcao::HUMP:
        hs = 1.0;
        he = 0.01;
        for (int i =0; i < n; i++) {
            l[i] = -5.0;
            u[i] = 5.0;
        }
        *func = new Hump(n);
        break;

    case Funcao::MATYAS:
        hs = 1.0;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = -5.0;
            u[i] = 10.0;
        }
        *func = new Matyas(n);
        break;

    case Funcao::SCHWEFEL:
        if (n == 2) {
            hs = 5.0;
            he = 0.25;
        }
        else if (n==6) {
            hs = 50.0;
            he = 0.25;
        }

        for (int i = 0; i < n; i++) {
            l[i] = -500.0;
            u[i] = 500.0;
        }
        *func = new Schwefel(n);
        break;

    case Funcao::COLVILLE:
        hs = 1.0;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = -10.0;
            u[i] = 10.0;
        }
        *func = new Colville(n);
        break;

    case Funcao::PERM:
        //hs = 1.0;
        //he = 0.01;
        hs = 0.1;
        he = 0.0125;
        for (int i =0; i < n; i++) {
            l[i] = (real) -n;
            u[i] = (real) n;
        }
        *func = new Perm(n);
        break;

    case Funcao::PERM0:
        hs = 1.0;
        he = 0.01;
        //hs = 0.1;
        //he = 0.0125;
        for (int i =0; i < n; i++) {
            l[i] = (real) -n;
            u[i] = (real) n;
        }
        *func = new Perm_0(n);
        break;

    case Funcao::POWERSUM:
        hs = 1.0;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = (real) 0.0;
            u[i] = (real) n;
        }
        *func = new PowerSum(n);
        break;


    case Funcao::GRIEWANK:
        hs = 10.0;
        he = 0.25;
        for (int i =0; i < n; i++) {
            l[i] = -300.0;
            u[i] = 600.0;
        }
        *func = new Griewank(n);
        break;

    case Funcao::RASTRIGIN:
        //hs = 1.0;
        //he = 0.1;
        hs = 0.5;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = -2.56;
            u[i] = 5.12;
        }
        *func = new Rastrigin(n);
        break;


    case Funcao::TRID:
        if (n == 10) {
            hs = 5.0;
            he = 0.1;
        }
        else {
            hs = 1.0;
            he = 0.1;
        }

        for (int i =0; i < n; i++) {
            l[i] = (real) -n*n;
            u[i] = (real) n*n;
        }

        *func = new Trid(n);
        break;

    case Funcao::POWELL:
        hs = 1.0;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = -4.0;
            u[i] = 5.0;
        }
        *func = new Powell(n);
        break;

    case Funcao::DIXONPRICE:
        hs = 5.0;
        he = 0.25;
        for (int i =0; i < n; i++) {
            l[i] = -10.0;
            u[i] = 10.0;
        }
        *func = new DixonPrice(n);
        break;

    case Funcao::ACKLEY:
        hs = 5.0;
        he = 0.05;
        for (int i =0; i < n; i++) {
            l[i] = -15.0;
            u[i] = 30.0;
        }
        *func = new Ackley(n);
        break;


    case Funcao::LEVY:
        hs = 1.0;
        he = 0.1;
        for (int i =0; i < n; i++) {
            l[i] = -10.0;
            u[i] = 10.0;
        }
        *func = new Levy(n);
        break;

    case Funcao::SPHERE:
        hs = 2.0;
        he = 0.05;
        for (int i =0; i < n; i++) {
            l[i] = -2.56;
            u[i] = 5.12;
        }
        *func = new Sphere(n);
        break;

    /*
    case Funcao::SHIFTEDSPHERE:
        hs = 2.0;
        he = 0.1;
        for (int i =0; i < n; i++){
            l[i] = -100.0;
            u[i] = 100.0;
        }
        *func = new CECShiftedSphere(n);
        break;

    case Funcao::SHIFTEDSCHWEFEL:
        hs = 5.0;
        he = 0.1;
        for (int i =0; i < n; i++){
            l[i] = -100.0;
            u[i] = 100.0;
        }
        *func = new CECShiftedSchwefel(n);
        break;

    case Funcao::SHIFTEDSCHWEFELN:
        hs = 5.0;
        he = 0.1;
        for (int i =0; i < n; i++){
            l[i] = -100.0;
            u[i] = 100.0;
        }
        *func = new CECShiftedSchwefelNoise(n);
        break;

    case Funcao::ROTATEDRASTRIGIN:
        hs = 2.0;
        he = 0.05;
        for (int i =0; i < n; i++){
            l[i] = -5.0;
            u[i] = 5.0;
        }
        *func = new CECRotatedRastrigin(n);
        break;

    case Funcao::ROTATEDWEIERSTRASS:
        hs = 0.25;
        he = 0.01;
        for (int i =0; i < n; i++){
            l[i] = -0.5;
            u[i] = 0.5;
        }
        *func = new CECRotatedWeierstrass(n);
        break;

    case Funcao::ROTATEDEXPSCAFFERS:
        hs = 5.0;
        he = 0.1;
        for (int i =0; i < n; i++){
            l[i] = -100.0;
            u[i] = 100.0;
        }
        *func = new CECRotatedExpScaffers(n);
        break;

    */
    }

    mgrasp = new MGrasp(n, l, u, *func, hs, he, plo);
    mgrasp->setDebugLevel(1);
    return mgrasp;
}


void usage(){
    printf("\nForma de uso: ");
    printf(" CGrasp FN N MAX_EVALS RUNS TYPE M\n");
    printf(" FN: nome da funcao (ex: ROSENBROCK, ZAKHAROV, etc)\n");
    printf(" N: numero de dimensoes\n");
    printf(" RUNS: numero de execucoes do CGrasp p\n");
    printf(" MAX_EVALS: numero maximo de avaliacoes da funcao. Caso 0 rodar até encerrar o algoritmo\n");
    printf(" TYPE: tipo (PURO, HIBRIDO)\n");
    printf(" M: numero de correcoes da matriz do L-BFGS (m < n)\n\n");
}

int getFuncNumb(char *funcName){

    if (!strcmp(funcName, "ROSENBROCK"))         return Funcao::ROSENBROCK;
    if (!strcmp(funcName, "ZAKHAROV"))           return Funcao::ZAKHAROV;
    if (!strcmp(funcName, "SUMSQUARES"))         return Funcao::SUMSQUARES;
    if (!strcmp(funcName, "BRANIN"))             return Funcao::BRANIN;
    if (!strcmp(funcName, "EASOM"))              return Funcao::EASOM;
    if (!strcmp(funcName, "GOLDSTEINPRICE"))     return Funcao::GOLDSTEINPRICE;
    if (!strcmp(funcName, "SHEKEL"))             return Funcao::SHEKEL;
    if (!strcmp(funcName, "HARTMANN"))           return Funcao::HARTMANN;
    if (!strcmp(funcName, "SHUBERT"))            return Funcao::SHUBERT;
    if (!strcmp(funcName, "BEALE"))              return Funcao::BEALE;
    if (!strcmp(funcName, "BOOTH"))              return Funcao::BOOTH;
    if (!strcmp(funcName, "BOHACHEVSKY"))        return Funcao::BOHACHEVSKY;
    if (!strcmp(funcName, "HUMP"))               return Funcao::HUMP;
    if (!strcmp(funcName, "MATYAS"))             return Funcao::MATYAS;
    if (!strcmp(funcName, "SCHWEFEL"))           return Funcao::SCHWEFEL;
    if (!strcmp(funcName, "COLVILLE"))           return Funcao::COLVILLE;
    if (!strcmp(funcName, "PERM"))               return Funcao::PERM;
    if (!strcmp(funcName, "PERM0"))              return Funcao::PERM0;
    if (!strcmp(funcName, "POWERSUM"))           return Funcao::POWERSUM;
    if (!strcmp(funcName, "GRIEWANK"))           return Funcao::GRIEWANK;
    if (!strcmp(funcName, "RASTRIGIN"))          return Funcao::RASTRIGIN;
    if (!strcmp(funcName, "TRID"))               return Funcao::TRID;
    if (!strcmp(funcName, "POWELL"))             return Funcao::POWELL;
    if (!strcmp(funcName, "DIXONPRICE"))         return Funcao::DIXONPRICE;
    if (!strcmp(funcName, "ACKLEY"))             return Funcao::ACKLEY;
    if (!strcmp(funcName, "LEVY"))               return Funcao::LEVY;
    if (!strcmp(funcName, "SPHERE"))             return Funcao::SPHERE;
    if (!strcmp(funcName, "SHIFTEDSPHERE"))      return Funcao::SHIFTEDSPHERE;
    if (!strcmp(funcName, "SHIFTEDSCHWEFEL"))    return Funcao::SHIFTEDSCHWEFEL;
    if (!strcmp(funcName, "SHIFTEDSCHWEFELN"))   return Funcao::SHIFTEDSCHWEFELN;
    if (!strcmp(funcName, "ROTATEDRASTRIGIN"))   return Funcao::ROTATEDRASTRIGIN;
    if (!strcmp(funcName, "ROTATEDWEIERSTRASS")) return Funcao::ROTATEDWEIERSTRASS;
    if (!strcmp(funcName, "ROTATEDEXPSCAFFERS")) return Funcao::ROTATEDEXPSCAFFERS;

    return -1;
}

int getType(char *typeName)
{

    if (!strcmp(typeName, "PURO"))      return PURO;
    if (!strcmp(typeName, "BFGS"))      return BFGS;
    if (!strcmp(typeName, "HIBRIDO"))   return HIBRIDO;

    return -1;
}

inline void closeIfNotNull(FILE *f)
{
    if (f != NULL)
        fclose(f);
}

void saveGaps(real *mediaGaps, int numIter)
{
    FILE *arqlog100 = fopen("gap100.txt", "a+");
    FILE *arqlog500 = fopen("gap500.txt", "a+");
    FILE *arqlog1000 = fopen("gap1000.txt", "a+");
    FILE *arqlog5000 = fopen("gap5000.txt", "a+");
    FILE *arqlog10000 = fopen("gap10000.txt", "a+");
    FILE *arqlog20000 = fopen("gap20000.txt", "a+");
    FILE *arqlog50000 = fopen("gap50000.txt", "a+");

    printf("Media do GAP 100 = %lf \n", mediaGaps[0]/(real)numIter);
    if (arqlog100 != NULL)
        fprintf(arqlog100, "%lf\n", mediaGaps[0]/(real)numIter);

    printf("Media do GAP 500 = %lf \n", mediaGaps[1]/(real)numIter);
    if (arqlog500 != NULL)
        fprintf(arqlog500, "%lf\n", mediaGaps[1]/(real)numIter);

    printf("Media do GAP 1000 = %lf \n", mediaGaps[2]/(real)numIter);
    if (arqlog1000 != NULL)
        fprintf(arqlog1000, "%lf\n", mediaGaps[2]/(real)numIter);

    printf("Media do GAP 5000 = %lf \n", mediaGaps[3]/(real)numIter);
    if (arqlog5000 != NULL)
        fprintf(arqlog5000, "%lf\n", mediaGaps[3]/(real)numIter);

    printf("Media do GAP 10000 = %lf \n", mediaGaps[4]/(real)numIter);
    if (arqlog10000 != NULL)
        fprintf(arqlog10000, "%lf\n", mediaGaps[4]/(real)numIter);

    printf("Media do GAP 20000 = %lf \n", mediaGaps[5]/(real)numIter);
    if (arqlog20000 != NULL)
        fprintf(arqlog20000, "%lf\n", mediaGaps[5]/(real)numIter);

    printf("Media do GAP 50000 = %lf \n", mediaGaps[6]/(real)numIter);
    if (arqlog50000 != NULL)
        fprintf(arqlog50000, "%lf\n", mediaGaps[6]/(real)numIter);

    closeIfNotNull(arqlog100);
    closeIfNotNull(arqlog500);
    closeIfNotNull(arqlog1000);
    closeIfNotNull(arqlog5000);
    closeIfNotNull(arqlog10000);
    closeIfNotNull(arqlog20000);
    closeIfNotNull(arqlog50000);
}



int main(int argc, char **argv)
{
    char *iFuncName;
    int m, info;
    int maxEvals;
    int iFuncNumb, n, numIter;
    int contSucess = 0;
    int type;
    real *x;
    real epsg, epsf, epsx;
    real maxiters = 0;
    long fnEvals, mediaFnEvals = 0;
    long gradEvals, mediaGradEvals = 0;
    bool sucess;
    int64_t initialTime, finalTime;
    int64_t deltaTime, mediaTime = 0;
    ap::real_1d_array xBFGS;
    MGrasp *mgrasp;
    LBFGS *lbfgs;
    Funcao *func;

    real *gaps;
    real mediaGaps[7];

    if (argc < 7) {
        usage();
        return 1;
    }

    epsg = 0.000001;
    epsf = 0.000001;
    epsx = 0.000001;
    maxiters = 0;

    iFuncName   = argv[1];
    iFuncNumb   = getFuncNumb(iFuncName);
    n           = atoi(argv[2]);
    maxEvals    = atoi(argv[3]);
    numIter     = atoi(argv[4]);
    type        = getType(argv[5]);
    m           = atoi(argv[6]);

    if (iFuncNumb == -1) {
        printf("Função %s não existe... \n\n", iFuncName);
        return 1;
    }

    if (type == -1) {
        printf("Tipo %s não existe... \n\n", argv[4]);
        return 1;
    }

    if (m > n) {
        printf("'m' deve ser menor ou igual a 'n' \n\n");
        return 1;
    }

    for (int i = 0; i < 7; i++) {
        mediaGaps[i] = 0.0;
    }

    srand(time(NULL));
    for (int i = 1; i <= numIter; i++) {
        sucess = false;

        printf("[%d]Iteracao \n", i);
        initialTime = getMilisegundos();

        mgrasp = initMGrasp(iFuncNumb, n, &func);

        if (type == PURO) {
            printf("Puro... \n");
            sucess = mgrasp->start(false, m, maxEvals);
        }
        else if (type == HIBRIDO) {
            printf("Hibrido... \n");
            sucess = mgrasp->start(true, m, maxEvals);
        }
        else {
            printf("BFGS... \n");
            x = new real[n];
            mgrasp->unifRandom(x);
            xBFGS.setbounds(1, n);
            for (int j = 0; j < n; j++) {
                xBFGS(j+1) = x[j];
            }
            lbfgs = new LBFGS(func, false);
            lbfgs->minimize(n, m, xBFGS, epsg, epsf, epsx, maxiters, info);

            sucess = true;
            printf("Info = %d \n", info);
        }

        finalTime = getMilisegundos();
        printf("\tTime = %lld \n", finalTime - initialTime);

        if (maxEvals) {
            gaps = mgrasp->getGaps();
            for (int j = 0; j < 7; j++){
                mediaGaps[j] += gaps[j];
                printf("[%d]Gap[%d] = %lf (%lf)... \n", i, j, mediaGaps[j], gaps[j]);
            }
        }
        else if (sucess) {
            contSucess++;
            fnEvals = func->getFnEvals();
            gradEvals = func->getGradEvals();
            deltaTime = finalTime - initialTime;

            mediaFnEvals   += fnEvals;
            mediaGradEvals += gradEvals;
            mediaTime      += deltaTime;
            printf("[%d]Sucesso(%d) = %ld (%d)... \n", i, contSucess, mediaFnEvals, fnEvals);
            printf("[%d]Grad(%d) = %ld (%d)... \n", i, contSucess, mediaGradEvals, gradEvals);
        }
        printf("\n");
        delete mgrasp;
        delete func;
    }

    if (maxEvals) {
        saveGaps(mediaGaps, numIter);
    }
    else {
        printf("Num execucoes com sucesso... = %d \n", contSucess);
        printf("Media de avaliacao da funcao... = %d \n", (long)((real)mediaFnEvals/contSucess));
        printf("Media de avaliacao do gradiente... = %d \n", (long)((real)mediaGradEvals/contSucess));
        printf("Media de tempo... = %d \n", (long)((real)mediaTime/contSucess));
    }

    return 0;
}
