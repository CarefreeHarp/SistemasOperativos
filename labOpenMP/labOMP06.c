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
 *              a dicha función los cuales se dividen entre diferentes cantidades    *
 *              de hilos especificados por el usuario usando OpenMP.                 *
 *              Al final, cada hilo suma todos sus resultados individualmente        *
 *              y luego se suman los resultados generales de todos los hilos         *
 *              Nota: También se calculan los tiempos de ejecución por lo cual       *
 *              se puede evaluar el rendimiento utilizando diferentes cantidades     *
 *              de hilos                                                             *
*************************************************************************************/

#include <stdio.h> //librería para manejar entradas y salidas
#include <omp.h> //librería para usar openmp
#include <stdlib.h> //librería para usar exit()
#include <math.h> //librería para usar la funcion seno
#include <sys/time.h> //libreria para las estructuras timeval

struct timeval inicio, fin; //declaracion de dos estructuras a nivel global del tipo timeval

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

void InicioMuestra(){ 		// Función para iniciar la medición del tiempo
	gettimeofday(&inicio, (void *)0);// Obtener el tiempo de inicio del programa
}

void FinMuestra(){ // Función para finalizar la medición del tiempo y mostrar el resultado
	gettimeofday(&fin, (void *)0); // Obtener el tiempo de finalización del programa
	fin.tv_usec -= inicio.tv_usec; // Calcular la diferencia en microsegundos
	fin.tv_sec  -= inicio.tv_sec; // Calcular la diferencia en segundos
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); // Convertir el tiempo total a microsegundos
	printf("Tiempo total registrado %9.0f \n", tiempo);// Mostrar el tiempo total en microsegundos sin decimales
}


//funcion principal
int main(int argc, char *argv[]) {
    //Se deben enviar 3 argumentos, de lo contrario, no se puede ejecutar
    if(argc != 3){
        printf("Error : \n\t $./ejecutable numHilos repeticiones\n");
        exit(0);
    }
    double resSumatoria = 0; //Declara la variable resSumatoria y la inicializa en 0
    int numHilos = (int)atoi(argv[1]); //el segundo argumento será la cantidad de hilos a usar para paralelizar
    int rep = (int)atoi(argv[2]); //el tercer argumento será la cantidad de repeticiones

    omp_set_num_threads(numHilos); //se fija la cantidad de hilos OpenMP

    InicioMuestra(); //Registra el tiempo inicial

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

    FinMuestra(); //Calcula e imprime el tiempo final

    printf("Resultado Sumatoria funcion SENO: %0.2f \n", resSumatoria); //imprime el resultado con presicion de 2 decimales

    //devolvemos 0 para indicar la correcta ejecución del programa
    return 0;
}
