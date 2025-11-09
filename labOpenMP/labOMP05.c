/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 11 de Noviembre del 2025                                                   *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: El programa utiliza una función para sumar el seno de un conjunto    *
 *              de numeros dado un numero i. Es importante aclarar que para cada     *
 *              numero i, el rango en el cual se calcula la suma de senos es         *
 *              diferente.                                                           *
 *              Adicionalmente, el programa suma el resultado de varios llamados     *
 *              a la función (30000) los cuales se dividen                           *
 *              entre la cantidad de hilos que tenga la máquina donde se             * 
 *              ejecute el programa.                                                 *
 *              Al final, cada hilo suma todos sus resultados individualmente        *
 *              y luego se suman los resultados generales de todos los hilos         *
*************************************************************************************/

#include <stdio.h> //librería para manejar entradas y salidas
#include <omp.h> //librería para usar openmp
#include <stdlib.h> //librería para usar exit()
#include <math.h> //librería para usar la funcion seno

//funcion sumatoria
double fsum(int i){ //recibe un numero entero i
    int inicio = i*(i+1)/2; //inicio guarda la suma de todos los naturales desde 0 hasta i
    int fin = inicio+i; //y el final guarda el final del
    //De esta forma, contemplaremos un intervalo que considera todos los numeros naturales
    //dentro de un rango definido sin solapamiento con respecto a los anteriores o siguientes números i.

    //Por ejemplo, para i, i+1 y i-i tendremos 3 rangos distintos R, R1 y R2 respectivamente
    //Esta formula, también conocida como la fórmula de Gauss, nos garantiza que R, R1 y R2 no tienen intersección.
    //Al tener cualquier numero i y al aplicarle la formula, estamos empezando el intervalo de numero naturales
    //desde el que acabó el intervalo de i-1 y al sumarle i, finalizamos el intervalo donde comenzará el siguiente intervalo (el de i+1)

    //Esto pasa porque la formula de Gauss, suma todos los numeros naturales desde 0 hasta i y si al resultado le sumamos i, obtendremos 
    //la suma de todos los numeros naturales desde 0 hasta i+1, que es desde donde comienza el siguiente intervalo 

    //Una vez explicado esto, entenderemos que el ciclo for que viene a continuación, realiza la suma de todos los senos
    //dentro de un rango específico. Es decir, para un i, se sumarán todos los senos dentro de su rango asociado los cuales son
    //todos diferentes respecto a los otros rangos de otros i's

    double valorSum = 0;
    for(int j = inicio ; j < fin ; j++){
        valorSum += sin(j);
    }
    return valorSum; //devolvemos el resultado de la suma de todos los senos dentro del rango de ese i
}

int main() {
    double resSumatoria = 0; // Declara e inicializa en 0 la variable resSumatoria
    int rep = 30000; // Define una variable rep y la inicializa en 30000

    // Declara e inicializa la variable maxCores en la maxima cantidad de cores lógicos de la máquina donde se ejecute el programa
    int maxCores = omp_get_max_threads(); 
    printf("Numero maximo de cores del SO: %d \n", maxCores); //los imprime


    //Entra en una sección paralela que divide la cantidad total de iteraciones del ciclo
    //for entre la cantidad de cores lógicos de la máquina donde se ejecute, por ejemplo, para una máquina con
    //10 cores lógicos, cada uno se encargará de realizar 3000 iteraciones del ciclo for (siempre y cuando se use una distribución estática).
    //Adicional a eso, establece la variable resSumatoria como una variable privada en cada hilo
    //la cual, al final de la sección paralela, cada hilo aportará su propio resultado y todos ellos 
    //se sumarán en la variable resSumatoria: (+: resSumatoria)
    #pragma omp parallel for reduction (+: resSumatoria) 
    for(int i = 0 ; i < rep ; i++){
        resSumatoria += fsum(i);
    }

    //imprime el resultado con precision de 2 decimales
    printf("Resultado Sumatoria funcion SENO: %0.2f \n", resSumatoria);

    //devolvemos el 0 para indicar la correcta ejecucion del programa

    return 0;
}
