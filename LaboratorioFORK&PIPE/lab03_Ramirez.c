/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 9 de Octubre del 2025                                                      *
 * Autor: Daniel Felipe Ramirez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Creacion de procesos fork                                                   *
 * - Identificacion del proceso padre e hijo                                         *
 * - Procesos duplicados                                                             *
 * - Comunicacion entre procesos con PIPE                                            *
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    //Creacion de la tuberia de comunicacion entre procesos
    int pipefd[2];
    pid_t pHijo_PID; //Id del hijo como proceso


    //Verificar si la tuberia se creo correctamente
    if(pipe(pipefd) == -1){
        perror("Error en la creacion de la tuberia");
        exit(EXIT_FAILURE);
    }

    /*Se invoca la creacion del proceso en un INT para identificar*/
    pHijo_PID = fork();

    if(pHijo_PID == -1){
        perror("Error en la creacion del proceso hijo");
        exit(EXIT_FAILURE);
    }

    /*Se duplica el proceso*/
    if(pHijo_PID == 0){
        printf("\nHola soy Ramirez %d \n\n", getpid());
        /*Lectura del mensaje desde el hijo*/
        close(pipefd[1]); //Cierra el extremo de escritura del pipe
        char mensaje[100]; //Capacidad para almacenar el mensaje
        int lecturaB = read(pipefd[0], mensaje, sizeof(mensaje)); //Lee el mensaje del pipe
        // verificacion de la lectura desde el pipe
        if(lecturaB == -1){
            perror("Error en la lectura del pipe");
            exit(EXIT_FAILURE);
        }
        printf("Hijo recibe: ==# %.*s #== \n", lecturaB, mensaje);
        close(pipefd[0]); //Cierra el extremo de lectura del pipe



    } else if (pHijo_PID > 0){
        /*ENVIO del mensaje desde el hijo*/
        close(pipefd[0]); //Cierra el extremo de lectura del pipe
        char mensaje[] = "hijo, trae el pan y las gaseosas...!";
        int escrituraB = write(pipefd[1], mensaje, sizeof(mensaje)); //envia el mensaje por el pipe
        // verificacion de la escritura desde el pipe
        if(escrituraB == -1){
            perror("Error en la escritura del pipe");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]); //Cierra el extremo de escritura del pipe
    } else {
        printf("Error de llamada a fork \n");
    }

    printf("Fin del programa! \n");
    return 0;
}
