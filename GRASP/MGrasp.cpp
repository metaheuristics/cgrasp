#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits>

#include "MGrasp.h"
#include "Util.h"
#include "real.h"
#include "Dts.h"


MGrasp::MGrasp(int n, real* l, real *u, Funcao *func, real hs,
               real he, real plo)
{
    this->n = n;
    this->l = l;     // esta classe controla os ponteiros l e u
    this->u = u;
    this->func = func;
    this->hs = hs;
    this->he = he;
    this->plo = plo;

    this->contIter   = 0;

    this->xBest      = new real[n];
    this->debug      = DEBUG_LEVEL1_;
    this->dts        = new Dts(n, l, u, func, hs, he);
    this->indexGap   = 0;

    evals[0] = 100;
    evals[1] = 500;
    evals[2] = 1000;
    evals[3] = 5000;
    evals[4] = 10000;
    evals[5] = 20000;
    evals[6] = 50000;
    for (int i = 0; i < 7; i++) {
        gaps[i] = 0.0;
    }
}

MGrasp::~MGrasp()
{
    if (l != NULL) {
        delete[] l;
        l = NULL;
    }

    if (u != NULL) {
        delete[] u;
        u = NULL;
    }

    if (dts != NULL) {
        delete dts;
        dts = NULL;
    }

    if (xBest != NULL) {
        delete []xBest;
        xBest = NULL;
    }
}

real *MGrasp::getXBest()
{
    return xBest;
}

real *MGrasp::getGaps()
{
    return gaps;
}


// Se o criterio de parada foi atingido returna 'true'.
// Senao retorna 'false'.
bool MGrasp::stopCriteria()
{
    contIter++;

    if (func->isNearOptimum(fBest)) {
        if (debug ==  DEBUG_LEVEL1_) {
            printf("Achou o OTIMO... \n");
            printf("Num FnEvals = %d \n\n\n", func->getFnEvals());
        }
        return true;
    }

    if (contIter > MAX_ITERACOES) {
        return true;
    }

    return false;
}


// Seleciona um inteiro 'j' de 0 a (tamanho da lista-1) e
// retorna o valor desse elemento da lista (*j);
int MGrasp::randSelectElement(std::list<int> rcl)
{
    // Gera um numero aleatorio de 0 a rcl.size()-1
    //real r = dRand();
    real r = Util::dRand();
    int rElement = (int)(r * (real)(rcl.size()));

    int cont = 0;
    for (std::list<int>::iterator i = rcl.begin(); i != rcl.end(); i++) {
        if (cont == rElement) {
            return *i;
        }
        cont++;
    }

    return -1;
}


// Gera uma solucao aleatoria no intervalo l, u.
void MGrasp::unifRandom(real *xAux)
{
    real r;

    // Para os n indices gera
    for (int i = 0; i < n; i++) {
        // Gera um numero de ponto flutuante entre 0 e 1
        r = Util::dRand();
        // Pega o numero aleatorio e coloca ele na faixa de valores da funcao
        xAux[i] = l[i] + (r * (u[i] - l[i]));
    }

    return;
}


// Numa busca linear, faz-se uma busca na direcao p(k) e quao distante eh aquela busca(tamanho do passo,
// definido por a(k). Entao, o movimento gerado numa busca linear eh x(k+1) = x(k) + a(k)*p(k).
// No caso do C-Grasp, a busca sera realizada na direcao de 'i' com tamanho de passo 'h';
/* real MGrasp::linearSearch(real *x, int i, real *gI, real h)
{
   bool melhorou = false;

   real *xAux = new real[n];
   real xAuxI;
   real valX, valLinear;
   real auxPos, auxNeg;
   int numIter, numIterPos, numIterNeg;

   valX = func->calc(x);
   xAuxI = x[i];
   melhorou = false;
   auxPos = ((u[i] - x[i])/h);
   auxNeg = ((x[i] - l[i])/h);

   numIterPos = (int) auxPos;
   numIterNeg = (int) auxNeg;

   numIter = (numIterPos > numIterNeg) ? numIterPos : numIterNeg;
   //printf("NumIterPos = %d \n", numIterPos);
   //printf("NumIterNeg = %d \n", numIterNeg);
   //printf("NumIter = %d \n", numIter);


   for (int j = 0; j < numIterPos; j++){
   xAux[i] = x[i] + ((real) (1+j)*h);
   //printf("P [%d]Passo = %lf - XAux[%d] = %lf \n",i, j+h*k*0.2, i, xAux[i]);

   // Busca linear pode produzir pontos fora dos limites da funcao.
   if (xAux[i] > u[i]){
   break;
   }

   valLinear = func->calc(xAux);
   //printf("\tP - ValX = %lf - (%lf) \n",valX, xAuxI);
   //printf("\tP - ValLinear = %lf - (%lf) \n",valLinear, xAux[i]);
   if (valLinear < valX){
   //printf("P - Melhorou ValX... %lf \n", valLinear);
   xAuxI = xAux[i];
   valX = valLinear;
   melhorou = true;
   //break;
   }
   }

   for (int j = 0; j < numIterNeg; j++){
   xAux[i] = x[i] - ((real) (1+j)*h);
   //printf("P [%d]Passo = %lf - XAux[%d] = %lf \n",i, j+h*k*0.2, i, xAux[i]);

   // Busca linear pode produzir pontos fora dos limites da funcao.
   if (xAux[i] < l[i]){
   break;
   }

   valLinear = func->calc(xAux);
   //printf("\tP - ValX = %lf - (%lf) \n",valX, xAuxI);
   //printf("\tN - ValLinear = %lf - (%lf) \n",valLinear, xAux[i]);
   if (valLinear < valX){
   //printf("N - Melhorou ValX... %lf \n", valLinear);
   xAuxI = xAux[i];
   valX = valLinear;
   melhorou = true;
   //break;
   }
   }

   //printf("XAux[%d] = (%lf) = %lf", i, xAuxI, valX);

   delete []xAux;
   *gI = valX;
   return xAuxI;
   }*/

real MGrasp::linearSearch(real *x, int i, real *gI, real h)
{
    real *xAux = new real[n];
    real valX, xAuxI;
    real min;

    Util::copy(xAux, x, n);
    xAux[i] = l[i];

    min = std::numeric_limits<real>::max();
    //min = func->calc(x);
    while( (xAux[i] < u[i]) || (Util::equals(xAux[i],u[i])) ) {
        valX = func->calc(xAux);
        //printf("X "); Util::printX(xAux, n);
        //printf(" = %lf \n", valX);
        if (min > valX){
            min = valX;
            xAuxI = xAux[i];
        }

        xAux[i] += h;
    }

    //printf("\n");
    *gI = min;

    delete []xAux;
    return xAuxI;
}

// Etapa de construcao do C-Grasp
bool MGrasp::constructGreedyRandom(real *x, real h)
{
    int j;

    bool reuse = false;
    bool imprC = false;

    real *xAux, *g, *z;
    real gMin, gMax;
    real alpha;
    real threshold;
    std::list<int> unfixed;
    std::list<int> rcl;

    real fXInit = func->calc(x);
    // unfixed = {1,2...,n}
    for (int j = 0; j < n; j++) {
        unfixed.push_back(j);
    }

    // Gera um numero de ponto flutuante entre 0 e 1
    //alpha = dRand();
    alpha = Util::dRand();
    if (debug ==  DEBUG_LEVEL2_) {
        printf("Alpha = %lf \n", alpha);
    }

    z = new real[n];
    g = new real[n];

    // Enquanto lista nao vazia
    while(unfixed.size() > 0) {
        gMin = std::numeric_limits<real>::max();
        gMax = std::numeric_limits<real>::min();

        for (std::list<int>::iterator i = unfixed.begin(); i != unfixed.end(); i++) {
            if (!reuse) {
                z[*i] = linearSearch(x,*i, &(g[*i]), h);
                if (debug ==  DEBUG_LEVEL2_){
                    printf("z[%d] = %lf - g[i] = %lf \n", *i, z[*i], g[*i]);
                }
                if (gMin > g[*i]) {
                    gMin = g[*i];
                }
                if (gMax < g[*i]) {
                    gMax = g[*i];
                }
            }
        }

        rcl.clear();
        threshold = gMin + alpha * (gMax - gMin);

        if (debug ==  DEBUG_LEVEL2_) {
            printf("gMin = %lf \n", gMin);
            printf("gMax = %lf \n", gMax);
            printf("threshold = %lf \n", threshold);
        }

        for (std::list<int>::iterator k = unfixed.begin(); k != unfixed.end(); k++) {
            if ((g[*k] < threshold) || Util::equals(g[*k], threshold)){
                if (debug ==  DEBUG_LEVEL2_){
                    printf("Adiciona %d na RCL\n", *k);
                }
                rcl.push_back(*k);
            }
        }

        j = randSelectElement(rcl);
        if (debug ==  DEBUG_LEVEL2_) {
            printf("Selecionando %d da lista unfixed \n\n", j);//DEBUG:
        }

        if (!Util::equals(x[j], z[j])) {
            reuse = false;
            x[j] = z[j];
            //imprC = true;
        }
        else{
            if (debug ==  DEBUG_LEVEL2_) {
                printf("x[%d] == z[%d] \n", j,j);//DEBUG:
            }
            reuse = true;
        }

        for (std::list<int>::iterator w = unfixed.begin(); w != unfixed.end(); w++) {
            if (*w == j){
                if (debug ==  DEBUG_LEVEL3_) {
                    printf("Retirando %d da lista unfixed \n\n", *w);//DEBUG:
                }
                unfixed.erase(w);
                break;
            }
        }
    }

    if (func->calc(x) < fXInit) {
        imprC = true;
    }


    rcl.clear();
    unfixed.clear();
    delete []z;
    delete []g;
    return imprC;
}


void MGrasp::randSelectElementBh(real *x, real *xBestAux, real h)
{
    int auxI;
    real gridI;
    real numPointsPos, numPointsNeg;
    real numPoints = 0.0;
    real r, normaVector;
    real *xGrid = new real[n];
    real *bhSelected = new real[n];
    real aux = 0.0, distancia = 0.0;

    // Escolhe aleatoriamente um ponto do Grid de tamanho de passo h.
    for (int i = 0; i < n; i++) {
        // Calcula o numero de pontos naquela direcao com tamanho de passo h.
        numPointsPos = floor((u[i] - xBestAux[i])/h);
        numPointsNeg = floor((xBestAux[i] - l[i])/h);

        numPoints = numPointsPos + numPointsNeg;

        // Escolhe aleatoriamente um dos indices do Grid na direcao i.
        //r = dRand();
        r = Util::dRand();
        auxI = (int)(r * (real)numPoints);

        gridI = ((real)auxI - numPointsNeg);

        // Calcula a posicao da direcao no eixo i.
        xGrid[i] = xBestAux[i] + ((real)gridI*h);
    }

    // Calcula a projecao do vetor de x a xGrid.
    normaVector = Util::calcNorma(xBestAux, xGrid, n);
    for (int i = 0; i < n; i++) {
        bhSelected[i] = xBestAux[i] + ((h* (xGrid[i]- xBestAux[i]))/normaVector);
        //aux += pow((bhSelected[i] -xBestAux[i]), 2);
    }

    if (debug ==  DEBUG_LEVEL4_) {
        printf("\tBhSelected = "); Util::printX(bhSelected,n);
        printf(" = %lf \n\n", func->calc(bhSelected));
    }
    //distancia = sqrt(aux);
    //printf("Distancia = %lf \n", distancia);

    Util::copy(x, bhSelected, n);
    delete []xGrid;
    delete []bhSelected;
    return;
}


bool MGrasp::verifyGap(real fX, int maxEvals)
{
    if (maxEvals && (func->getFnEvals() > evals[indexGap])) {
        if (fX < fBest) {
            fBest = fX;
            func->setBestValue(fBest);
        }
        gaps[indexGap] = func->getGap();
        indexGap++;
    }

    if (indexGap == 7) {
        return true;
    }

    return false;
}



bool MGrasp::start(bool hibrid, int m, int maxEvals)
{
    real *x = new real[n];
    real fX, fXAnt;
    real h;
    bool imprC;
    bool imprL;
    int cont = 0;
    real epsg, epsf, epsx;
    ap::real_1d_array xBFGS;
    int info;
    LBFGS *lbfgs = NULL;

    real maxiters = 0.0;
    if (hibrid) {
        epsg = 0.000001;
        epsf = 0.000001;
        epsx = 0.000001;
        maxiters = 0;
        lbfgs = new LBFGS(func, false);
    }

    fBest = std::numeric_limits<real>::max();
    fXAnt = fBest;
    while (!stopCriteria()) {
        unifRandom(x);
        h = hs;
        if (debug ==  DEBUG_LEVEL1_) {
            printf("\tNovo start point "); Util::printX(x,n);
            printf(" = %lf \n\n", func->calc(x));
        }

        while (h > he || Util::equals(h,he)) {
            imprC = false;
            imprL = false;
            if (debug ==  DEBUG_LEVEL2_) {
                printf("H... = %lf\n", h);
            }

            imprC = constructGreedyRandom(x,h);
            if (debug ==  DEBUG_LEVEL2_) {
                printf("\tConstrucao "); Util::printX(x,n);
                printf(" = %lf (%d) \n", func->calc(x), func->getFnEvals());
            }

            fX = func->calc(x);
            if (verifyGap(fX, maxEvals)) {
                delete[] x;
                return false;
            }

            // Incluido apenas para teste
            if (fX == fXAnt) {
                h /= 2.0;
                //unifRandom(x);
                //printf("\n\tPerturbando o ponto..."); Util::printX(x,n);
                //printf(" = %lf \n\n", func->calc(x));
            }
            fXAnt = fX;

            imprL = dts->explorationSearch(x, &fX, h);
            if (debug ==  DEBUG_LEVEL2_) {
                printf("\tLocal "); Util::printX(x,n);
                printf(" = %lf (%d)\n", func->calc(x), func->getFnEvals());
            }

            if (verifyGap(fX, maxEvals)) {
                delete[] x;
                return false;
            }

            if (debug ==  DEBUG_LEVEL2_) {
                printf("ImprC = %d - ImprL = %d...\n\n\n", imprC, imprL);
            }

            if (fX < fBest) {
                Util::copy(xBest, x, n);
                fBest = fX;
                func->setBestValue(fBest);

                if (debug >=  DEBUG_LEVEL1_) {
                    printf("\tXBest "); Util::printX(xBest,n);
                    printf(" = %lf (%d)\n\n", fBest, func->getFnEvals());
                }

                if (func->isNearOptimum(fBest)) {
                    if (debug >=  DEBUG_LEVEL1_) {
                        printf("Achou o OTIMO = %d... \t", cont);
                        printf("Num FnEvals = %d \n\n\n", func->getFnEvals());
                    }
                    delete []x;
                    return true;
                }
            }


            if ((!imprC) && (!imprL)) {
                if (hibrid) {
                    if (debug >=  DEBUG_LEVEL1_) {
                        printf("\tVai chamar BFGS = %lf \n", fBest);
                        printf("\tChamando L-BFGS... \n");
                    }
                    xBFGS.setbounds(1, n);
                    for (int j = 0; j < n; j++) {
                        xBFGS(j+1) = x[j];
                    }

                    lbfgs->minimize(n, m, xBFGS, epsg, epsf, epsx, maxiters, info);
                    for (int j = 0; j < n; j++) {
                        x[j] = xBFGS(j+1);
                    }

                    fX = func->calc(x);
                    printf("\tFx = %lf (%d)\n\n", fX);
                    if (verifyGap(fX, maxEvals)) {
                        delete[] x;
                        return false;
                    }

                    real *grad = new real[n];
                    ap::real_1d_array g;
                    g.setbounds(1, n);
                    func->calcGrad(xBFGS,g);

                    for (int j = 0; j < n; j++) {
                        grad[j] = g(j+1);
                    }
                    printf("\tNorma do Gradiente = %lf\n", Util::calcNorma(grad, n));

                    if (func->isNearOptimum(fX)){
                        if (debug >=  DEBUG_LEVEL1_){
                            printf("Achou o OTIMO = %d... \t", cont);
                            printf("Num FnEvals = %d \n\n\n", func->getFnEvals());
                        }
                        delete []x;
                        return true;
                    }
                }

                h /= 2.0;
            }

            cont++;
        }
    }

    if (lbfgs != NULL)
        delete lbfgs;

    delete[] x;
    return false;
}
