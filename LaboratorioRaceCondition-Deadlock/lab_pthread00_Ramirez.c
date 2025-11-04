/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que crea múltiples hilos usando la librería Pthreads        *
 *              según un número indicado por el usuario. Cada hilo ejecuta una       *
 *              función que imprime un número de trabajo asignado.                   *
 *              Finalmente, el programa principal espera a todos los hilos           *
 *              con un join para asegurar que todos alcancen a terminar.             *
 *              Adicionalmente, se recibe como argumento el número de hilos que se   *
 *              desean crear.                                                        *
*************************************************************************************/
#include <stdio.h> //libreria para manejar entradas y salidas
#include <pthread.h> //librería para manejo de hilos
#include <stdlib.h> //librería para uso de las funciones exit() y atoi()

// Función que ejecuta cada hilo. Recibe un argumento que indica el número de trabajo del hilo.
static void *funcion(void *arg) {
    //hace explícito el casteo del argumento para guardarlo en una variable
    size_t job = *(size_t *)arg; 

    //Imprime el número de trabajo del hilo usando %zu para imprimir una variable del tipo size_t
    printf("Hilo %zu: Hola desde el hilo!\n", job);

    //retorna NULL al finalizar el trabajo del hilo, indicando que no hay valor de retorno
    return NULL;
}

//Función principal del programa
int main(int argc, char *argv[]) {

    //verifica  que se hayan proporcionado los argumentos necesarios para la ejecución del programa
    if(argc < 2){
        //En caso de no cumplir con la cantidad de argumentos, se le informa al usuario y se termina la ejecución
        printf("Faltan argumentos \n");
        exit(0);
    }

    //Convierte el argumento enviado como parámetro a entero y lo guarda en la variable N
    int N = atoi(argv[1]);

    //Declara el vector de trabajos que guarda datos del tipo size_t y el vector de hilos
    size_t jobs[N];      // vector de trabajos
    pthread_t hilos[N];  // Vector de hilos


    //Dado que size_t se comporta como un entero, se utiliza para un ciclo for
    //el cual itera desde 0 hasta N-1 llenando el arreglo de trabajos y el arreglo de hilos
    //creándolos con pthread_create
    for (size_t i = 0; i < N; i++) {
        jobs[i] = i;

        //Cada iteración crea un hilo con la funcion pthread_create que sigue los siguientes parámetros:
        //1. Dirección donde se guardará el identificador del hilo
        //2. Atributos con los cuales se creará el hilo (NULL los crea con atributos por defecto)
        //3. Dirección de la función que ejecutará el hilo
        //4. Argumento que se le pasara a la función que ejecutará el hilo (en este caso, su número de trabajo empezando desde 0)
        pthread_create(&hilos[i], NULL, funcion, jobs + i);
    }

    //Ciclo for que itera desde 0 hasta N-1 haciendo join() para evitar que el programa principal termine antes que los hilos
    for (size_t i = 0; i < N; i++) {

        //Cada iteración del ciclo, ejecuta la función pthread_join que tiene los siguientes parámetros:
        //1. Identificador del hilo que se va a esperar
        //2. Dirección donde se guardará el valor de retorno del hilo, es decir, el return o el pthread_exit que haya 
        //   ejecutado el hilo dentro de la función que se le asignó (en este caso nada)
        pthread_join(hilos[i], NULL); // Se espera por cada hilo finalice
    }


    //Devolvemos 0 para indicar la correcta ejecución del programa
    return 0;
}



