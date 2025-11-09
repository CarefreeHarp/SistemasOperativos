#************************************************************************************
# Pontificia Universidad Javeriana                                                  *
# Fecha:
# Autores: Daniel Felipe Ramirez Vargas - Guillermo Andrés Aponte Cárdenas          *
# Materia: Sistemas Operativos                                                      *
# Descripción: 
#************************************************************************************/

GCC = gcc
FLAGS = -lpthread #Se necesita para utilizar la biblioteca pthread
EJECUTABLES = Ejecutables#Crea un directorio de ejecutables donde se guardarán ordenadamente 
DIRECTORIOMODULOS = ModulosDeImplementacion#Directorio donde estan los modulos de implementacion

MODULOAGENTE = ModuloAgente
MODULOCONTROLADOR = ModuloControlador

PROGRAMAS = AgenteDeReservas ControladorDeReservas


all: $(PROGRAMAS)

AgenteDeReservas:
	mkdir -p $(EJECUTABLES)
	#Cada vez que se compile, borraremos el fichero del pipe que creamos para que no haya errores
	#rm -f /tmp/PIPE_COMUNICATOR

	$(GCC) -c $(DIRECTORIOMODULOS)/$(MODULOAGENTE).c -o $(EJECUTABLES)/$(MODULOAGENTE).o
	$(GCC) $@.c $(EJECUTABLES)/$(MODULOAGENTE).o -o $(EJECUTABLES)/$@ $(FLAGS)
ControladorDeReservas:
	mkdir -p $(EJECUTABLES)
	#Cada vez que se compile, borraremos el fichero del pipe que creamos para que no haya errores
	#rm -f /tmp/PIPE_COMUNICATOR 

	$(GCC) -c $(DIRECTORIOMODULOS)/$(MODULOCONTROLADOR).c -o $(EJECUTABLES)/$(MODULOCONTROLADOR).o
	$(GCC) $@.c $(EJECUTABLES)/$(MODULOAGENTE).o -o $(EJECUTABLES)/$@ $(FLAGS)

clear:
	$(RM) -rf $(EJECUTABLES)

