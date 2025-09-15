#Este makefile compila el programa labRendiRamirez.c y el modulo modulo.c
#Crea un directorio donde se guardaran los ejecutables y los objetos,
#en dicho directorio, se guardan los archivos compilados como el ejecutable y el objeto

#Existe tambien la opcion de clear, para borrar dicha carpeta y todo su contenido
#Es ¡¡¡¡IMPORTANTE!!!! aclarar que se debe utilizar el comando make clear antes de volver a compilar

#Una vez ejecutado el comando make labRendiRamirez para compilar, se debe entrar a la carpeta
#Ejecutables y alli ejecutar el programa con el comando ./labRendiRamirez <N>
#donde N es la dimension de las matrices a multiplicar

CC = gcc
DIRECTORIO = Ejecutables
MODULO = modulo


labRendiRamirez:
	mkdir Ejecutables 
	$(CC) -c $(MODULO).c -o $(DIRECTORIO)/$(MODULO).o
	$(CC) $@.c $(DIRECTORIO)/$(MODULO).o -o $(DIRECTORIO)/$@
clear:
	rm -rf $(DIRECTORIO)