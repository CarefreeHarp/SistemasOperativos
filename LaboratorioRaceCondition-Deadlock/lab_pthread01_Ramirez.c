/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que crea dos hilos usando la librería Pthreads.             *
 *              Cada hilo ejecuta una función que imprime un mensaje único           *
 *              para cada hilo. Finalmente, el programa principal espera a ambos     *
 *              hilos para terminar correctamente la ejecución sincronizándolos.     *
 *              El programa no requiere de argumentos de entrada                     *
*************************************************************************************/
#include <stdio.h> //librería para el manejo de entradas y salidas 
#include <pthread.h> //librería para el manejo de hilos

//Función que ejecuta cada hilo, recibe un puntero a void como argumento
//y luego se hace el cast a un puntero a variable del tipo char para poder imprimir
//el argumento por pantalla
void *print_message_function(void * ptr){
    char *message;
    message = (char*) ptr;

    //Usa %s para imprimir el argumento casteado enviado como parámetro 
    printf("%s \n", message);
}

//Funcion principal
int main(){
    //Declaración del identificador de cada hilo
    pthread_t thread1, thread2;

    //Declaración de los mensajes que se enviarán como parámetro
    char *message01 = "Soy el hilo 1";
    char *message02 = "Soy el hilo 2";

    //Declaración de variables que permiten guardar el valor de retorno de las funciones pthread_create
    //para detectar errores en la creación de hilos
    int iret1, iret2;

    //Primer hilo creado con pthread_create, se guarda su identificador en thread1, no se usan atributos especiales,
    //se le asigna la función print_message_function y se le pasa como argumento a la función, el valor de message01
    iret1 = pthread_create(&thread1, NULL, print_message_function, message01);

    //Segundo hilo creado con pthread_create, se guarda su identificador en thread2, no se usan atributos especiales,
    //se le asigna la función print_message_function y se le pasa como argumento a la función, el valor de message02
    iret2 = pthread_create(&thread2, NULL, print_message_function, message02);

    //Se usa pthread_join para evitar que el programa principal termine antes que los hilos
    //Se espera al hilo1 y se descarta el valor de retorno
    pthread_join(thread1,NULL);

    //Se espera al hilo2 y se descarta el valor de retorno
    pthread_join(thread2,NULL);

    //Se imprime por pantalla el valor de retorno de la función pthread_create para cada hilo
    //que fue guardado en las variables iret1 e iret2 para detectar errores
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    //Devolvemos 0 para indicar la correcta ejecución del programa
    return 0;
}