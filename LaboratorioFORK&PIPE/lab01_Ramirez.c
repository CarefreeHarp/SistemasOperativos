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
#include <stdlib.h> //

int main(){
    /*Se invoca la creacion del proceso en un INT para identificar*/
    pid_t procesoID = fork(); /*Se duplica el proceso*/

    
    if(procesoID == 0){//El hijo de un proceso siempre estará asociado a un 0
        //Este es el hijo, el cual imprime su id, mayor al del padre porque es creado después
        printf("Hola soy Daniel hijo %d \n\n", getpid()); 
    } else {
        //Este es el padre el cual imprime tambien su respectivo id
	    printf("Hola soy Ramirez Padre %d \n\n", getpid());   
    }


    return 0;
}
