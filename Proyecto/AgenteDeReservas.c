/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha:
 * Autores: Daniel Felipe Ramirez Vargas - Guillermo Andrés Aponte Cárdenas          *
 * Materia: Sistemas Operativos                                                      *
 * Descripción: 
*************************************************************************************/

#include <unistd.h> //librería para utilizar funciones como fork() y getpid()
#include <pthread.h> //librería para manejo de hilos 
#include <stdlib.h>// Para utilizar funciones como exit, perror y EXIT_FAILURE (manejo de errores)
#include <fcntl.h>// Incluye la biblioteca para utilizar open y la bandera O_RDWR
#include <stdio.h> //Librería para manejo de entradas y salidas
#include "ModulosDeDefinicion/ModuloAgente.h" //Se incluye el modulo que contiene las declaraciones de las funciones y estructuras


int main(){
    
    printf("Hola mundo Agente\n");
    return 0;
}