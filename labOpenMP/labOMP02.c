/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que recibe como argumento la cantidad de hilos que se       *
 *              desean usar para ejecutar una sección paralela.                      *
 *              Se muestran por pantalla la cantidad total de cores de la máquina    *
 *              donde se esté ejecutando el programa.                                *
 *              La sección paralela es ejecutada por todos los hilos y cada          *
 *              uno saluda e imprime su numero de hilo.                              *
*************************************************************************************/

#include <omp.h> //librería para utilizar OpenMP
#include <stdio.h> //librería para manejar entradas y salidas
#include <stdlib.h> //librería para usar exit()

int main(int argc, char *argv[]) {

    //Se necesitan dos argumentos para la ejecución del programa
    if(argc != 2){
        printf("Error : \n\t $./ejecutable numHilos \n");
        exit(0); //termina si no cumple la cantidad de argumentos
    }

    //El segundo argumento es la cantidad de hilos que se desean usar
    int numHilos = (int) atoi(argv[1]);

    //Se obtiene la cantidad de cores lógicos con la funcion omp_get_max_threads() y se 
    //imprimen por pantalla
    int maxCores = omp_get_max_threads();
    printf("Numero maximo de cores del SO %d \n", maxCores);

    //Se establece la cantidad de hilos que se haya querido
    omp_set_num_threads(numHilos);
    
    //Comienza una sección paralela 
    #pragma omp parallel
    { 
        //Esto será ejecutado por todos los hilos, por lo cual van a indicar cada uno su número de hilo
        printf("Hello World desde el thread %d\n", omp_get_thread_num());
    }

    //Devuelve un 0 indicando la correcta ejecución del programa
    return 0;
}
