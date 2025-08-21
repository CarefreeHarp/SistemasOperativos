/*Daniel Felipe Ramirez Vargas
Sistemas operativos
Reto #1
*/
#include <stdio.h>//librerias necesarias para el funcionamiento
#include <string.h>
#include <stdlib.h>

int main(){
	char *p; //Se declara un puntero a un tipo de char
	char *q = NULL; //Se declara un puneto a un tipo de char y se le asigna un null para no apuntar a nada
	printf("adress of p = %s\n", p); //imprime el contenido de lo que apunte p

	strcpy(p, " Hola soy el mejor sistema operativo!"); //copia en p la cadena "Hola soy el mejor sistema operativo"
	printf("%s\n", p); //imprime el contenido de la cadena a la que apunte p
	printf("about to copy \"Goodbye\" to q\n"); //imprime un texto
	strcpy(q, "Good Bye!!"); //copia la cadena "Good Bye!!" en q
	printf("String copied\n"); //imprime un texto informando que se pudo copiar
	printf("%s\n", q); //imprime el contenido de q por pantalla

	return 0;

}
