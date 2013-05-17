#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "real.h"
#include "TabuList.h"
#include "Util.h"


TabuList::TabuList(int length, int n)
{
    // Aloca um elemento a mais para poder dar um shift na hora da reordenacao.
    this->list = new TlElement *[length+1];
    this->length = length;
    this->n = n;
    this->numElements = 0;

    // TODO: Utilizar tanto a ordem de visita (recency) quanto o valor da função objetivo (function_value).
    // Por enquanto, está utilizando apenas a ordem de visita.
    this->nMax = 1.0;
    this->uMax = 1.0;
    this->nMin = (real)(1.0/(real)length);
    this->uMin = (real)(1.0/(real)length);
}

TabuList::~TabuList()
{
    for (int i = 0; i < numElements; i++) {
        delete list[i];
    }

    delete []list;
}

int TabuList::getNumberElements()
{
    return numElements;
}

int TabuList::getLength()
{
    return length;
}

TlElement *TabuList::getElement(int i){
    if (i > numElements) {
        return NULL;
    }

    return this->list[i];
}

real *TabuList::getX(int i)
{
    if (i > numElements) {
        return NULL;
    }

    return list[i]->getX();
}

bool TabuList::isSemiTR(real *xSTR, real *x, real rSTR)
{
    // Se a distancia de x para o ponto da lista tabu for menor ou igual
    // ao raio da regiao Semi-TR (rSTR), entao ele esta na regiao Semi-TR.
    if (Util::dist(xSTR, x, n) <= rSTR) {
        return true;
    }

    return false;
}


bool TabuList::isAnySemiTR(real *x, real rSTR)
{
    // Desloca todos os elementos uma posicao para a direita.
    for (int i = 0; i < numElements; i++) {
        if (isSemiTR(list[i]->getX(), x, rSTR)) {
            return true;
        }
    }

    return false;
}

void TabuList::insertElement(real *x, int n, int fX)
{
    TlElement *elem = new TlElement(x, n, fX);

    if (!numElements) {
        list[0] = elem;
        numElements++;
        return;
    }

    // Desloca todos os elementos uma posicao para a direita.
    for (int i = numElements-1; i >= 0; i--) {
        list[i+1] = list[i];
    }

    list[0] = elem;
    if (numElements < length) {
        numElements++;
    }
    else {
        delete list[numElements];
    }
}

bool TabuList::isInList(real *x, int n)
{
    real *xList;
    if (!numElements) {
        return false;
    }

    for (int i = 0; i < numElements; i++) {
        xList = list[i]->getX();
        for (int j = 0; j < n; j++) {
            if (!Util::equals(x[j], xList[j])) {
                return false;
            }
        }
    }

    return true;
}

void TabuList::clear()
{
    for (int i = 0; i < numElements; i++) {
        delete list[i];
    }

    numElements = 0;
}
