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


void *print_message_function(void * ptr){
    char *message;
    message = (char*) ptr;
    printf("%s \n", message);
}

int main(){
    pthread_t thread1, thread2;
    char *message01 = "Soy el hilo 1";
    char *message02 = "Soy el hilo 2";
    int iret1, iret2;


    iret1 = pthread_create(&thread1, NULL, print_message_function, message01);
    iret2 = pthread_create(&thread2, NULL, print_message_function, message02);


    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    return 0;
}