CC = gcc

OUT1 = Supermercado.exe
OUT2 = Sistema_Operativo.exe

FUENTE1 = Supermercado.c
FUENTE2 = Sistema_Operativo.c


COLA_DIN = '.\Cola Dinamica\TADColaDin.c'
COLA_EST = '.\Cola Estatica\TADColaEst.c'

Presentacion = ./Presentacion/presentacionWin.c


all:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_DIN) $(Presentacion)
	$(CC) -o $(OUT2) $(FUENTE2) $(COLA_DIN) $(Presentacion)


super_din:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_DIN) $(Presentacion)
super_est:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_EST) $(Presentacion)


so_din:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_DIN) $(Presentacion)
so_est:
	$(CC) -o $(OUT1) $(FUENTE1) $(COLA_EST) $(Presentacion)


clean:
	del /Q *.o *.exe 

