/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripcion: Suponiendo que x*x es un calculo altamente costoso computacionalmente*
 *              se desea calcular la suma de cuadrados usando HILOS POSIX            *
 *              se debe aplicar paralelismo de cada cuadrado usando hilos.           *
 *              Sin embargo, a diferencia del fichero lab_pthread05, este programa   *
 *              SI garantiza la correcta resolución del problema en el               *
 *              100% de los casos gracias a la presencia de mecanismos de            *
 *              sincronización como mutex                                            *
*************************************************************************************/
#include <stdio.h> //librería para manejar entradas y salidas
#include <pthread.h> //librería para manejar hilos
#include <stdint.h> //librería para manejar intptr_t

//Declaración e inicialización del mutex "lock"
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//Declaración e inicialización en 0 de la variable "acumulado"
int acumulado = 0;

//Funcion cuadrados la cual recibo un puneto a void como único parámetro
void *cuadrados(void *x){
    //Cast a intptr_t de la variable enviada como parámetro para asegurar que no se pierda información de la variable
    int xi = (intptr_t)x;

    //Sección critica protegida por el mutex "lock"
    //Se utiliza para evitar condiciones de carrera explicadas en el fichero lab_pthread05,
    //asegurando la variable global "acumulado" 
    pthread_mutex_lock(&lock);
    acumulado += xi * xi;
    //Se libera el mutex
    pthread_mutex_unlock(&lock);

    //Cada hilo devuelve NULL
    return NULL;
}

//Funcion principal
int main(){

    //Se declara el arreglo donde se guardará el identificador de cada hilo
    pthread_t hilos[20];

    //Se crean 20 hilos
    for(int i=0; i<20; i++){
        //Por cada iteración, se crea un hilo guardando su identificador en el arreglo, con atributos por defecto,
        //ejecutando la función cuadrados y pasandole como parámetro la variable i+1 siendo casteada a un intptr_t y luego a un
        //puntero a void
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i+1));
    }

    //Se liberan los recursos de los 20 hilos creados y el programa principal espera
    //a que todos terminen para continuar
    for(int i=0; i<20; i++){
        pthread_join(hilos[i], NULL);
    }

    //Se imprime por pantalla el resultado de la variable acumulado, la cual guardará
    //la suma de todos los numeros del 1 al 20 elevados al cuadrado
    printf("La suma de cuadrados es: %d\n", acumulado);

    //Devuelve 0 indicando la correcta ejecución del programa
    return 0;
}
