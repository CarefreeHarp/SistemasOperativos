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

#include <stdio.h> //libreria para manejo de entradas y salidas
#include <stdlib.h> // libreria para manejar errores (buenas practicas de programacion)
#include <unistd.h> // libreria para hacer fork(), getpid() y pipe()

int main(){
    //Creacion de la tuberia de comunicacion entre procesos
    int pipefd[2];
    pid_t pHijo_PID; //se crea una variable del tipo pid_t para almacenar el id del proceso hijo


    //Verificar si la tuberia se creo correctamente
    if(pipe(pipefd) == -1){ //la funcion pipe devuelve -1 en caso de error y crea el pipe en el arreglo definido arriba
        perror("Error en la creacion de la tuberia");//da error
        exit(EXIT_FAILURE);// y se termina el programa con un codigo de error
    }

    /*Se invoca la creacion de un proceso hijo*/
    pHijo_PID = fork();

    if(pHijo_PID == -1){ //se verifica si hubo un error en la creacion del proceso
        perror("Error en la creacion del proceso hijo");// si devuelve -1 hubo un error
        exit(EXIT_FAILURE);// y se termina el programa con un codigo de error
    }

    //Aca decidimos que hace cada proceso, el padre y el hijo siendo el hijo el que siempre va asociado a un 0
    if(pHijo_PID == 0){
        /*Lectura del mensaje desde el hijo*/
        close(pipefd[1]); //Cierra el extremo de escritura del pipe
        char mensaje[100]; //Crea un apuntador a char y fija 100 bytes de memoria 
        //para darle capacidad al mensaje que se va a leer del pipe


        int lecturaB = read(pipefd[0], mensaje, sizeof(mensaje)); //Lee el mensaje del pipe con 3 parametros
        //parametro #1: el extremo de lectura del pipe
        //parametro #2: el apuntador a la direccion de memoria donde se va a guardar el mensaje que reciba
        //parametro #3: el tamaño maximo del mensaje que se va a leer
        //finalmente devuelve un entero con el numero de bytes leidos o -1 en caso de error

        // verificacion de la lectura desde el pipe
        if(lecturaB == -1){ //como dijimos antes, devuelve -1 en caso de error leyendo del pipe
            perror("Error en la lectura del pipe"); // da error
            exit(EXIT_FAILURE);// y se termina el programa con un codigo de error
        }
        printf("Hijo recibe: ==# %.*s #== \n", lecturaB, mensaje); //imprime el mensaje recibido del pipe utilizando
        // %*.s para definir la cantidad de caracteres a imprimir, en este caso la cantidad de bytes leidos
        // en este caso lecturaB es un dato del tipo entero que contiene el numero de bytes leidos de la tuberia
        //y es por eso que se asocia al * y luego la s se asocia al mensaje como tal que se quiere mostrar
        //por pantalla

        close(pipefd[0]); //Cierra el extremo de lectura del pipe porque ya no lo usa mas
        // ATENCION: se cierra el extremo de lectura del pipe solo para el proceso hijo, no para el padre
        //El padre lo cierra cuando ya no lo va a usar mas, osea para el aun es funcional ese extremo

    } else if (pHijo_PID > 0){
        /*ENVIO del mensaje desde el hijo*/
        close(pipefd[0]); //Cierra el extremo de lectura del pipe para el proceso hijo
        //cabe aclarar que el pipe cierra el extremo de lectura para el proceso hijo unicamente
        //y que el extremo de lecutra del padre sigue abierto y funcionando hasta que el mismo lo cierre
        //lo mismo aplica para el extremo de escritura del pipe

        char mensaje[] = "hijo, trae el pan y las gaseosas...!"; // se crea el mensaje a enviar por el pipe
        int escrituraB = write(pipefd[1], mensaje, sizeof(mensaje)); //envia el mensaje por el pipe con la funcion write
        //esta funcion utiliza 3 parametros,
        //el lado del pipe por donde se envia el mensaje, el apuntador a la direccion de memoria 
        //que contiene el mensaje y el tamaño del mensaje
        //y finalmente devuelve un entero con el numero de bytes escritos o -1 en caso de error

        // verificacion de la escritura desde el pipe
        if(escrituraB == -1){//como dijimos antes, devuelve -1 en caso de error escribiendo en el pipe
            perror("Error en la escritura del pipe");// da error
            exit(EXIT_FAILURE);// y se termina el programa con un codigo de error
        }
        close(pipefd[1]); //Cierra el extremo de escritura del pipe
    } else {
        printf("Error de llamada a fork \n"); //en caso de error
        exit(EXIT_FAILURE); //y se termina el programa con un codigo de error
    }

    printf("Fin del programa! \n");
    return 0;//devolvemos el 0 que prometimos en la funcion main
}
