/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 11 de Noviembre del 2025                                                   *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: El programa ejecuta una sección de código en paralelo utilizando     *
 *              OpenMP. Dicha sección paralela, comparte la dirección de memoria de  *
 *              la variable b por lo cual se llena de condiciones de carrera         *
 *              y el resultado de b es impredecible                                  *
*************************************************************************************/
#include <omp.h> //librería para utilizar OpenMP
#include <stdio.h> //librería  para manejar entradas y salidas

//Función principal
int main(){
    //Se declara la constante que mide la cantidad de iteraciones del ciclo for
    const int N = 1000;

    //Se declaran las variables a, b y i
    int i;
    int a = 50;
    int b = 0;

    //Sección paralela.
    //Se divide la cantidad de iteraciones del cilo for entre 
    //la cantidad de hilos que tenga la maquina donde se ejecute el programa.
    //Adicionalmente, con "private(x)" se indica que la variable x va a ser independiente para cada hilo
    //es decir que cada hilo tendrá una copia de esa variable diferente de las demás y del hilo principal del programa 
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++){
        b = a + i;
    }

    //Dado que en la sección paralela los hilos comparten la variable b, las operaciones
    //que se realizan sobre ella, están llenas de race conditions por lo cual el resultado de b
    //es impredecible
    printf("a = %d b = %d (Se espera a=50 b es impredecible)\n", a, b);

    //Devolvemos 0 para indicar la correcta ejecución del programa
    return 0;
}
