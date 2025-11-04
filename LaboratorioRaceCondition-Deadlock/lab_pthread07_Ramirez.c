/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripcion: Programa que crea 2 hilos que llaman a 2 funciones diferentes        *
 *              cuyo resultado depende del orden en el que ejecuten, sin embargo,    *
 *              en este programa, a diferencia del fichero lab_pthread08,            *
 *              no se manejan mecanismos que den garantía sobre el resultado         *
 *              de la ejecución.                                                     * 
*************************************************************************************/
#include <stdio.h> //librería para manejo de entradas y salidas
#include <pthread.h> //librería para manejo de hilos
#include <stdbool.h> //librería para poder usar el dato de tipo bool

//Se declara e inicializa en 100 la variable "valor"
int valor = 100;

//Función reportar, no recibe parámetros
void *reportar(){

    //Imprime por pantalla el valor de la variable global "valor"
    //este valor puede ser 100 si este hilo llega más rápido a este punto del programa
    //o puede ser 20 si el otro hilo ejecutó primero su parte en la otra función
    printf("El valor calculado es: %d\n", valor);

    //Devuelve NULL
    return NULL;
}

//Función asignar, no recibe parámetros
void *asignar(){

    //Le asigna 20 a la variable global "valor"
    valor = 20;

    //Devuelve NULL
    return NULL;
}

//Función principal
int main(){

    //Crea dos variables del tipo pthread_t que guardarán los identificadores de cada hilo
    pthread_t reporte, asigne;

    //Crea el primer hilo guardando su identificador en la variable "reporte", con atributos por defecto,
    //ejecutando la función reportar y sin enviarle parámetros
    pthread_create(&reporte, NULL, reportar, NULL);

    //Crea el segundo hilo guardando su identificador en la variable "asigne", con atributos por defecto,
    //ejecutando la función asignar y sin enviarle parámetros
    pthread_create(&asigne, NULL, asignar, NULL);

    //se crea variable para recoger valor de los hilos
    void *nousada;

    //Se hace join a ambos hilos para liberar sus recursos y para esperar a que ambos terminen
    //Adicionalmente, lo que sea que hayan devuelto, se guardará en la variable del tipo puntero a void "nousada"
    // (Aunque ambos hilos devuelven NULL)
    pthread_join(reporte, &nousada);
    pthread_join(asigne, &nousada);

    //Devuelve 0 para indicar la correcta ejecución del programa
    return 0;
}