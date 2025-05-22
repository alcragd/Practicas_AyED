CC = gcc

OUT1 = Supermercado.exe
OUT2 = Sistema_Operativo.exe

FUENTE1 = Supermercado.c
FUENTE2 = Sistema_Operativo.c


COLA_DIN = './Cola Dinamica/TADColaDin.c'
COLA_EST = './Cola Estatica/TADColaEst.c'

UTILS = ./Utils/consola_utils.c

Presentacion = ./Presentacion/presentacionWin.c


all:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_DIN) $(Presentacion) $(UTILS)
	$(CC) -o $(OUT2) $(FUENTE2) $(COLA_DIN) $(Presentacion) $(UTILS)


super_din:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_DIN) $(Presentacion) $(UTILS)
super_est:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_EST) $(Presentacion) $(UTILS)


so_din:
	$(CC) -o $(OUT2) $(FUENTE2) $(COLA_DIN) $(Presentacion) $(UTILS)
so_est:
	$(CC) -o $(OUT2) $(FUENTE2) $(COLA_EST) $(Presentacion) $(UTILS)


clean:
	del /Q *.o *.exe 

