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
