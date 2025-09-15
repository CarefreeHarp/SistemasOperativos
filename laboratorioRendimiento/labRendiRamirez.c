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

double *mA, *mB, *mC;//declara apuntadores a datos del tipo double globales

int main(int argc, char *argv[]) {
    if(argc<=1){ //valida que se hayan ingresado los argumentos de entrada necesarios
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;//termina el programa si no se ingresan los argumentos correctos
    }

    int N = (int) atof(argv[1]); //convierte el argumento de entrada a entero (dimensión de la matriz)
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n"); // ¿Validación de que la dimensión sea mayor que cero
        return -1;
    };

    //se reserva la cantidad de memoria necesaria para las matrices cuadradas de dimensión N

    mA = (double *) malloc(N*N*sizeof(double));// reserva memoria para las mA
    mB = (double *) malloc(N*N*sizeof(double)); // reserva memoria para las mB
    mC = (double *) calloc(N*N,sizeof(double)); // reserva memoria para las mC e inicializa en cero todas las posiciones

	/** Se inicializan las 2 matrices **/
	iniMatriz(N, mA, mB);

    //se imprimen las matrices
	imprMatrices(N, mA);
	imprMatrices(N, mB);

    //se toma el tiempo inicial antes de empezar el algoritmo de multiplicación
    InicioMuestra();

    //se multiplican mA y mB
    multiMatrizClasica(mA, mB, mC, N);

    //se toma el tiempo final despues de terminar el algoritmo de multiplicación y se muestra por pantalla
    FinMuestra();
    
    //se imprime la matriz mC, es decir el resultado de la multiplicación 
	imprMatrices(N, mC);

    //se libera la memoria, como siempre se debe hacer
    printf("\n\tFin del programa.............!\n");
    free(mA);
    free(mB);
    free(mC);
    return 0;

}
