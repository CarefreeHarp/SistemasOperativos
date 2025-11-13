/*******************************************************************
 * Pontificia Universidad Javeriana
 * Facultad de Ingeniería
 * Carrera: Ingeniería de Sistemas
 * Autores: Daniel Ramírez
 * Materia: Sistemas Operativos
 * Tema: Sistema de Ficheros
 * Archivo: lab03.c
 * Descripcion: Este programa dado el nombre de un directorio que esté en el mismo directorio que
 *              el ejecutable de este programa, mostrará el nombre, modo, permisos y
 *              los ficheros regulares modificados en los últimos 10 días que se encuentren en el directorio indicado
 * Fecha: 13/11/25
 ******************************************************************/

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// Funcion principal
int main() {
  // Declaracion de variables
  int er, i = 0;
  // Declaracion de arreglos de caracteres
  char nomdir[100], nomfich[100], resp[30];
  char *fechaDeAcceso;

  // Declaracion de una estructura tipo atr para obtener atributos
  struct stat atr;

  // Declaracion de puntero a estructura tipo DIR y dirent para leer directorios
  DIR *d;
  struct dirent *rd1;

  // Declaracion de una variable del tipo time_t para manejar fechas
  time_t fecha;

  // Solicitar al usuario el nombre del directorio a evaluar
  printf("Nombre directorio\n");
  fgets(nomdir, sizeof(nomdir), stdin);

  /* hay que quitar el \n del nombre del directorio*/
  nomdir[strlen(nomdir) - 1] = '\0';

  // Obtener la fecha actual
  fecha = time(&fecha);

  // Abrir el directorio y en caso de error finalizar la ejecucion
  if ((d = opendir(nomdir)) == NULL) {
    printf("No existe ese directorio \n");
    return -1;
  } else {
    // Leer el directorio hasta el final
    while ((rd1 = readdir(d)) != NULL) {

      // Excluir los directorios especiales . y .. , es decir los actuales y padres
      if ((strcmp(rd1->d_name, ".") != 0) && (strcmp(rd1->d_name, "..") != 0)) {

        //Esta i se utiliza para mostrar bien los resultados
        i++;

        // Construir el nombre completo del fichero
        strcpy(nomfich, nomdir);
        strcat(nomfich, "/");
        strcat(nomfich, rd1->d_name);

        // imprimir la informacion del fichero con ayuda de stat obteniendo todos sus atributos
        printf("RESULTADO %d :%s:", i, nomfich);
        er = stat(nomfich, &atr);

        // Si falla la extraccion de atributos del archivo
        if (er != 0) {
          perror("stat");
          continue; // Salta a la siguiente entrada del directorio, es decir, la siguiente iteracion
        }

        // Mostrar los permisos de lectura para el propietario
        printf("modo :%#o:", atr.st_mode);

        // Comprobar si tiene permiso de lectura para el propietario, esto se hace con un AND lógico a nivel de bits
        // Ya que el segundo dígito hace referencia a los permisos para el propietario, el segundo digito es para los del mismo grupo
        // Y el tercero es para los demás usuarios
        // En este caso el 4 indica esos permisos
        if ((atr.st_mode & 0400) != 0)
          printf(" permiso R para propietario\n");
        else
          printf(" No permiso R para propietario\n");

        //Quitamos el salto de linea al final del ctime para poder imprimirlo bien
        fechaDeAcceso = ctime(&atr.st_mtime);
        fechaDeAcceso[strlen(fechaDeAcceso) -1] = '\0';

        // Comprobar si es un directorio o un fichero regular
        if (S_ISDIR(atr.st_mode))
          printf("RESULTADO %d Es un directorio \n", i);
        if (S_ISREG(atr.st_mode))
          /* ficheros modificados en los últimos 10 dias  segun la fecha que hayamos obtenido*/
          if ((fecha - 10 * 24 * 60 * 60) < atr.st_mtime) {
            printf("RESULTADO %d:%s: fecha acceso %s, en sgdos %ld\n", i,  rd1->d_name, fechaDeAcceso, atr.st_mtime);
          }
      }
    }

    // Cerramos el directorio
    closedir(d);
  }
  return 0;
}

/*Observaciones/Notas/Conclusiones:
    El programa permite listar los ficheros de un directorio especificado por el usuario, mostrando sus atributos, permisos y aquellos modificados en los últimos 10 días
    Se utilizan funciones del sistema para manejar directorios y obtener información de los ficheros
    Es importante manejar correctamente las cadenas de caracteres para construir rutas completas y evitar errores al acceder a los ficheros (borrar el salto de línea)
    Es importante cerrar el directorio al terminar de utilizarlo
    NOTA IMPORTANTE: ctime() y time() mide los segundos transcurridos desde las 00:00:00 del 01-01-1970 (Un estandar de UNIX)
*/
