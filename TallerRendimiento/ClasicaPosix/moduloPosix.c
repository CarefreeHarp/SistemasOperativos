/*#######################################################################################
#* Fecha:
#* Autor: J. Corredor, PhD
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/

#include "moduloPosix.h"

double *matrixA, *matrixB, *matrixC;
struct timeval inicio, fin;

void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}


void iniMatrix(double *m1, double *m2, int D){ 
	for(int i = 0; i < D*D; i++, m1++, m2++){
			*m1 = 1 + (double)rand()/RAND_MAX*(5.0-1.0);
			*m2 = 5 + (double)rand()/RAND_MAX*(9.0-5.0);
		}	
}

void impMatrix(double *matriz, int D){
	if(D < 9){
    		for(int i = 0; i < D*D; i++){
     				if(i%D==0) printf("\n");
            		printf(" %.2f ", matriz[i]);
			}	
    	printf("\n>-------------------->\n");
	}
}

void *multiMatrix(void *variables){
	struct parametros *data = (struct parametros *)variables;
	
	int idH		= data->idH;
	int nH		= data->nH;
	int D		= data->N;
	int filaI = (D * idH) / nH; 
	int filaF = (D * (idH + 1)) / nH;
	double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
			pA = matrixA + i*D; 
			pB = matrixB + j;
			Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB+=D){
				Suma += *pA * *pB;
			}
			matrixC[i*D+j] = Suma;
		}
	}

	free(variables);
	pthread_exit(NULL);
}