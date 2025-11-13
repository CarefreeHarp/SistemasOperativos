/*******************************************************************
 * Pontificia Universidad Javeriana
 * Facultad de Ingeniería
 * Carrera: Ingeniería de Sistemas
 * Autores: Guillermo Aponte, Daniel Ramírez
 * Materia: Sistemas Operativos
 * Tema: IPC con named Semaphores y Sahred Memory
 * Archivo: 
 * Descripcion:
 * Fecha: 14/11/25
 ******************************************************************/
#ifndef __MODULOCONSUMER_H__
#define __MODULOCONSUMER_H__

#include <stdio.h>// librería para manejo de entradas y salidas
#include <stdlib.h>// librería para usar exit()
#include <unistd.h>// librería para usar funciones como sleep() y close()
#include <sys/mman.h>// librería para usar PROT_READ | PROT_WRITE, MAP_SHARED
#include <sys/stat.h>// librería para otorgar permisos 0644
#include <fcntl.h>// librería para abrir archivos y usar banderas como O_CREAT, O_RDWR
#include <semaphore.h> // librería que permite el uso de semaforos
#define BUFFER 5   // Tamaño del buffer de la memoria compartida

//Estructura que sirve de plantilla para operar la memoria compartida
typedef struct {
    int salida; 
    int entrada;  
    int bus[BUFFER];   
} compartir_datos;

void abrirSemaforos(sem_t** vacio, sem_t** lleno);
void abrirMemoriaCompartida(int* fd_compartido);
void mapearYConsumir(compartir_datos** compartir, sem_t* vacio, sem_t* lleno, int fd_compartido);
void liberarRecursos(int fd_compartido, sem_t* vacio, sem_t* lleno, compartir_datos* compartir);


#endif