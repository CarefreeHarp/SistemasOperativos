/*#######################################################################################
#* Fecha:
#* Autor: J. Corredor, PhD
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/


#include "moduloPosix.h"


int main(int argc, char *argv[]){
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int N = atoi(argv[1]); 
    int n_threads = atoi(argv[2]); 

    pthread_t p[n_threads];

	matrixA  = (double *)calloc(N*N, sizeof(double));
	matrixB  = (double *)calloc(N*N, sizeof(double));
	matrixC  = (double *)calloc(N*N, sizeof(double));

	iniMatrix(matrixA, matrixB, N);
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	InicioMuestra();


    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = N;

        pthread_create(&p[j],NULL,multiMatrix,(void *)datos);
	}

    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL);

	FinMuestra();
	
	impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);

	return 0;
}

