/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 16 de octubre de 2025                                                      *
 * Autor: Daniel Felipe Ramírez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Implementación de productor-consumidor a partir de Pipe Named               *
 * Descripción:                                                                      *
 *  - Este programa implementa el proceso cliente utilizando un named pipe.          *
 *    Permite enviar mensajes al servidor, el cual los invierte y devuelve.          *
 *    El cliente:                                                                    *
 *     1. Abre el named pipe creado previamente por el servidor.                     *
 *     2. Envía cadenas de texto ingresadas por el usuario.                          *
 *     3. Espera la respuesta del servidor e imprime el resultado.                   *
 *     4. Finaliza cuando el usuario ingresa la palabra "end".                       *
 *                                                                                   *
 *    Nota: La explicación detallada sobre la creación del named pipe (mkfifo),      *
 *          el funcionamiento de las funciones open, close, write y read se          *
 *          encuentra documentada en el archivo servidor.c                           *
 *                                                                                   *
 *************************************************************************************/
#include <stdio.h>// Incluye la biblioteca para manejar entradas y salidas
#include <string.h>// Incluye la biblioteca para manejar funciones de cadenas como strcpy, strcmp y strlen
#include <fcntl.h>// Incluye la biblioteca para utilizar open y la bandera O_RDWR
#include <unistd.h>// Incluye la biblioteca para las funciones del sistema como read, write y close
#include <stdlib.h>// Para utilizar funciones como exit, perror y EXIT_FAILURE (manejo de errores)

// Define la ruta del fichero en el directorio tmp (ubicado en la raíz del sistema) llamado PIPE_COMUNICATOR
#define FIFO_FILE "/tmp/PIPE_COMUNICATOR"

int main() {
   int fd;// Declara la variable para guardar el descriptor de archivo del named pipe
   int end_process;// Declara la variable para el resultado de la comparación entre la cadena ingresada y "end"
   int stringlen;// Declara la variable para saber la longitud de la cadena ingresada
   int read_bytes;// Declara la variable que almacenará la cantidad de bytes leídos desde el named pipe
   char readbuf[80];// Declara un arreglo de char donde se guardará el texto leído o recibido desde el servidor
   char end_str[5];// Declara un arreglo de char que contendrá la palabra "end"

   //Mensaje para indicar cómo finalizar el proceso
   printf("FIFO_CLIENT: ENVÍE MENSAJES. PARA TERMINAR, ESCRIBA \"end\"\n"); 
   
   //Apertura del named pipe con open (librería fcntl.h)
   // El primer parámetro es la ruta del fichero definida al comienzo
   // El segundo parámetro es el modo en el que se abrirá la tubería desde el cliente
   // En este caso se abre para lectura y escritura con la flag O_RDWR
   // Además, se maneja el error en caso de que no se abra correctamente el archivo del pipe
   fd = open(FIFO_FILE, O_RDWR);
   if (fd == -1) {
      perror("Error abriendo el named pipe");
      exit(EXIT_FAILURE);
   }

   //Guarda la cadena "end" en la variable end_str para saber cuándo terminar el proceso
   strcpy(end_str, "end");
   
   //Ciclo infinito hasta que se escriba "end"
   while (1) {
      //Solicita al usuario escribir algo en el named pipe
      printf("(CLIENTE) ESCRIBA AQUÍ SU MENSAJE: ");

      //Se lee utilizando la función fgets (librería stdio.h) 
      // El primer parámetro es donde se guardará lo que se escribe
      // El segundo parámetro es cuántos bytes/caracteres se quieren leer
      // El tercer parámetro es por donde llegará el flujo de entrada, puede ser por ejemplo de un archivo
      // pero en este caso es directamente del teclado
      // En este caso, fgets devuelve el mismo readbuf si la lectura es exitosa, si no, devuelve NULL
      // Según esto, se maneja el error en caso de lectura del teclado fallida
      if (fgets(readbuf, sizeof(readbuf), stdin) == NULL) {
         perror("Error leyendo del teclado");
         close(fd);
         exit(EXIT_FAILURE);
      }

      //stringlen guarda el tamaño del mensaje que se leyó del teclado
      stringlen = strlen(readbuf);

      //Añade un \0 al final del mensaje para indicar que ahí termina la cadena de caracteres 
      readbuf[stringlen - 1] = '\0';

      //Verifica si se debe terminar el proceso, es decir, si lo que se leyó del teclado es "end"
      // strcmp devuelve 0 si los dos parámetros enviados (char *) son iguales
      end_process = strcmp(readbuf, end_str);
      
      // Verifica si debe terminar la ejecución
      if (end_process != 0) {
         //En caso de no terminar:

         //Se escribe en el named pipe lo que se haya leído del teclado
         // y se tiene en cuenta el posible error de escritura
         if (write(fd, readbuf, strlen(readbuf)) == -1) {
            perror("Error escribiendo en el named pipe");
            close(fd);
            exit(EXIT_FAILURE);
         }

         //Se muestra por pantalla lo que se acaba de enviar por el named pipe
         printf("FIFOCLIENT: STRING ENVIADO: \"%s\" LA LONGITUD ES %d\n", readbuf, (int)strlen(readbuf));

         /*El proceso se duerme durante 1 segundos para darle tiempo al servidor de leer el named pipe,
         de lo contrario, el cliente recibiría de nuevo el mensaje cuando se repita el ciclo*/
         sleep(1);

         //Ahora se lee lo que sea que haya en el pipe, en caso de no haber nada aún, espera a que haya algo
         // En este caso, el servidor recibe el mensaje, lo invierte y lo vuelve a mandar por el named pipe
         // También se tiene en cuenta el error en caso de fallo al leer del named pipe
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         if (read_bytes == -1) {
            perror("Error leyendo del named pipe");
            close(fd);
            exit(EXIT_FAILURE);
         }
         
         //Añade un \0 al final de lo que se haya leído del named pipe para poder imprimir correctamente
         readbuf[read_bytes] = '\0';

         //Muestra por pantalla el string recibido (el que se envió pero invertido)
         printf("FIFOCLIENT: STRING RECIBIDO: \"%s\" LA LONGITUD ES %d\n", readbuf, (int)strlen(readbuf));
      } else {

         //En caso de que se haya escrito "end" en el teclado, igualmente se envía por el pipe
         // y se verifica que no haya error escribiendo en él
         if (write(fd, readbuf, strlen(readbuf)) == -1) {
            perror("Error escribiendo en el FIFO");
            close(fd);
            exit(EXIT_FAILURE);
         }

         //Se muestra que se envió "end" y su longitud (3)
         printf("FIFOCLIENT: STRING ENVIADO: \"%s\" LA LONGITUD ES %d\n", readbuf, (int)strlen(readbuf));

         //Se cierra el named pipe en base al descriptor del archivo del mismo (biblioteca unistd.h) 
         close(fd);

         break;//Acaba el ciclo infinito de lectura
      }
   }
   return 0;//Devuelve el 0 que se prometió en la función main
}
