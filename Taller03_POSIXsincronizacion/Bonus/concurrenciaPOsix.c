 /*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Autores: Guillermo Aponte, Daniel Ramírez
 * Fecha: 27/10/2025
 * Tema: Posix para la creación de hilos concurrentes:
 * Descripción:
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct argHilos{
        int inicio;
        int fin;
        int *vector;
        int maxparcial;
};

typedef struct argHilos param_H;

void *buscarMax(void *parametro){
        param_H *argumentos = (param_H *)parametro;
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];
        for(int i=0; i<argumentos->fin; i++){
                if(argumentos->vector[i] > argumentos->maxparcial)
                        argumentos->maxparcial = argumentos->vector[i];
        }
        pthread_exit(0);
        return NULL;
}

int main(int argc, char *argv[]) {
        FILE *fichero;
        int n, nhilos, i;
        int *vec;
        int ret, maximo;
        if (argc!=3) {
                fprintf(stderr, "Error en número de argumentos \n");
                exit(-1);
        }
        fichero = fopen(argv[1], "r");
        if (fichero == NULL) {
                perror("No se puede abrir fichero");
                exit(-2);
        }
        ret = fscanf(fichero, "%d", &n);
        if (ret !=1) {
                fprintf(stderr, "No se puede leer tamaño\n");
                exit(-3);
        }
        nhilos = atoi(argv[2]);
        vec = malloc(sizeof(int) * n);
        for (i=0;i!=n;++i) {
                ret = fscanf(fichero, "%d", &vec[i]);
                if (ret !=1) {
                        fprintf(stderr, "No se puede leer elemento nro %d\n", i);
                        fclose(fichero);
                        free(vec);
                }
        }
        maximo = maximoValor(vec,n,nhilos);
        printf("Máximo: %d\n", maximo);
        fclose(fichero);
        free(vec);
        return 0;
}

