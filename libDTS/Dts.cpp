#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits>

#include "Dts.h"
#include "Util.h"


 Dts::Dts(int n, double* l, double *u, Funcao *func, double hs, double he){
 	this->n = n;
 	this->l = l;
 	this->u = u;
 	this->func = func;
 	this->hs = hs;
 	this->he = he;
 
 
	this->debug = DEBUG_LEVEL1_;
 
	tl  = new TabuList(5*n, n);
  	rSTR = hs/2.0;
	rTR  = hs/4.0;
 }

 Dts::~Dts(){
	delete tl;	 	
 }

 double *Dts::goldenSearch(double *x, double *v, double *fXAux, double h, bool *imprL){
	bool melhorou = false;
	double valA, valB;
	double valC, valD;
	double ratio1, ratio2;
	double *xAux = new double[n];
	double *xA = new double[n];
	double *xB = new double[n];
	double *xC = new double[n];
	double *xD = new double[n];
	
	double *dir = new double[n];
	double normaDir = Util::calcNorma(v, n);
	for (int i = 0; i < n; i++){
		dir[i] = v[i]/normaDir;
	}

	Util::copy(xAux	, x, n);
	//printf("X (%lf, %lf) = %lf \n", x[0], x[1], valX);
	
	Util::copy(xA, x, n);
	
	ratio1 = ((sqrt(5.0) - 1.0)/2.0);
	ratio2 = ratio1*ratio1;
	
	for (int i = 0; i < n; i++){
		xB[i] = xA[i] + dir[i]*h;
	
		//c = r*a + (1-r)*b;
		//d = (1-r)*a + b;
 		xC[i] = xA[i] + dir[i]*ratio2*h; 
		xD[i] = xA[i] + dir[i]*ratio1*h; 
	}
	
	valA  = func->calc(xA);
	valB  = func->calc(xB);
 	valC = func->calc(xC);
	valD = func->calc(xD);
	if (debug ==  DEBUG_LEVEL2_){	
		printf("Ratio1 = %lf - Ratio2 = %lf \n", ratio1, ratio2);
		
		printf("\tXa "); Util::printX(xA, n);
		printf(" = %lf \n", valA);

		printf("\tXb "); Util::printX(xB, n);
		printf(" = %lf \n", valB);

		printf("\tXc "); Util::printX(xC, n);
		printf(" = %lf \n", valC);

		printf("\tXd "); Util::printX(xD, n);
		printf(" = %lf \n", valD);
	}
	
 	// Calcula c e d e ve qual é o menor valor. Se c for menor o novo intervalo eh
 	// [x,c], senao o novo intervalo eh [d, x+h]
 	while(h >= he){
 		//printf("hGold... = %lf \n", h);
 		if (valC < valD){
			if (debug ==  DEBUG_LEVEL2_){
 				printf("ValC < ValD \n");
			}	
 			// Agora o limite superior 'B' será o ponto 'D'.
 			Util::copy(xB, xD, n);
 			valB = valD;
 			
 			// Agora o ponto interior 'D' sera o ponto 'C'.
 			Util::copy(xD, xC, n); 
 			valD = valC;
 			
			//h = xB[i] - xA[i];
 			h = Util::dist(xA, xB, n);
 			
			// Calcula-se um novo ponto interior 'C'.
 			for (int i = 0; i < n; i++){
				xC[i] = xA[i] + dir[i]*ratio2*h;
			}
 			valC = func->calc(xC);

			if (debug ==  DEBUG_LEVEL2_){
				printf("\tNovo Xb "); Util::printX(xB, n);
				printf(" = %lf \n", valB);

				printf("\tNovo Xd "); Util::printX(xD, n);
				printf(" = %lf \n", valD);
	
				printf("\tNovo Xc "); Util::printX(xC, n);
				printf(" = %lf \n", valC);

				printf("Novo h = %lf \n", h);
			} 			
	
		}
 		else{
			if (debug ==  DEBUG_LEVEL2_){
			 	printf("ValC > ValD \n");
			}		
 			// Agora o limite superior 'B' será o ponto 'D'.
 			Util::copy(xA, xC, n);
 			valA = valC;
		
 			// Agora o ponto interior 'D' sera o ponto 'C'.
 			Util::copy(xC, xD, n); 
 			valC = valD;
			
 			//h = xB[i] - xA[i];
 			h = Util::dist(xA, xB, n);
 			
			// Calcula-se um novo ponto interior 'C'.
 			//xD[i] = xA[i] + ratio1*h;
			for (int i = 0; i < n; i++){
				xD[i] = xA[i] + dir[i]*ratio1*h;
			} 			
		
			valD = func->calc(xD);
			
			if (debug ==  DEBUG_LEVEL2_){
				printf("\tNovo Xa "); Util::printX(xA, n);
				printf(" = %lf \n", valA);

				printf("\tNovo Xc "); Util::printX(xC, n);
				printf(" = %lf \n", valC);
	
				printf("\tNovo Xd "); Util::printX(xD, n);
				printf(" = %lf \n", valD);

				printf("Novo h = %lf \n", h);
			}		
	
		}
		
		if (valA < valB){
 			if (valA < *fXAux){
				if (debug ==  DEBUG_LEVEL2_){
					printf("\tXa é menor = "); Util::printX(xA, n);
					printf(" = %lf \n", valA);
			 	}
	
 				*fXAux= valA;
 				Util::copy(xAux, xA, n);
				//*imprL = true;
 				break;
 			}
 		}
 		else{
 			if (valB < *fXAux){
				if (debug ==  DEBUG_LEVEL2_){
					printf("\tXb é menor = "); Util::printX(xB, n);
					printf(" = %lf \n", valB);
			 	}
 				*fXAux = valB;
 				Util::copy(xAux, xB, n);
				//*imprL = true;
				break;
 			}
 		}	
	}
 	
 	delete []xA;
 	delete []xB;
 	delete []xC;
 	delete []xD;
 	delete []dir;
 	
 	//printf("\n\n\n");
 	return xAux;
 }



 double *Dts::calcCentroide(double *x, double *dMax){
	double *centroide, nCentroide;
	double *xSTR, dist;	
	
	if (debug ==  DEBUG_LEVEL4_){	
		printf("\tXNaSemi-TR ");
		Util::printX(x, n);
		printf(" \n");
	}

	// Inicializa os parametros
	*dMax = std::numeric_limits<double>::min();	
	centroide = new double[n];
	nCentroide = 0.0;		
	for (int i = 0; i < n; i++){
		centroide[i] = 0.0;	
	}
		
	// Calcula o centroide dos centros das regioes Semi-TR e 
	// a distancia maxima entre x e esses centros (dMax).
	for (int i = 0; i < tl->getNumberElements(); i++){
		xSTR = tl->getX(i);	
		if (debug ==  DEBUG_LEVEL4_){	
			printf("\tXSTR[%d] ", i);
			Util::printX(xSTR, n);
			printf(" \n");
		}
				
		if (tl->isSemiTR(xSTR, x, rSTR)){
			if (debug ==  DEBUG_LEVEL4_){	
				printf("\tNa STR = [%d] \n", i);
			}
	
			for (int i = 0; i < n; i++){
				centroide[i] += xSTR[i];	
			}	
			nCentroide += 1.0;			
			dist = Util::dist(xSTR, x, n);
			if (dist > *dMax){
				*dMax = dist;
			}
		}
	}
		
	for (int i = 0; i < n; i++){
		centroide[i] /= nCentroide;	
	}

	if (debug ==  DEBUG_LEVEL4_){	
		printf("\t Centroide ");
		Util::printX(centroide, n);
		printf(" \n\n\n");
	}

	return centroide;
 }

 
 bool Dts::neighborhoodSearch(double *x, double *fXAux, double h, double *dir){
	
	double **y = new double *[n];
	double **U = new double *[n];
	double *w = new double [n];
	double *fY = new double [n];
	double *deltafY  = new double [n];
	double *stepSize = new double [n];
	double totalfY = 0.0;
	double normaY, sign, signAux;	
	double r, dMax;	
	double *centroide; 
	
	bool imprL = false;	
	double fX;	
	double *xAux = new double[n];	
	double *xBestAux = new double[n];	


	// Se o ponto esta em alguma Semi-TR, aplique o procedimento semiTRSearch.
	//if (tl->isAnySemiTR(x, rSTR)){
	if (0){
		if (debug ==  DEBUG_LEVEL4_){	
			printf("\tCaiu na regiao Semi-TR\n");
		}
		
		centroide = calcCentroide(x, &dMax);				
		for (int i = 0; i < n; i++){
			sign = 	(x[i] - centroide[i] >= 0) ? 1.0: -1.0;		
			stepSize[i] = (double)h*sign;			
		}
		
		if (debug ==  DEBUG_LEVEL4_){	
			printf("\tStepSize ");
			Util::printX(stepSize, n);
			printf(" \n");
		}

		/*double norma = Util::calcNorma(centroide, x, n);
		for (int i = 0; i < n; i++){
			dir[i] = (x[i] - centroide[i])/norma;
			if (debug ==  DEBUG_LEVEL4_){	
				printf("Dir[%d] = %lf \n", i, dir[i]);		
			}		
		}*/	
					
	}
	// Senao aplique o método APS.
	else{
		for (int i = 0; i < n; i++){
			// Gera um numero de ponto flutuante entre 0 e 1
 			r = Util::dRand();
			signAux = (int)(r * (double)2);
			sign = (!signAux) ? 1.0 : -1.0;			
			stepSize[i] = (double)h*sign;  
		}
	}

	// Calcula os y[i] e os fY[i]
	for (int i = 0; i < n; i++){
		U[i] = new double[n];
		y[i] = new double[n];
		Util::copy(y[i], x, n);
		
		y[i][i] += stepSize[i];		
		fY[i] = func->calc(y[i]);
		
		// O ponto de vizinhança y[i] é melhor que o ponto atual x.
		// Então retorne o ponto y[i];		
		if (fY[i] < *fXAux){
			if (debug ==  DEBUG_LEVEL4_){	
				printf("Y[%d] ", i);
				Util::printX(y[i], n);
				printf(" = %lf \n", fY[i]);
			}			
			Util::copy(x, y[i], n);
			*fXAux = fY[i];

			for (int j = 0; j <= i; j++){
				delete []U[j];
				delete []y[j];
			}		
			delete []U;
			delete []y;
			delete []w;
			delete []fY;	
			delete []deltafY;
			delete []stepSize;
			delete []xBestAux;
			delete []xAux;
			return true;		
		}		
		
		deltafY[i] = fY[i] - *fXAux;	
		totalfY += fabs(deltafY[i]);	
			
		if (debug ==  DEBUG_LEVEL4_){	
			printf("Y[%d] ", i);
			Util::printX(y[i], n);
			printf(" = %lf \n", fY[i]);
		
			printf("DeltaFY[%d] = %lf - TotalFy = %lf \n", i, deltafY[i], totalfY);
		}	
	}
 
	// Calcula os w[i] e os u[i];	
	for (int i = 0; i < n; i++){
		w[i] = deltafY[i] / totalfY;	
		
		normaY = Util::calcNorma(x, y[i], n);
		for (int j = 0; j < n; j++){
			U[i][j] = - (y[i][j] - x[j]) / normaY;  
		}
	
		if (debug ==  DEBUG_LEVEL4_){	
			printf("W[%d] = %lf\n", i, w[i]);
			printf("Norma[%d] = %lf\n", i, normaY);		
			printf("U[%d] ", i);
			Util::printX(U[i], n);
			printf("\n");
		}
	}

	//Calcula a direção de descida d.
	for (int i = 0; i < n; i++){
		dir[i] = 0.0;		
		for (int j = 0; j < n; j++){
			dir[i] += (w[j]*U[j][i]);  
		}
	}

	double norma = Util::calcNorma(dir,n);
	for (int i = 0; i < n; i++){
		dir[i] /= norma; 
	}	
	
	if (debug ==  DEBUG_LEVEL4_){	
		printf("Dir "); Util::printX(dir, n);		
		printf(" = %lf \n", Util::calcNorma(dir,n)); 		
	}	
	//}


	// Escolhe o melhor dos pontos Y
	double fXAtual = *fXAux;
	*fXAux = std::numeric_limits<double>::max();	
	for (int k = 0; k < n; k++){
		if (fY[k] < *fXAux){
			Util::copy(xBestAux, y[k], n);
			*fXAux = fY[k];
			//imprL = true;
			if (debug ==  DEBUG_LEVEL4_){	
				printf("\tLocalMelhorou "); Util::printX(xBestAux,n);  				 	
				printf(" = %lf \n\n", *fXAux);
 			}
		}
	}
	
	// Faz a busca local na direção 'dir' e escolhe o melhor ponto
	/*for (int k = 0; k < 2; k++){
		Util::copy(x, xAux, n);
		for (int i = 0; i < n; i++){
			x[i] += h*dir[i];
		}			
		
		if ((Util::feasible(x, l, u, n)) && ((fX = func->calc(x)) < *fXAux)){
			Util::copy(xBestAux, x, n);
			*fXAux = fX;
			//imprL = true;
			if (debug ==  DEBUG_LEVEL4_){	
				printf("\tLocalMelhorou "); Util::printX(xBestAux,n);  				 	
				printf(" = %lf \n\n", *fXAux);
 			}	
		}

		h /= 2.0;
	}*/
	fX = func->calc(x);
	if (xAux != NULL){
		delete []xAux;
		xAux = NULL;
	}

	xAux = goldenSearch(x, dir, &fX, h, &imprL);
	if ((Util::feasible(xAux, l, u, n)) && (fX < *fXAux)){
		Util::copy(xBestAux, xAux, n);
		*fXAux = fX;
	} 

	Util::copy(x, xBestAux, n);
	if (*fXAux < fXAtual){
		imprL = true;
	} 

	for (int j = 0; j < n; j++){
		delete []U[j];
		delete []y[j];
	}		
	delete []U;
	delete []y;
	delete []w;
	delete []fY;	
	delete []deltafY;
	delete []stepSize;
	delete []xBestAux;
	delete []xAux;

	return imprL;	
	//return false;
 }

/*
 bool Dts::localSearch(double *x, double *fXAux, double h, double *dir){
	bool imprL = false;	
	double fX;	
	double *xAux = new double[n];	
	double *xBestAux = new double[n];	

	Util::copy(xAux, x, n);
	Util::copy(xBestAux, x, n);
	
	*fXAux = std::numeric_limits<double>::max();	
	//*fXAux = func->calc(x);	
	//xBestAux = goldenSearch(x, dir, fXAux, h, &imprL);	
			
	for (int k = 0; k < 2; k++){
		Util::copy(x, xAux, n);
		for (int i = 0; i < n; i++){
			x[i] += h*dir[i];
		}			
		
		if ((Util::feasible(x, l, u, n)) && ((fX = func->calc(x)) < *fXAux)){
			Util::copy(xBestAux, x, n);
			*fXAux = fX;
			imprL = true;
			if (debug ==  DEBUG_LEVEL4_){	
				printf("\tLocalMelhorou "); Util::printX(xBestAux,n);  				 	
				printf(" = %lf \n\n", *fXAux);
 			}	
		}

		h /= 2.0;
	}

	Util::copy(x, xBestAux, n);
	return imprL;	
 }*/
	

 void Dts::perturbe(double *x, double *xBestAux, double h){
	int auxI;
	double gridI; 
	double numPointsPos, numPointsNeg;
	double numPoints = 0.0;
	double r, normaVector;
	double *xGrid = new double[n];
	double *bhSelected = new double[n];
	double aux = 0.0, distancia = 0.0;
		
	// Escolhe aleatoriamente um ponto do Grid de tamanho de passo h.
	for (int i = 0; i < n; i++){
		// Calcula o numero de pontos naquela direcao com tamanho de passo h.
		numPointsPos = floor((u[i] - xBestAux[i])/h);
 		numPointsNeg = floor((xBestAux[i] - l[i])/h);
				
		numPoints = numPointsPos + numPointsNeg;
	
		// Escolhe aleatoriamente um dos indices do Grid na direcao i.
		//r = dRand();
		r = Util::dRand();
		auxI = (int)(r * (double)numPoints);
	
		gridI = ((double)auxI - numPointsNeg); 
					
		// Calcula a posicao da direcao no eixo i.
		xGrid[i] = xBestAux[i] + ((double)gridI*h);
	}
	
	// Calcula a projecao do vetor de x a xGrid.
	normaVector = Util::calcNorma(xBestAux, xGrid, n); 
	for (int i = 0; i < n; i++){
		bhSelected[i] = xBestAux[i] + ((h* (xGrid[i]- xBestAux[i]))/normaVector);
		//aux += pow((bhSelected[i] -xBestAux[i]), 2); 
	}

	if (debug ==  DEBUG_LEVEL4_){
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
 
 // Etapa de exploração do DTS
 bool Dts::explorationSearch(double *x, double *fXAux, double h){
	bool imprL = false;
	bool imprN = false;	
	double *dir = new double[n];;
	double fXBest, *xBest = new double[n];	
	double min;
	int NumIterNoImprov = 0, MaxItersNoImprov = 2*n;
	//int NumIterNoImprov = 0, MaxItersNoImprov = n*n;

 	rSTR = h/2.0;
	rTR  = h/4.0;

	*fXAux = func->calc(x);
	fXBest = *fXAux;
	Util::copy(xBest, x, n);		
	if (debug ==  DEBUG_LEVEL4_){	
		printf("X ");
		Util::printX(x, n);
		printf(" = %lf \n", *fXAux);
	}
	
	while (NumIterNoImprov < MaxItersNoImprov){		
		NumIterNoImprov++;
		
		imprN = neighborhoodSearch(x, fXAux, h, dir);	
		if (debug ==  DEBUG_LEVEL2_){	
			printf("\t\tDtsX "); //Util::printX(x, n);
			printf(" = %lf \n", *fXAux);
		}	
		
		if (Util::feasible(x,l,u,n) && ((*fXAux) < fXBest)){
			//printf("Melhorando local... %lf - %lf (%d) \n", *fXAux, fXBest, imprN);
			fXBest = *fXAux;
			Util::copy(xBest, x, n);
			imprL = true;
			NumIterNoImprov = 0;		
		}
		else{
			perturbe(x, xBest, h);			
			*fXAux = func->calc(x);			
			if (debug ==  DEBUG_LEVEL2_){	
				printf("\t\tDtsPert %lf \n", *fXAux);
			}
		}
	
		//*fXAux = fXBest;
		//Util::copy(x, xBest, n);		
	}	
		
	*fXAux = fXBest;
	Util::copy(x, xBest, n);		
	if (debug ==  DEBUG_LEVEL4_){	
		printf("\tXFinal ");
		Util::printX(x, n);
		printf(" = %lf \n", *fXAux);
	}	

	delete []xBest;
	delete []dir;
	
	return imprL;
 }
