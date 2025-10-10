/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 9 de Octubre del 2025                                                      *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Creacion de procesos fork                                                   *
 * -Identificacion del proceso padre e hijo                                          *
*************************************************************************************/

#include <stdio.h> //librería para manejo de entradas y salidas
#include <unistd.h> //libreria para hacer fork() y getpid()
#include <stdlib.h> //libreria para manejar errores (buenas practicas de programacion)

int main(){
    /*Se invoca la creacion del proceso en para identificarlo mas adelante*/
    pid_t procesoID = fork(); /*Se duplica el proceso y se guarda en un dato de tipo pid_t*/
    /*pid_t se comporta como un int pero es utilizado por buenas prácticas ya que la implementacion de pid_t
    puede cambiar dependiendo del sistema operativo, simplemente es una mejor practica utilizarlo*/

    if(procesoID == -1){ // se maneja el error en la creacion del proceso
        perror("Error en la creacion del proceso hijo"); // si devuelve -1 hubo un error
        exit(EXIT_FAILURE); //y se termina el programa con un codigo de error
    }
    
    if(procesoID == 0){//El hijo de un proceso siempre estará asociado a un 0
        //Este es el hijo, el cual imprime su id, mayor al del padre porque es creado después
        printf("Hola soy Daniel hijo %d \n\n", getpid()); 
    } else {
        //Este es el padre el cual imprime tambien su respectivo id
	    printf("Hola soy Ramirez Padre %d \n\n", getpid());   
    }


    return 0;//devolvemos el 0 que prometimos en la funcion main
}
