/**************************************************************************************
 * Fecha: 11 de Septiembre del 2025
 * Autor: Daniel Felipe Ramirez Vargas
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"


struct timeval ini, fin;

/*Funcion para tomar tiempo inicial y guardarlo en ini*/
void InicioMuestra(){
	gettimeofday(&ini, (void *)0);
}

/*Funcion para tomar tiempo final*/
void FinMuestra(){
	gettimeofday(&fin, (void *)0); //Guarda el momento final en fin
	fin.tv_usec -= ini.tv_usec;//Dado que la estructura timeval tiene dos campos, uno para segundos y otro para microsegundos,
	fin.tv_sec -= ini.tv_sec;// Se hace la resta en cada uno (tv_sec y tv_usec)
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); //Se convierte todo a microsegundos ya que un segundo es un millon de microsegundos
	printf("Tiempo total: %9.0f \n", tiempo);//se imprime el tiempo total en microsegundos
}

/*Inicializa dos matrices de acuerdo a un contador i que va desde 0 hasta N*N (N es enviado como parametro a la funcion)*/
void iniMatriz(int n, double *m1, double *m2){
   	for(int i=0; i<n*n; i++){
	        m1[i] = i*2.3 + 1.3;
	        m2[i] = i*2.3;
	}
};

/*Dada una matriz y su tamanio enviados como parametro,
se imprime la matriz por pantalla*/
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
   	for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
	        printf(" %f ", matriz[i]);
   }
    } else {
        printf("\n#######################################################\n");
    }
};


//Multiplica las matrices m1 y m2, y almacena el resultado en m3
//utilizando el algoritmo de multiplicacion clasica
//es decir, filas por columnas
void multiMatrizClasica(double *m1, double *m2, double *m3, int N){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = m1 + i*N;
            pB = m2 + j;
            for(int k=0; k<N; k++, pA++, pB+=N){
                sumaTemp += *pA * *pB;
            }
            m3[j+i*N] = sumaTemp;
        }
    }
}
