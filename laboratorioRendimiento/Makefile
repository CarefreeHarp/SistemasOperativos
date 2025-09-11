CC = gcc
DIRECTORIO = Ejecutables
MODULO = modulo


labRendiRamirez:
	mkdir Ejecutables
	$(CC) -c $(MODULO).c -o $(DIRECTORIO)/$(MODULO).o
	$(CC) $@.c $(DIRECTORIO)/$(MODULO).o -o $(DIRECTORIO)/$@
clear:
	rm -rf $(DIRECTORIO)