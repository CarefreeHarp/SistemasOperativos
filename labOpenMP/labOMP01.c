/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que por medio de OpenMP, ejecuta en paralelo                *
 *              un bloque de código desde el cual cada hilo saluda y muestra su      *
 *              numero de hilo.                                                      *
 *              Muestra la cantidad total de cores lógicos de la maquina donde se    *
 *              ejecuta el programa                                                  *
*************************************************************************************/

#include <omp.h> //librería para utilizar OpenMP
#include <stdio.h> //librería para manejar entradas y salidas

int main() {
    //Se obtiene la cantidad de cores lógicos con la funcion omp_get_max_threads() y se 
    //imprimen por pantalla
    int maxCores = omp_get_max_threads();
    printf("Numero maximo de cores del SO %d \n", maxCores);
    
    //Comienza una sección paralela 
    #pragma omp parallel
    { 
        //Esto será ejecutado por todos los hilos, por lo cual van a indicar cada uno su número de hilo
        printf("Hello World desde el thread %d\n", omp_get_thread_num());
    }

    //Devuelve un 0 indicando la correcta ejecución del programa
    return 0;
}
