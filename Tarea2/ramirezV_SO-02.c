/************************************************************************
*                                                                       *
*                                                                       *
*                       ██████╗ ██╗   ██╗     ██╗                       *
*                       ██╔══██╗██║   ██║     ██║                       *
*                       ██████╔╝██║   ██║     ██║                       *
*                       ██╔═══╝ ██║   ██║██   ██║                       *
*                       ██║     ╚██████╔╝╚█████╔╝                       *
*                       ╚═╝      ╚═════╝  ╚════╝                        *
*                                                                       *
*                                                                       *
*                    Pontificia Universidad Javeriana                   *	
*         ======================================================        *	
* Autor: Daniel Felipe Ramirez Vargas                                   *
* Materia: Sistemas Operativos                                          *
* Docente: J. Corredor, PhD                                             *
* Objetivo: Crear archivos en C para lograr una compilacion modular     *
*                                                                       *
* Descripcion: Creacion de un archivo main, funciones que utiliza,      *
*               archivo header y makefile para compilar los modulos     *
*                                                                       *
~       ~       ~       ~       ~       ~       ~       ~       ~       */


#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char* argv[]){

	if(argc<4){
		printf("$./ejecutable valor 1 (altura) valor 2 (masa corporal) valor 3\n");
		exit(0);
	}

	float altura = (float)atof(argv[1]);
	float masacorporal = (float)atof(argv[2]);
	int N = (int)atof(argv[3]);

	printFunction();

	float valorIMC = imcFunction(masacorporal,altura);

	printf("El indice de masa corporal es %f\n", valorIMC);
	printf("********************************\n\n\n");

	printf("********************************\n");
	printf("*           Matrices           *\n");
	printf("********************************\n");
	float m1, m2, m3;

	llenarMatriz(N,m1,m2);
	impMatrix(m1,N);
	impMatrix(m2,N);

	float mc = matrixMult(N,m1,m2);
	impMatrix(mc, N);

	return 0;
}
