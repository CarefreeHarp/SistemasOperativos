/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 6 de Noviembre del 2025                                                    *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: Este programa crea tres hilos que ejecutan la función compute().     *
 *              Cada hilo entra en una sección crítica protegida por un mutex        *
 *              ya que se le suma a una variable global, hace un trabajo y luego     *
 *              la imprime, por lo cual mientras se realiza el trabajo, se debe      *
 *              se debe conservar el valor del contador o los demás hilos lo         *
 *              modificarán                                                          *
*************************************************************************************/
#include <stdio.h> //librería para manejar entradas y salidas
#include <pthread.h> //librería para manejar hilos
#include <string.h> //librería para manejar strings, en este caso, para contolar errores

//Se crea el arreglo para guardar 3 identificadores de hilos
pthread_t tid[3];

//Se declara e inicializa la variable global counter en 0
int counter = 0;

//Se declara e inicializa el mutex "lock"
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//Funcion compute 
void* compute(void *arg) {
    //Declara una variable i de tipo unsigned long para poder manejar el ciclo for
    //hasta el numero hexadecimal 0xFFFFFFFF (muy grande)
    unsigned long i = 0;

    //Sección crítica protegida por el mutex "lock"
    //Se utiliza para proteger el valor de la variable counter ya que cada hilo debe realizar
    //un ciclo for de muchas iteraciones y luego mostrar por pantalla su valor. En caso de no protegerla,
    //mientras que un hilo está iterando muchas veces en el for, otro hilo puede cambiar el valor de counter
    //y no se msotrará correctamente
    pthread_mutex_lock(&lock);
    //Se incrementa counter en 1
    counter += 1;
    //Imprime por pantalla el valor de counter
    printf("\n Job %d has started\n", counter);
    //Ciclo por de muchas iteraciones
    for(i = 0; i < (0xFFFFFFFF); i++);
    //Imprime por pantalla el valor de counter después de terminar el ciclo for de muchas iteraciones
    printf("\n Job %d has finished\n", counter);

    //Se libera el mutex
    pthread_mutex_unlock(&lock);

    //Los hilos retornan NULL
    return NULL;
}

//Funcion principal
int main() {
    //Se declaran las variables "i" y "error"
    int i = 0;
    int error;

    //Se crean 3 hilos (uno en cada iteración)
    while(i < 3) {
        //El valor del retorno de la función pthread_create se guarda en la variable "error"
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);
        if (error != 0)
            //strerror traduce los codigos POSIX de error a texto y lo imprime por pantalla en caso de haber alguno 
            printf("\nThread can't be created : [%s]", strerror(error));
        i++; //se incrementa i
    }

    //Se liberan los recursos de cada uno de los hilos creados y se esperan a que terminen para que
    //el programa principal no acabe antes que ellos
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    //Devuelve 0 indicando la correcta ejecuión del programa
    return 0;
}
