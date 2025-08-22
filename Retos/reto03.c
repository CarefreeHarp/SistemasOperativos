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


#include <stdlib.h>
//Con ayuda de el comando 'man malloc' fue posible determinar cual
//era el #include necesarios

int main(){
	int *ptr; // declara un puntero a un tipo de dato entero
	ptr = malloc(15 * sizeof(*ptr)); //Reserva un espacio de memoria equivalente a lo que ocupa un entero multiplicado por 15

	if(ptr != NULL){ //Se realiza la operacion siguiente solamente si malloc reservo bien la memoria
		*(ptr+5) = 480; //le asigna un valor de 480 a lo que apunte ptr mas 5 espacios de memoria equivalentes a lo que ocupen 5 enteros
	}

	return 0;

}
