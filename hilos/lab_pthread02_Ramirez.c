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

#define NTHREADS 10
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *thread_function(void *arg) {
    int i = *(int *)(arg);
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
}

void main() {
    pthread_t thread_id[NTHREADS];
    int i, j;

    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, thread_function, &i);
    }

    printf("Final counter value: %d\n", counter);
}
