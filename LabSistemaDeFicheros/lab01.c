/*******************************************************************
 * Pontificia Universidad Javeriana
 * Facultad de Ingeniería
 * Carrera: Ingeniería de Sistemas
 * Autores: Daniel Ramírez
 * Materia: Sistemas Operativos
 * Tema: Sistema de Ficheros
 * Archivo: lab01.c
 * Descripcion: Este programa dado el nombre de un fichero que esté en el mismo directorio que
 *              el ejecutable de este programa, mostrará su contenido limitando la cantidad de bytes leídos por linea
 *              a 256 bytes. El programa al tiempo que va leyendo, escribe por pantalla lo leído y al final cierra el fichero
 *              para liberar recursos
 * Fecha: 13/11/25
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Se declara el nombre del fichero que se va a utilizar
  char *nombrefichero = "../readme.txt";

  // Se declara un dato del tipo FILE para abrir el archivo
  // El primer parametro es el nombre del fichero
  // El segundo parametro es el modo de apertura, en este caso r, es decir, solo lectura
  FILE *fp = fopen(nombrefichero, "r");

  // En casi de error se Imprime el mensaje de error y se devuelve un 1 indicando la incorrecta ejecucion del programa
  if (fp == NULL) {
    printf("Error: No se puede abrir el fichero\n");
    return 1;
  }

  // Se imprime texto anunciado que se va a mostrar el contenido del fichero
  printf("=============================\n");
  printf("Lectura de fichero readme.txt\n");
  printf("=============================\n");

  // Lectura de fichero, maximo 256 bytes por linea
  // lectura de linea por linea (buscar \n)
  const unsigned LARGO_MAX_LINEA = 256;
  char buffer[LARGO_MAX_LINEA]; // Se crea el buffer para guardar el contenido de las lineas del archivo

  // Mientras que aun haya algo que leer, se hace un ciclo while
  // Se usa la funcion fgets que lee desde el archivo
  // El primer parametro es donde se guardará lo que se va a leer
  // El segundo parametro es la cantidad de bytes a leer
  // El tercer parametro es del archivo de donde se va a leer el archivo
  while (fgets(buffer, LARGO_MAX_LINEA, fp)) {
    printf("%s\n", buffer); // Se imprime lo leido
  }

  // Cerrar el fichero
  fclose(fp);

  // Devolvemos 0 para indicar la correcta ejecucion del archivo
  return 0;
}

/*Observaciones/Notas/Conclusiones:
        Es importante despues de abrir el archivo, al final despues de utilizarlo, cerrarlo para liberar recursos
        Además, el programa imprime lineas de maximo 256 bytes teniendo en cuenta que si en el fichero
        hay lineas con un largo mayor, esa linea se dividirá y por pantalla solo se mostrará de maximo 256
*/
