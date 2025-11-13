#NOTA: DESPUES DE COMPILAR, ES NECESARIO ACCEDER AL DIRECTORIO "Ejecutables" (cd Ejecutables)
#	   Para ejecutar desde allí los programas
#      En el caso del lab02 y lab03, se requiere escribir almenos ../ ya que
#      el directorio Ejecutables no lleva estructura de directorios por dentro

GCC = gcc

EJECUTABLES = Ejecutables

PROGRAMAS = lab01 lab02 lab03

all: $(PROGRAMAS)

lab01:
	mkdir -p $(EJECUTABLES)
	$(GCC) $@.c -o $(EJECUTABLES)/$@
lab02:
	mkdir -p $(EJECUTABLES)
	$(GCC) $@.c -o $(EJECUTABLES)/$@
lab03:
	mkdir -p $(EJECUTABLES)
	$(GCC) $@.c -o $(EJECUTABLES)/$@
clean:
	rm -rf $(EJECUTABLES)
