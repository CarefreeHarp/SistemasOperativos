#************************************************************************************
# Pontificia Universidad Javeriana                                                  *
# Fecha: 6 de Noviembre del 2025                                                    *
# Autor: Daniel Felipe Ramirez Vargas                                               *
# Materia: Sistemas Operativos                                                      *
# Tema: Compilación con Makefile            										*
# Descripcion: Fichero que permite automatizar la compilación de todos los 			*
#			   laboratorios sobre hilos												*
#************************************************************************************/

GCC = gcc
FLAGS = -lpthread #Se necesita para utilizar la biblioteca pthread
DIRECTORIO = Ejecutables#Crea un directorio de ejecutables donde se guardarán ordenadamente 

PROGRAMAS = lab_pthread00_Ramirez lab_pthread01_Ramirez lab_pthread02_Ramirez lab_pthread03_Ramirez lab_pthread04_Ramirez lab_pthread05_Ramirez lab_pthread06_Ramirez lab_pthread07_Ramirez lab_pthread08_Ramirez

all: $(PROGRAMAS)

lab_pthread00_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread01_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread02_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread03_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread04_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread05_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread06_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread07_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
lab_pthread08_Ramirez:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
clear:
	$(RM) -rf $(DIRECTORIO)

