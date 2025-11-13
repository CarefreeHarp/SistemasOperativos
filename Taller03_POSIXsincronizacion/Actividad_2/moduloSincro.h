#ifndef __MODULOCONSUMER_H__
#define __MODULOCONSUMER_H__



#include <stdio.h>      // printf(), fprintf()
#include <stdlib.h>     // exit()
#include <string.h>     // strerror()
#include <pthread.h>    // pthread_create(), pthread_join(), mutex, cond
#include <unistd.h>     // sleep()

#define MAX_BUFFERS 100 //Se inicializa una constante que define el tamaño máximo del buffer



char buf [MAX_BUFFERS] [100]; //Se declara un buffer de caracteres de tamaño MAX_BUFFERS x 100
int buffer_index; //Índice para el buffer de producción
int buffer_print_index; //Índice para el buffer de impresión


/*Se inicializa un mutex usando las siguientes carácterísticas:

pthread_mutex_t: Es el tipo de variable usado por POSIX para representar un mutex (mutual exclusion lock), el mutex
se utiliza para proteger secciones críticas, asegurando que un solo hilo pueda ejecutar cierta región de código o acceder a cierta estructura
de datos a la vez, evitando que se generen errores durante la ejecución.

al mutex declarado se le da el nombre: buf_mutex.

El valor asignado a mutex1 es PTHREAD_MUTEX_INITIALIZER, que es una inicialización estática del mutex provista
por POSIX, es decir, esta inicialización se realiza en tiempo de compilación en lugar de hacerlo en tiempo de ejecución,
si se quiere realizar su inicialización dinámica se tendria que usar pthread_mutex_init, que permite configurarle los valores
por defecto a diferencia de como se está haciendo en este código.

Valores por defecto dados por PTHREAD_MUTEX_INITIALIZER:

-Tipo de mutex: PTHREAD_MUTEX_DEFAULT: Mutex normal, no recursivo.
-Protocolo: PTHREAD_PRIO_NONE: No da prioridad al mutex.
-Compartición: PTHREAD_PROCESS_PRIVATE: Solo sirve dentro del mimso proceso.
-Robustez: no robusto, si un hilo muere con el mutex tomado se le asigna undefined behavior.
-Chequeo de errores: No valida errores, como por ejemplo desbloquearlo antes de bloquearlo.
-Recursividad: No recursivo.

Operaciones ofrecidas por pthread_mutex_t:

-pthread_mutex_lock(&buf_mutex.): Bloquea un proceso hasta adquirir el mutex.
-pthread_mutex_trylock(&buf_mutex.): Trara de adquirir el mutex, si no puede devuelve EBUSY.
-pthread_mutex_timedlock(&buf_mutex., &abstime): Bloquea el proceso y espera hasta un tiempo límite.
-pthread_mutex_unlock(&buf_mutex.): Libera el mutex.*/
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;


/*Se inicializan dos variables de condición usando las siguientes características:

pthread_cond_t: Es el tipo de variable usado por POSIX para representar una condición
(condition variable). Las variables de condición permiten que los hilos se sincronicen
entre sí mediante señales, haciendo que un hilo pueda esperar (bloquearse) hasta que
otro hilo indique (despierte) que cierta condición se ha cumplido.

El valor asignado a la variable de condición es PTHREAD_COND_INITIALIZER, lo cual indica
una inicialización estática provista por POSIX. Esto significa que la configuración se
realiza en tiempo de compilación. Si se quisiera inicializar dinámicamente, se usaría
pthread_cond_init, que permite configurar atributos personalizados.

Valores por defecto dados por PTHREAD_COND_INITIALIZER:

- Tipo de atributo: PTHREAD_COND_DEFAULT
- Sin prioridad ni orden especial de activación de hilos
- No compartible entre procesos a menos que se configure explícitamente

Operaciones ofrecidas por pthread_cond_t:

- pthread_cond_wait(&condition_cond, &mutex):
  Hace que el hilo espere hasta que ocurra una señal. Mientras espera, el mutex asociado
  se libera automáticamente y se vuelve a adquirir cuando la condición se cumple.

- pthread_cond_signal(&condition_cond):
  Despierta a un hilo que esté esperando en la variable de condición.

- pthread_cond_broadcast(&condition_cond):
  Despierta a *todos* los hilos que estén esperando en la condición.

Notas importantes:
- Siempre debe usarse junto con un mutex para evitar race conditions.
- Las variables de condición no guardan un estado por sí mismas; dependen de una condición
  lógica definida en el programa y del mutex asociado.
*/
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;
int buffers_available = MAX_BUFFERS; //se declara una variable entera que indica la cantidad de buffers disponibles
int lines_to_print = 0; //se declara una variable entera que indica la cantidad de líneas por imprimir

void *producer (void *arg);
void *spooler (void *arg);


#endif