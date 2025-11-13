/*******************************************************************
 * Pontificia Universidad Javeriana
 * Facultad de Ingeniería
 * Carrera: Ingeniería de Sistemas
 * Autores: Daniel Ramírez
 * Materia: Sistemas Operativos
 * Tema: Sistema de Ficheros
 * Archivo: lab01.c
 * Descripcion: Este programa dado el nombre de un directorio que esté en el mismo directorio que
 *              el ejecutable de este programa, mostrará el nombre y tamaño de cada uno de
 *              los ficheros regulares que se encuentren en el directorio indicado
 * Fecha: 13/11/25
 ******************************************************************/

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Funcion principal
int main() {

  // Declaración de una estructura DIR llamada d
  DIR *d;

  // Declaracion de dos arreglos de caracteres para guardar el nombre del directorio y de los ficheros
  char nomdir[90], nomfich[90];

  // Declaracion de una estructura del tipo stat para guardar los datos de cada fichero encontrado
  struct stat datos;

  // Declaracion de una estructura del tipo dirent
  struct dirent *direc;

  // Imprime un mensaje por pantalla
  printf("Introduzca el Nombre de un Directorio: ");

  // Lee desde la entrada estandar, es decir, desde la consola
  // Guarda lo leído en nomdir ya que se recibe el nombre del directorio a inspeccionar
  // Lee maximo 90 bytes que es el tamaño del arreglo nomdir
  fgets(nomdir, sizeof(nomdir), stdin);

  nomdir[strlen(nomdir) - 1] = '\0'; /*Eliminamos el \n del Nombre del Fichero*/

  // Si al intentar abrir el archivo recibimos un NULL, se imprime un error y termina el programa
  if ((d = opendir(nomdir)) == NULL) {
    printf("El directorio no existe\n");
    return -1;
  }

  // Mientras aun haya archivos para leer imprime las caracteristicas del mismo
  while ((direc = readdir(d)) != NULL) {
    strcpy(nomfich, nomdir);
    strcat(nomfich, "/");
    strcat(nomfich, direc->d_name);
    stat(nomfich, &datos);
    if (S_ISREG(datos.st_mode))
      printf("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size);
  }

  // Se cierra el directorio
  closedir(d);
}

/*Observaciones/Notas/Conclusiones:
                                La funcion stat recibe la ruta de un fichero y guarda los datos del mismo
                                La funcion ISREG permite identificar si el archivo es un fichero para mostrarlo
                                Es necesario cerrar el directorio al finalizar la ejecución para liberar recursos
*/
