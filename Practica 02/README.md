## COMPILACIÓN:

gcc -o Relleno.exe RellenoConColor.c BMP.o pila_din.o

### Cada que que se haga un cambio en pila_din.c o BMP.c volver a compilar los codigos objeto (.o) antes de compilar RellenoConColor.c

gcc -c .\pila_dinamica\pila_din.c

gcc -c .\BMP\BMP.c
