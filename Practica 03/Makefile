CC = gcc
OUT = EvalInfijas.exe
OBJ = EvalInfijas.c 
LIB_DIN = ./pila_dinamica/pila_din.c
LIB_EST = ./pila_estatica/pila_est.c

all:
	$(CC) -o $(OUT) $(OBJ) $(LIB_DIN)
din:
	$(CC) -o $(OUT) $(OBJ) $(LIB_DIN)
est:
	$(CC) -o $(OUT) $(OBJ) $(LIB_EST)
clean:
	del /Q *.o *.exe 