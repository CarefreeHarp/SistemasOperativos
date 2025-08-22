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
//Con ayuda de el comando 'man scanf' y 'man realloc' fue posible determinar cuales 
//eran los #include necesarios


int main(){
	int *ptr, i, n1, n2;// se declaran tres variables de tipo entero (i, n1, n2) y un puntero a tipo de dato entero (*ptr)
	printf("Digite el tamanio que desee reservar \n"); //imprime un texto
	scanf("%d", &n1); //solicita al usuario ingresar el valor de n1
	ptr = (int*)malloc(n1 * sizeof(int)); //reserva n1 * (el tamaño de un tipo de dato entero en bytes) y le asigna a ptr para apuntar a ese bloque de memoria reservado
	printf("Las memorias previamente reservadas: "); //imprime un texto
	for( i = 0; i < n1 ; ++i) //inicia un ciclo for que se repite n1 veces
		printf("\np = %p\n", ptr+i); //imprime la direccion de memoria que guarde ptr y por cada iteracion del ciclo, pasa a mostrar la siguiente
	printf("\n Digite el nuevo tamanio que desee reservar: ");//imprime un texto
	scanf("%d", &n2);//solicita al usuario digitar el valor de n2

	//vuelve a reservar la memoria

	ptr = realloc(ptr, n2 * sizeof(int)); //reasigna la memoria a la que apunta ptr y reserva n2 * (el tamaño de un tipo de dato entero en bytes)
	printf("Las nuevas memorias reservadas: "); //imprime un texto
	for( i = 0; i < n2 ; ++i) //inicia un ciclo for que se repite n2 veces
		printf("\np = %p\n", ptr+i); // imprime por pantalla la direccion de memoria a la que apunta ptr y en cada iteracion, muestra la siguiente  
	free(ptr);//liberamos la memoria a la que apunte ptr
	return 0;
}
