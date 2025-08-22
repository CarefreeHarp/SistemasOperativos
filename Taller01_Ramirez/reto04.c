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


#include <stdio.h>
#include <stdlib.h>
//Con ayuda de el comando 'man scanf' y 'man calloc' fue posible determinar cuales 
//eran los #include necesarios


int main(){
	int n, i, *ptr, sum = 0; //declara tres enteros (n, i, sum), un apuntador a tipo entero
	printf("Ingrese numero de elementos\n"); //imprime un texto
	scanf("%d", &n); //lee un numero entero
	ptr = (int*)calloc(n,sizeof(int)); //reserva una cantidad de memoria equivalente a lo que ocupa un tipo entero
	if(ptr == NULL){ // verifica que se haya reservado bien la memoria
		printf("Error! memoria no reservada"); //indica que no se pudo reservar adecuadamente la memoria
		exit(1) ;// se sale del programa si la memoria no se reservo bien
	}
	printf("Ingrese los elementos:\n"); //Imprime un texto
	for(i = 0; i < n; ++i){ //Inicia un ciclo que se repite n veces (lo que haya indicado el usuario)
		scanf("%d", ptr + i); //lee numeros y los va guardando en la memoria reservada a la que apunta ptr
		sum += *(ptr+i);//va sumando los numeros que se le ingresen
	}
	printf("La suma (variable Sum) es = %d\n", sum);//imprime un texto
	free(ptr);//libera la memoria reservada por ptr
	return 0;
}
