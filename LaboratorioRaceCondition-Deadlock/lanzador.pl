#!/usr/bin/perl
#************************************************************************************
# Pontificia Universidad Javeriana                                                  *
# Fecha: 6 de Noviembre del 2025                                                    *
# Autor: Daniel Felipe Ramirez Vargas                                               *
# Materia: Sistemas Operativos                                                      *
# Descripción: Programa que ejecuta todos los laboratorios sobre hilos.             *
#			   Para ejecutar, se debe escribir el comando ./lanzador.pl             * 
#			   en la terminal y se automatizará la compilación con Makefile,		*
#			   así como la ejecución pertinente de cada laboratorio.				*
#			   Se proporcionan argumentos a los programas que necesiten y se 		*
#			   ejecutan varias veces aquellos programas donde se quiere evidenciar	*
#			   la aparición de Race Conditions.										*
#************************************************************************************


$Path = `pwd`; # guarda el path del path actual
chomp($Path); # elimina el salto de línea al final de la variable 

# nombre de los ejecutables a correr
@laboratorios = (
	"lab_pthread00_Ramirez",
	"lab_pthread01_Ramirez",
	"lab_pthread02_Ramirez",
	"lab_pthread03_Ramirez",
	"lab_pthread04_Ramirez",
	"lab_pthread05_Ramirez",
	"lab_pthread06_Ramirez",
	"lab_pthread07_Ramirez",
	"lab_pthread08_Ramirez"
);

# Compilación con el Makefile
printf("make clear\n");
system("make clear");
printf("make\n");
system("make");

#Para cada laboratorio, se aplican reglas diferentes para ejecutarlos
#En el caso del laboratiorio #0, siendo el único programa que requiere de argumentos, se puso por defecto como 10 (se puede modificar a su gusto).
#En el caso del laboratorio 4 al 8, se imprime un mensaje adicional ya que el laboratorio 4 debe hacer muchas iteraciones y se demorará bastante,
# mientras que del laboratorio 5 al 8, se ejecutará 1000 veces cada uno para evaluar posibles Race Conditions.
#El resto de laboratorios se ejecutan con normalidad.
foreach $lab (@laboratorios){
	printf("\n\n\n========================= RESULTADO %s =========================\n", $lab);
	if( $lab eq "lab_pthread00_Ramirez"){

		system("$Path/Ejecutables/$lab 10"); #Se puede cambiar aquí el valor del argumento para el laboratorio #0

	} elsif($lab eq "lab_pthread04_Ramirez" || $lab eq "lab_pthread05_Ramirez" || $lab eq "lab_pthread06_Ramirez" || $lab eq "lab_pthread07_Ramirez" || $lab eq "lab_pthread08_Ramirez"){
			
			printf("Porfavor espere, este programa puede tardar un poco en terminar de ejecutarse\n");

			if($lab ne "lab_pthread04_Ramirez"){
				#Acá se puede cambiar a la cantidad de veces que se desea ejecutar el laboratorio #5 al laboratorio #8 (En este caso son 1000)
				system("bash", "-c", "for i in {1..1000}; do $Path/Ejecutables/$lab; done | sort | uniq -c"); 
			} else {
				system("$Path/Ejecutables/$lab");
			}
		} else {
			system("$Path/Ejecutables/$lab");
	}
}