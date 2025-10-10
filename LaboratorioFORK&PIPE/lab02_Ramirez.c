/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 9 de Octubre del 2025                                                      *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Creacion de procesos fork                                                   *
 * -Identificacion del proceso padre e hijo                                          *
*************************************************************************************/

#include <stdio.h> //libreria para manejo de entradas y salidas
#include <stdlib.h> //libreria para manejar errores (buenas practicas de programacion)
#include <unistd.h> //libreria para hacer fork() y getpid()

int main(){
    /*Se invoca la creacion del proceso en para identificarlo mas adelante*/
    pid_t procesoID = fork(); /*Se duplica el proceso y se guarda en un dato de tipo pid_t*/
    /*pid_t se comporta como un int pero es utilizado por buenas prácticas ya que la implementacion de pid_t
    puede cambiar dependiendo del sistema operativo, simplemente es una mejor practica utilizarlo*/

     if(procesoID == -1){ // se maneja el error en la creacion del proceso
        perror("Error en la creacion del proceso hijo"); // si devuelve -1 hubo un error
        exit(EXIT_FAILURE); //y se termina el programa con un codigo de error
    }

    /*el proceso hijo de otro proceso siempre estara asociado a un 0*/
    /*En este caso cada proceso, imprime unas iteraciones de 2 ciclos diferentes*/
    /*el hijo lo imprime en orden ascendente*/
    /*el padre lo imprime en orden descendente*/
    if(procesoID == 0){ 
        //Este es el hijo, el cual imprime su id, mayor al del padre porque es creado después
        printf("\nHola soy Ramirez %d \n\n", getpid());
        for(int i=0; i<5; i++){
            printf("Valor de Bucle: ==# %d #== \n", i); //hace un bucle que imprime numeros de 0 a 4
        }
    } else if (procesoID > 0){
        //Este es el padre el cual imprime tambien su respectivo id
	    printf("\nHola soy Padre Ramirez %d \n\n", getpid());   
        for(int i=5; i>0; i--){
            printf("Valor de Bucle: ==# %d #== \n", i); //hace un bucle que imprime numeros de 5 a 1
        }
    } else {
        printf("Error de llamada a fork \n"); //en caso de error
        exit(EXIT_FAILURE); //y se termina el programa con un codigo de error
    }

    printf("Fin del programa! \n");
    return 0;//devolvemos el 0 que prometimos en la funcion main
}
