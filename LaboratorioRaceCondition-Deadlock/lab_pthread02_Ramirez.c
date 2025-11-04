/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *                            
 * Descripción: Programa que crea 10 hilos (Dados por la variable global NTHREADS)   *
 *              que a su vez imprimen su identificador de hilo y su                  *
 *              número de hilo. Además, cada hilo incrementa un contador             *
*************************************************************************************/
#include <stdio.h> //librería para el manejo de entradas y salidas
#include <pthread.h> //librería para el manejo de hilos
#include <stdlib.h> //librería para manejo de memoria dinámica

#define NTHREADS 10 //Se define el numero de hilos a crear
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; //Se declara e inicializa el mutex
int counter = 0; //variable global que empieza en 0

//Función que ejecutará cada hilo, recibe un puntero a void como argumento
void *thread_function(void *arg) {
    //Se hace el casteo del argumento para que sea explícito que es un puntero a entero
    int i = *(int *)(arg);

    //Se imprime el numero del hilo (el orden en el que fue creado) y su ID usando pthread_self()
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());

    //Zona crítica para incrementar el valor de la variable global
    //para evitar Race Conditions se utiliza el mecanismo del mutex bloqueando dicha zona para permitir
    //un único hilo a la vez el cual aumentará el valor de la variable en 1
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);

    //se libera la memoria dinámica asignada al argumento de la función
    free(arg);
}

//Funcion principal
int main() {
    //Se declara el arreglo de identificadores de hilos
    pthread_t thread_id[NTHREADS];

    //Se itera desde 0 hasta NTHREADS-1 para crear los hilos
    for (int i = 0; i < NTHREADS; i++) {
        //Se reserva memoria dinámica para el argumento que le pasaremos a cada hilo
        int *j = malloc(sizeof(int));

        //Le asignamos el valor de i al espacio de memoria que reservamos,
        //de esta forma a cada hilo le pasamos su número de creación.
        //Usamos memoria dinámica para crear cada vez una copia diferente ya que si enviáramos
        //la referencia a la variable i, varios hilos podrían imprimir el mismo valor en sus funciones ya que 
        //se actualiza en cada iteración del main.
        *j = i;

        //Se crea cada hilo guardando su identificador en el arreglo thread_id, con atributos por defecto,
        //ejecutando la función thread_function y pasándole a cada uno como parámetro, el número que indica el
        //orden en su creación
        pthread_create(&thread_id[i], NULL, thread_function, j);
    }

    //Se hace un ciclo for desde 0 hasta NTHREADS-1 para asegurar en cada iteración, la liberación de recursos
    //de cada hilo y para impedir que el hilo principal termine antes que los demás
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    //Imprime el valor de la variable global que actualizaron todos los hilos
    //En caso de ser exitosa la ejecución, el contador debe ser la misma cantidad de hilos
    //ya que cada uno de ellos le suma 1 empezando desde 0
    printf("Final counter value: %d\n", counter);

    //Devuelve 0 indicando la correcta ejecución del programa
    return 0;
}
