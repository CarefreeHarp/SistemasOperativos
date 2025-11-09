#Se crea un directorio llamado Ejecutables donde se guardan los ejecutables
#Es necesario ejecutar los programas desde dicho directorio
#Se tiene la opcion clear, para borrar el directorio y todo su contenido


GCC = gcc
DIRECTORIO = Ejecutables
#Se utiliza la flag -fopenmp para compilar archivos.c que utilizan OpenMP y tambien -lm para incluir funciones matemáticas como seno
FLAGS = -lm -fopenmp 

PROGRAMAS = labOMP01 labOMP02 labOMP03 labOMP04 labOMP05 labOMP06

#Regla que permite compilar todos los laboratorios
all: $(PROGRAMAS)

#Regla que permite compilar cada laboratorio por separado
labOMP01:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
labOMP02:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
labOMP03:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
labOMP04:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
labOMP05:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)
labOMP06:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@ $(FLAGS)

#Regla para borrar el directorio de ejecutables
clear:
	$(RM) -rf $(DIRECTORIO)
