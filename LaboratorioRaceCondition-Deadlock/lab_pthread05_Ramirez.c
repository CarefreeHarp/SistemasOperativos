/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripcion: Suponiendo que x*x es un calculo altamente costoso computacionalmente*
 *              se desea calcular la suma de cuadrados usando HILOS POSIX            *
 *              se debe aplicar paralelismo de cada cuadrado usando hilos.           *
 *              Sin embargo, a diferencia del fichero lab_pthread06, este programa   *
 *              no garantiza la correcta resolución del problema en el               *
 *              100% de los casos debido a la falta de sincronización con mutex      *
*************************************************************************************/
#include <stdio.h> //librería para manejar entradas y salidas
#include <pthread.h> //librería para manejar hilos
#include <stdint.h> //librería para manejar intptr_t

//Declaración e inicialización en 0 de la variable "acumulado"
int acumulado = 0;

//Funcion cuadrados la cual recibo un puneto a void como único parámetro
void *cuadrados(void *x){

    //Cast a intptr_t de la variable enviada como parámetro para asegurar que no se pierda información de la variable
    int xi = (intptr_t)x;

    //En este caso podemos llegar a presenciar una condición de carrera por culpa de muchos hilos
    //accediendo a la misma variable a la vez
    //Puede ocurrir una secuencia de pasos indeseables como por ejemplo:
    // 1. HiloX lee la variable "acumulado" (Ej: 10)
    // 2. HiloX hace la respectiva operación (ResultadoX: 100)
    // 3. HiloY lee la variable "acumulado" (Ej: 10)
    // 4. HiloX escribe en memoria el resultadoX (acumulado = 100)
    // 5. HiloY hace la respectiva operación (ResultadoY: 100)
    // 6. HiloY escribe en memoria el resultadoY (acumulado = 100)
    //Como podemos ver, existe la posibilidad de que se pierda información en medio del pipeline de CPU
    //provocando errores y NO garantizando el resultado 
    acumulado += xi * xi;

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
    //la suma de todos los numeros del 1 al 20 elevados al cuadrado en caso de que no hubiese race conditions durante la ejecución
    printf("La suma de cuadrados es: %d\n", acumulado);

    //Devuelve 0 indicando la correcta ejecución del programa
    return 0;
}
