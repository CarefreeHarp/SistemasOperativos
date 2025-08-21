/**************************************************************************************
 * Fecha: 14 agosto 2025
 * Autor: Daniel Felipe Ramirez Vargas
 * Materia: Sistemas Operativos
 * Tema: Rendimiento y Concurrencia
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

/* Se declaran 3 punteros del tipo double para las matrices*/
double *mA, *mB, *mC;

/*Funcion para imprimir las Matrices*/
void imprMatrices(int n, double *matriz)
{
    if (n < 9)
    {
        for (int i = 0; i < n * n; i++)
        {
            if (i % n == 0)
                printf("\n");
            printf(" %f ", matriz[i]);
        }
        printf("\n#######################################################\n");
    }
    else
    {
        printf("\n#######################################################\n");
    }
};

/*INICIALIZACION DE MATRICES**/
void iniMatriz(int n, double *matrizA, double *matrizB)
{
    for (int i = 0; i < n * n; i++)
    {
        matrizA[i] = i * 5 + 1;
        matrizB[i] = i * 2 + 3;
    }
};



int main(int argc, char *argv[])
{
    if (argc < 2) //Se encarga de revisar que haya almenos 1 argumento util para usar en la dimension de las matrices
    {
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }

    int n = (int)atof(argv[1]); //n es la dimension de la matriz (cuadrada)
    // Se espera un valor positivo para la dimension matrices
    if (n <= 0)
    {
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    // para almacenar matrices cuadradas de acuerdo al segundo argumentoi enviado al ejecutar
    mA = (double *)malloc(n * n * sizeof(double)); // reserva espacio en memoria sin modificarlo
    mB = (double *)malloc(n * n * sizeof(double)); // reserva espacio en memoria sin modificarlo
    mC = (double *)calloc(n * n, sizeof(double));  // memoria dinamica que inicializa los espacios de memoria reservados en 0

    iniMatriz(n, mA, mB);
    imprMatrices(n, mA);
    imprMatrices(n, mB);
    imprMatrices(n, mC);

    /*
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = mA + i*n;
            pB = mB + j*n;
            for(int k=0; k<n; k++, pA++, pB+=n){
                   sumaTemp += *pA * *pB;
            }
            mC[j+i*n] = sumaTemp;
        }
    }
    */

    printf("\n.............Fin del programa.............!\n");
    // Se libera memoria debibo a que debemos ahorrar la memoria que tenemos a disposicion
    free(mA);
    free(mB);
    free(mC);
    return 0;
}
