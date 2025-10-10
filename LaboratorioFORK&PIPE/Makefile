#Se crea un directorio llamado Ejecutables donde se guardan los ejecutables
#Es necesario ejecutar los programas desde dicho directorio
#Se tiene la opcion clear, para borrar el directorio y todo su contenido

GCC = gcc
PROGRAMAS = lab01_Ramirez lab02_Ramirez lab03_Ramirez
DIRECTORIO = Ejecutables

lab01_Ramirez:
	mkdir -p Ejecutables
	$(GCC) $@.c -o $(DIRECTORIO)/$@
lab02_Ramirez:
	mkdir -p Ejecutables
	$(GCC) $@.c -o $(DIRECTORIO)/$@
lab03_Ramirez:
	mkdir -p Ejecutables
	$(GCC) $@.c -o $(DIRECTORIO)/$@
clear:
	$(RM) -rf $(DIRECTORIO)
