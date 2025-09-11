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
#include <string.h>
//Con ayuda de el comando 'man scanf' y 'man strcpy' fue posible determinar cuales 
//eran los #include necesarios

int main(){
	char *p; //Se declara un puntero a un tipo de dato char
	char *q = NULL; //Se declara un puntero a un tipo de char y se le asigna un null para no apuntar a nada
	printf("adress of p = %s\n", p); //imprime el contenido de lo que apunte p

	strcpy(p, " Hola soy el mejor sistema operativo!"); //copia en p la cadena "Hola soy el mejor sistema operativo"
	printf("%s\n", p); //imprime el contenido de la cadena a la que apunte p
	printf("about to copy \"Goodbye\" to q\n"); //imprime un texto
	strcpy(q, "Good Bye!!"); //copia la cadena "Good Bye!!" en q
	printf("String copied\n"); //imprime un texto informando que se pudo copiar
	printf("%s\n", q); //imprime el contenido de q por pantalla

	return 0;

}

