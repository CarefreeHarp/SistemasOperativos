#*******************************************************************
# Pontificia Universidad Javeriana
# Facultad de Ingeniería
# Carrera: Ingeniería de Sistemas
# Autores: Guillermo Aponte, Daniel Ramírez
# Materia: Sistemas Operativos
# Tema: Makefile 
# Archivo: Makefile
# Descripcion: Automatiza la compilación modular de varios ficheros 
#			   Teniendo en cuenta la estructura de directorios,
#			   es decir, directorios de modulos y de ficheros main
# Fecha: 14/11/25
#*******************************************************************


# Compilador
GCC = gcc

# Flags de compilación
FLAGS = -pthread -lrt

# Archivos
MAIN = concurrenciaPOsix
MODULO = moduloConcurrenciaPosix
EJECUTABLE = programaPosix

# Carpeta donde se guardarán los ejecutables y objetos
EJECUTABLES = Ejecutables

# Regla principal
all: $(EJECUTABLE)

# Compila el programa principal con el módulo
$(EJECUTABLE): $(MAIN).c $(EJECUTABLES)/$(MODULO).o
	mkdir -p $(EJECUTABLES)
	$(GCC) $(MAIN).c $(EJECUTABLES)/$(MODULO).o -o $(EJECUTABLES)/$(EJECUTABLE) $(FLAGS)

# Compila el módulo a archivo objeto
$(EJECUTABLES)/$(MODULO).o: $(MODULO).c $(MODULO).h
	mkdir -p $(EJECUTABLES)
	$(GCC) -c $(MODULO).c -o $(EJECUTABLES)/$(MODULO).o

# Limpieza
clean:
	rm -rf $(EJECUTABLES)
