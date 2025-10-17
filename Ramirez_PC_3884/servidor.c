/*************************************************************************************
 * Pontificia Universidad Javeriana                                                  *
 * Fecha: 16 de octubre de 2025                                                      *
 * Autor: Daniel Felipe Ramírez Vargas                                               *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Implementación de productor-consumidor a partir de Pipe Named               *
 * Descripción:                                                                      *
 *  - Este programa implementa el servidor utilizando un named pipe:                 *
 *  1. Se crea el archivo pipe                                                       *                                                              *
 *  2. Se abre el pipe en lectura y escritura                                        *
 *  3. Espera mensajes enviados por el cliente                                       *
 *  4. Cuando recibe un mensaje, lo muestra por pantalla y lo invierte usando        *
 *     la función reverse_string                                                     *
 *  5. Manda el mensaje invertido por la tubería para que el cliente la reciba       *
 *  6. Finaliza cuando recibe el mensaje "end" por el pipe                           *              
 *************************************************************************************/
#include <stdio.h> // Incluye la biblioteca para el manejo de entradas y salidas
#include <sys/types.h> // Incluye la biblioteca para el manejo de tipos de datos como por ejemplo pid_t
#include <unistd.h> // Incluye la biblioteca para usar read, write, close y sleep
#include <sys/stat.h> // Incluye la biblioteca para usar mkfifo
#include <fcntl.h> // Incluye la biblioteca para usar open y manejar sus banderas
#include <string.h> // Incluye la biblioteca para el manejo de cadenas de caracteres como strlen, strcpy, strcmp
#include <stdlib.h> // para utilizar funciones como exit, perror y utilizar EXIT_FAILURE (manejar errores)

// define la ruta fichero en el directorio tmp (ubicado en la raíz del sistema) llamado PIPE_COMUNICATOR
#define FIFO_FILE "/tmp/PIPE_COMUNICATOR"


void reverse_string(char *); // Declara el prototipo de la función que invierte la cadena de caracteres, recibe un puntero a char

/* Función principal */
int main() {
  int fd; // Declara la variable fd que almacenará el descriptor de archivo del named pipe
  char readbuf[80]; // Declara un arreglo estático de char para guardar la lectura
  char end[10]; // Declara un arreglo estático de char para guardar la palabra "end"
  int to_end; // Declara la variable to_end que almacenará el resultado de la comparación entre readbuf y end
  int read_bytes; // Declara la variable read_bytes que almacenará la cantidad de bytes leídos

  /*Creación del FIFO (named pipe) */
  // Utiliza la función mkfifo de la biblioteca sys/stat.h
  // El primer parámetro es el nombre del archivo del named pipe que se ha definido antes
  // El segundo parámetro son los permisos de acceso al archivo (S_IFIFO | 0640)
  // S_IFIFO indica que se está creando un FIFO (definido en la biblioteca sys/stat.h)
  // 0640 otorga permisos de lectura y escritura para el propietario, es decir, el usuario que crea el FIFO, en este caso el servidor
  // En este ejemplo, el número 0640 indica lo siguiente:
  // 1, 2 y 4 significan ningún permiso, escritura y lectura respectivamente, mientras que 0 significa sin permisos
  // Si se suman los permisos se obtiene un número entre 0 y 7
  // Para este ejemplo:
  // 0: prefijo que indica que es un número en base 8
  // 6: (segundo dígito) permisos del usuario propietario 4+2 = 6 (lectura y escritura)
  // 4: (tercer dígito) permisos del grupo al que pertenece el usuario propietario 4 = solo lectura
  // 0: (cuarto dígito) permisos para otros usuarios 0 = sin permisos
  // El operador | que aparece en S_IFIFO | 0640 es un OR a nivel de bits
  // Así se combinan los bits de S_IFIFO y 0640, ya que el segundo parámetro es __mode_t __mode y se debe enviar una serie de bits
  // También se maneja el error en caso de que no cree el named pipe
  if (mkfifo(FIFO_FILE, S_IFIFO | 0640) == -1) {
    perror("Error creando el named pipe");
    exit(EXIT_FAILURE);
  }

  strcpy(end, "end"); // Guarda la cadena "end" en el arreglo end

  // Abre el named pipe en modo lectura y escritura, usando la función open (biblioteca fcntl.h)
  // Indica como primer parámetro el nombre del archivo del named pipe y como segundo parámetro la bandera O_RDWR
  // O_RDWR abre el archivo en modo lectura y escritura
  // Asi mismo se maneja el error en caso de que no se pueda abrir
  fd = open(FIFO_FILE, O_RDWR); 
  if (fd == -1) {
    perror("Error abriendo el named pipe");
    exit(EXIT_FAILURE);
}

  while (1) { // Ejecuta un ciclo infinito para que el servidor esté siempre escuchando
    /*Lectura, función read de la biblioteca unistd.h*/
    // El primer parámetro es el descriptor de archivo del named pipe
    // El segundo parámetro es la cadena de caracteres declarada antes donde se almacenará la lectura
    // El tercer parámetro es el tamaño a leer
    // La función devuelve la cantidad de bytes leídos
    //tambien se maneja el error en caso de que no haya lectura exitosa
    read_bytes = read(fd, readbuf, sizeof(readbuf)); 
      if (read_bytes == -1) {
      perror("Error leyendo del named pipe");
      close(fd);
      exit(EXIT_FAILURE);
    }

    /*Procesamiento de la cadena leída*/
    // Coloca el carácter nulo al final de la cadena leída para que se pueda imprimir correctamente
    readbuf[read_bytes] = '\0';

    // Imprime la cadena leída y su longitud
    // Se debe hacer un cast de (int) a strlen porque strlen devuelve un size_t y printf espera un int por el %d
    printf("FIFOSERVER: STRING RECIBIDO: \"%s\" LA LONGITUD ES %d\n", readbuf, (int)strlen(readbuf)); 

    // Compara la cadena leída con la palabra "end"
    // strcmp devuelve 0 si las cadenas son iguales
    to_end = strcmp(readbuf, end); 
    
    // Si la cadena leída es "end", cierra el named pipe y sale del ciclo infinito
    if (to_end == 0) {
      close(fd); // Cierra el named pipe mediante la función close (biblioteca unistd.h) 
      break;     // Sale del ciclo y NO reenvía el mensaje invertido
    }

    // Invierte la cadena leída usando la función reverse_string y la guarda en readbuf
    reverse_string(readbuf);

    // Imprime la cadena invertida y su longitud
    printf("FIFOSERVER: STRING INVERTIDO: \"%s\" LA LONGITUD ES %d\n", readbuf, (int)strlen(readbuf));

    // Escribe por el pipe la cadena invertida usando la función write (biblioteca unistd.h)
    // El primer parámetro es el descriptor de archivo del named pipe
    // El segundo parámetro es la cadena de caracteres que se va a escribir
    // El tercer parámetro es la cantidad de bytes a escribir, en este caso la longitud de la cadena
    // Esto se puede hacer porque se abrió el pipe en modo O_RDWR 
    //Finalmente se maneja el error en caso de un fallo escribiendo en el named pipe
    if (write(fd, readbuf, strlen(readbuf)) == -1) {
      perror("Error escribiendo en el named pipe");
      close(fd);
      exit(EXIT_FAILURE);
  }
    
    /*El proceso se duerme durante 2 segundos para darle tiempo al cliente de leer el named pipe,
    de lo contrario, el servidor recibiría de nuevo el mensaje cuando se repita el ciclo*/
    sleep(2);
  }

  return 0; //Devuelve el 0 que se prometió en la función main
}

/*Función para invertir una cadena enviada como parámetro*/
void reverse_string(char *str) {
  int last, first;
  char temp;
  last = strlen(str) - 1; // La posición del último carácter de la cadena
  first = 0;              // La posición del primer caracter de la cadena

  while (first < last) { //Mientras llega a la mitad, resta la posición del último y suma la del primero
    //Realiza el intercambio de caracteres para voltear la cadena
    temp = str[first]; 
    str[first] = str[last];
    str[last] = temp;

    first++;
    last--;
  }

  return; //Finaliza la función
  //Nota: Como se envía la cadena por referencia, ya se actualiza globalmente
}
