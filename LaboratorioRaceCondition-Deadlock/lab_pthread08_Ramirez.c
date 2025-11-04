/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Programa que crea dos hilos que llaman a dos funciones diferentes    *
 *              cuyo resultado depende del orden en que se ejecuten, sin embargo,    *
 *              en este programa, a diferencia del fichero lab_pthread07, sí se      *
 *              manejan mecanismos que garantizan el resultado de la ejecución.      *
 *              En este caso, el hilo de la función reportar solo continuará si      *
 *              existe certeza de que el hilo de la función asignar ya asignó        *
 *              correctamente el valor 20 a la variable global que ambos utilizan.   *
*************************************************************************************/
#include <stdio.h> //librería para manejo de entradas y salidas
#include <pthread.h> //librería para manejo de hilos
#include <stdbool.h> //librería para poder usar el tipo de dato bool

// Se declara e inicializa en 100 la variable "valor"
int valor = 100;

// Se declara e inicializa en false la variable "notificar"
bool notificar = false;
// Se declaran e inicializan el mutex "bloqueoCC" y la condición para wait y signal "condiCC"
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condiCC = PTHREAD_COND_INITIALIZER;

// Función reportar, no recibe parámetros
void *reportar(){

    // Sección crítica protegida por el mutex "bloqueoCC".
    // Se utiliza para proteger el flujo entre wait y signal; además, se usa para proteger el uso
    // adecuado de la variable "notificar", que permitirá saber si se debe avanzar en la ejecución.
    pthread_mutex_lock(&bloqueoCC);
    // Mientras notificar sea falso, el hilo debe dormir.
    // Esta parte de código debe hacerse con un while ya que pueden presentarse casos en los cuales
    // un hilo dormido se despierte sin que nadie haya llamado a signal y, por lo tanto, debe volver a esperar.
    while(!notificar){
        // Se duerme el hilo utilizando pthread_cond_wait con los parámetros:
        // 1. condiCC: para indicar la condición que se utiliza para dormir el hilo
        // 2. bloqueoCC: para indicar qué mutex se utilizará en esta operación
        pthread_cond_wait(&condiCC, &bloqueoCC);
    }

    // Se imprime el valor de la variable global "valor"
    printf("El valor calculado es: %d\n", valor);

    // Se libera el mutex
    pthread_mutex_unlock(&bloqueoCC);

    // Devuelve NULL
    return NULL;
}

// Función asignar, no recibe parámetros
void *asignar(){

    // Se asigna 20 a la variable global "valor"
    valor = 20;

    // Sección crítica protegida por el mutex "bloqueoCC".
    // Se utiliza para proteger el flujo entre wait y signal; además, sirve para asegurar que
    // "notificar" se actualice a true antes de que la función reportar vaya a utilizarla.
    pthread_mutex_lock(&bloqueoCC);
    // Se actualiza la variable "notificar" a "true"
    notificar = true;
    // Se hace signal con la condición condiCC para que el hilo que espera esa condición pueda despertar
    // y continuar su ejecución
    pthread_cond_signal(&condiCC);

    // Se libera el mutex
    pthread_mutex_unlock(&bloqueoCC);

    // Devuelve NULL
    return NULL;
}

// Función principal
int main(){

    // Se crea una variable de tipo pthread_t para cada hilo que guardará el identificador de cada uno
    pthread_t reporte, asigne;

    // Se crea el primer hilo guardando su identificador en la variable "reporte", con atributos por defecto,
    // ejecutando la función reportar y sin enviarle parámetros
    pthread_create(&reporte, NULL, reportar, NULL);

    // Se crea el segundo hilo guardando su identificador en la variable "asigne", con atributos por defecto,
    // ejecutando la función asignar y sin enviarle parámetros
    pthread_create(&asigne, NULL, asignar, NULL);

    // Se crea una variable para recoger el valor devuelto por los hilos
    void *nousada;

    // Se hace join a ambos hilos para liberar sus recursos y para esperar a que terminen.
    // Adicionalmente, lo que hayan devuelto se guardará en la variable del tipo puntero a void "nousada"
    // (aunque ambos hilos devuelven NULL)
    pthread_join(reporte, &nousada);
    pthread_join(asigne, &nousada);

    // Devuelve 0 para indicar la correcta ejecución del programa
    return 0;
}
