#ifndef __MODULOPOSIX_H__
#define __MODULOPOSIX_H__
/*#######################################################################################
#* Fecha:
#* Autor: J. Corredor, PhD
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

extern pthread_mutex_t MM_mutex;
extern double *matrixA, *matrixB, *matrixC;
extern struct timeval inicio, fin;

struct parametros{
	int nH;
	int idH;
	int N;
};
void InicioMuestra();
void FinMuestra();
void iniMatrix(double *m1, double *m2, int D);
void impMatrix(double *matriz, int D);
void *multiMatrix(void *variables);


#endif