CC = gcc

OUT = diccionario.exe
SRC = diccionario.c 

lib_TablaHash = "Tabla Hash/TablaHash.c"
lib_TADLista = "Tabla Hash/TAD Lista DL/TADListaDL.c"

all:
	$(CC) -o $(OUT) $(SRC) $(lib_TablaHash) $(lib_TADLista)
clean: 
	del /Q *.exe *.out