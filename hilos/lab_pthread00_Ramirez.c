/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 9 de Octubre del 2025                                                      *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Uso de Interfaz de creacion de hilos PTHREAD                             *
 * -                                                                                 *
*************************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void *funcion(void *arg) {
    size_t job = *(size_t *)arg;
    printf("Job #%zu\n", job);
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Faltan argumentos \n");
        exit(0);
    }
    int N = atoi(argv[1]);

    size_t jobs[N];      // vector de trabajos
    pthread_t hilos[N];  // Vector de hilos

    for (size_t i = 0; i < N; i++) {
        jobs[i] = i;
        pthread_create(&hilos[i], NULL, funcion, jobs + i);
    }

    for (size_t i = 0; i < N; i++) {
        pthread_join(hilos[i], NULL); // Se espera por cada hilo finalice
    }

    return 0;
}



