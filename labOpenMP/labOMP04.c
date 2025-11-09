/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 11 de Noviembre del 2025                                                   *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: El programa ejecuta una sección de código en paralelo utilizando     *
 *              OpenMP. Dicha sección paralela, pone en privado todas las variables  *
 *              que usa por lo cual se crean copias distintas en cada hilo y al      *
 *              finalizar ese bloque de código, se destruyen todas.                  *
 *              El resultado final son las variables a y b tal cual se declararon    *
 *              y sin modificaciones                                                 * 
*************************************************************************************/
#include <omp.h> //librería para utilizar OpenMP
#include <stdio.h> //librería  para manejar entradas y salidas

//Función principal
int main(){
    //Se declara la constante que mide la cantidad de iteraciones del ciclo for
    const int N = 1000;

    //Se declaran las variables a, b, i
    int i;
    int a = 50;
    int b = 0;

    //Sección paralela.
    //Se divide la cantidad de iteraciones del cilo for entre 
    //la cantidad de hilos que tenga la maquina donde se ejecute el programa.
    //Adicionalmente, con "private(x)" se indica que la variable x va a ser independiente para cada hilo
    //es decir que cada hilo tendrá una copia de esa variable diferente de las demás y del hilo principal del programa 
    #pragma omp parallel for private(i) private(a) private(b)
    for (i = 0; i < N; i++){
        b = a + i;
    }

    //Dado que en la sección paralela la variable b es privada, todas las copias de esa variable
    //creadas en los diferentes hilos se destruirán y no modificaran la copia original del hilo principal
    //Es por esto que va a quedar sin modificar. (b = 0)
    //Por otro lado, la variable a nunca se modifica asi que seguirá siendo 50
    printf("a = %d b = %d (Se espera a=50 b=0)\n", a, b);

    //Devolvemos 0 para indicar la correcta ejecución del programa
    return 0;
}
