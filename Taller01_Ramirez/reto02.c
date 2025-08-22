/************************************************************************
*                                                                       *
*                    Pontificia Universidad Javeriana                   *
*																		*
*         ======================================================        *
* Autor: Daniel Felipe Ramirez Vargas                                   *
* Materia: Sistemas Operativos                                          *
* Docente: J. Corredor, PhD                                             *
* Objetivo: Estudiar el comportamiento de la reserva de memoria en c    *
*           usando malloc, calloc, realloc.							    *
*                                                                       *
~       ~       ~       ~       ~       ~       ~       ~       ~       */

//librerias necesarias para el funcionamiento
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Con ayuda de el comando 'man scanf', 'man strcpy' y 'man malloc' fue posible determinar cuales 
//eran los #include necesarios


int main(){
	char *q = NULL; //declara un puntero a un dato de tipo char y le asigna un nulo
	printf("Solicitando espaco para 'Goodbye'\n"); // imprime un texto
	q = (char*)malloc(strlen("Goodbye")+1); //reserva la cantidad de memoria que ocupe la cadena 'Goodbye' y le suma 1, ademas hace un casteo de que es una variable apuntadora a un tipo char

	if(!q){ //verifica si la reserva de memoria fue exitosa
		perror("Reserva de memoria fallida porque");
		exit(1);//termina el programa si no se pudo reservar la memoria
	}

	printf("A punto de copiar 'Goodbye' a q en la direccion %s\n", q);//imprime un texto
	strcpy(q, "Goodbye");// copia la cadena 'Goodbye' en q
	printf("String copiado !!\n");//imprime un texto
	printf("%s\n",q);//imprime el contenido de q osea la cadena 'Goodbye'
	return 0;
}
