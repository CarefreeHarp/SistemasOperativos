#************************************************************************************
# Pontificia Universidad Javeriana                                                  *
# Fecha: 16 de Octubre del 2025                                                     *
# Autor: Daniel Felipe Ramirez Vargas                                               *
# Materia: Sistemas Operativos                                                      *
# Tema: Implementacion de productor consumidor a partir de Pipe Named               *
# Descripcion:                                                                      *
#		Se crea un directorio llamado Ejecutables donde se guardan los ejecutables  *
#		Es necesario ejecutar los programas desde dicho directorio                  *
#		Se tiene la opcion clear, para borrar el directorio y todo su contenido     *
# 																				 	*
# NOTAS IMPORTANTES: 																*
# 	#1: Se debe ejecutar PRIMERO el SERVIDOR y luego el CLIENTE ya que				*
# 		el servidor es quien crea el pipe y el cliente solo lo abre.				*
# 	#2: Solo escriba su mensaje en el cliente cuando vea el mensaje que lo indica:  *
#		"(CLIENTE) ESCRIBA AQUÍ SU MENSAJE:", de lo contrario, habrá errores de		*
#		impresión en la consola														*
#************************************************************************************/

GCC = gcc
FLAGS =
MODULO =
DIRECTORIO = Ejecutables

PROGRAMAS = cliente servidor

cliente:
	mkdir -p $(DIRECTORIO)
	$(GCC) $@.c -o $(DIRECTORIO)/$@
servidor:
	mkdir -p $(DIRECTORIO)
	rm -f /tmp/PIPE_COMUNICATOR
	$(GCC) $@.c -o $(DIRECTORIO)/$@
clear:
	$(RM) -rf $(DIRECTORIO)


