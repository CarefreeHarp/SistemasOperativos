/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que utiliza 2 hilos para sumar una variable hasta llegar    *
 *              a un número específico establecido en la variable global COUNT_DONE. *
 *              Se utilizan mutexes y condiciones para wait y signal con el objetivo *
 *              de que el hilo1 solo actualice el contador mientras este esté por    *
 *              fuera del rango [COUNT_HALT1 ; COUNT_HALT2], mientras que el hilo2   *
 *              no tiene ninguna restricción para aumentar el contador y se encarga  *
 *              de enviar señales al hilo1 para informar cuando puede continuar.     *
*************************************************************************************/

#include <stdio.h> //librería para manejo de entradas y salidas
#include <pthread.h> //librería para manejo de hilos

//Se declara e incializa el mutex para proteger a la variable global count
pthread_mutex_t count_mutex      = PTHREAD_MUTEX_INITIALIZER;

//Se declara e incializa el mutex para proteger la sincronización entre wait y signal
pthread_mutex_t condition_mutex  = PTHREAD_MUTEX_INITIALIZER;

//Se declara e inicializa la condición para utilizar en wait y signal
pthread_cond_t  condition_cond   = PTHREAD_COND_INITIALIZER;

//Declara las variables globales count, COUNT_DONE, COUNT_HALT1 y COUNT_HALT2 que indicarán a
//los hilos, en qué intervalos pueden modificar variables y en que punto deben parar
int count = 0; 
#define COUNT_DONE 15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

//Función que ejecuta el hilo1
void *count01() {

    //inicia un ciclo infinito
    for(;;) {

        //Sección crítica protegida por condition_mutex.
        //Se utiliza para proteger el flujo entre wait y signal
        pthread_mutex_lock(&condition_mutex);
        //En caso de que el contador esté dentro del rango [COUNT_HALT1 ; COUNT_HALT2], el 
        //hilo1 se dormirá y esperará una señal
        while(count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        //Se libera el mutex condition_mutex
        pthread_mutex_unlock(&condition_mutex);

        //Sección crítica protegida por count_mutex para evitar
        //posibles condiciones de carrera ya que el hilo2 también puede actualizar esta variable
        pthread_mutex_lock(&count_mutex);
        //Se incrementa un contador
        count++;
        //Muestra un mensaje por pantalla indicando que fue el hilo1 el que aumentó el contador
        printf("Counter value function Count ==> 01 <==: %d\n", count);
        //Libera el mutex
        pthread_mutex_unlock(&count_mutex);

        //Verifica si el contador ya llegó a su punto deseado o si lo sobrepasó.
        //A pesar de que el contador ya haya llegado a COUNT_DONE y que el hilo que le sumó para llegar
        //a ese punto ya haya terminado, el otro hilo aún sigue ejecutando la función y puede incrementarlo una vez más 
        if(count >= COUNT_DONE) return(NULL);
    }
}

//Función que ejecuta el hilo2
void *count02() {
    //Empieza un ciclo infinito
    for(;;) {

        //Sección crítica protegida por condition_mutex
        //Se utiliza para proteger el flujo entre wait y signal
        pthread_mutex_lock(&condition_mutex);
        //En caso de que el contador esté por fuera del rango [COUNT_HALT1 ; COUNT_HALT2], se enviará
        //una señal con signal que le permitirá al hilo1 despertar ya que habría sido dormido previamente 
        //con la condicion que se usa en el signal. 
        if(count < COUNT_HALT1 || count > COUNT_HALT2) {
            pthread_cond_signal(&condition_cond);
        }
        //Se libera el mutex
        pthread_mutex_unlock(&condition_mutex);

        //Sección crítica protegida por count_mutex para evitar
        //posibles condiciones de carrera ya que el hilo1 también puede actualizar esta variable
        pthread_mutex_lock(&count_mutex);
        //Se incrementa un contador
        count++;
        //Muestra un mensaje por pantalla indicando que fue el hilo2 el que aumentó el contador
        printf("Counter value function Count ==> 02 <==: %d\n", count);
        //Libera el mutex
        pthread_mutex_unlock(&count_mutex);

        //Verifica si el contador ya llegó a su punto deseado o si lo sobrepasó.
        //A pesar de que el contador ya haya llegado a COUNT_DONE y que el hilo que le sumó para llegar
        //a ese punto ya haya terminado, el otro hilo aún sigue ejecutando la función y puede incrementarlo una vez más 
        if(count >= COUNT_DONE) return(NULL);
    }
}


//Función principal
int main() {
    //Se declaran dos variables del tipo pthread_t donde se guardará el identificador de cada hilo
    pthread_t thread1, thread2;

    //Se crea el hilo1 guardando su id en thread1, con atributos por defecto, ejecutando la funcion count01 y sin parámetros
    pthread_create(&thread1, NULL, count01, NULL);

    //Se crea el hilo2 guardando su id en thread1, con atributos por defecto, ejecutando la funcion count02 y sin parámetros
    pthread_create(&thread2, NULL, count02, NULL);

    //Se hace join para ambos hilos liberando sus recursos y asegurándose que ya han terminado para que el programa principal
    //no finalice antes de tiempo.
    //Además, no se recibe ningún dato que los hilos hayan devuelto
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //Se devuelve 0 indicando la correcta ejecución del programa
    return 0;
}

