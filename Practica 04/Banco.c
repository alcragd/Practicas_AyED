#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include "Utils/consola_utils.h"
#include <time.h>

#define TIEMPO_BASE 10 // 10ms

#define ANCHO 120 //
#define ALTO 30   // ANCHO y AlTO de la consola*
#define anchoCajero 5
#define altoCajero 4
#define DISTANCIA 2 // Distancia entre clientes

void DibujaCajero(int num, int ancho, int alto, int separacion);
void llegadaCliente(int numTipoCliente, cola *tipoCola, char tipoCliente);
void atenderCliente(cola *tipoCola, int i, int separacion, elemento *cajeros);
void limpiarCajero(int separacion, int i);
void actualizarColas(cola *tipoCola, char tipoCliente);
void cuandoCtrlC(void);

char *Emojis[] = {
	"👦",            // niño
	"👧",            // niña
	"🧑",            // persona
	"👨",            // hombre
	"👩",            // mujer
	"🧔",            // hombre con barba
	"👱‍♂️", // hombre rubio
	"👱‍♀️", // mujer rubia
	"🧓",            // persona mayor
	"👴",            // abuelo
	"👵",            // abuela
	"🧑‍🎓",   // estudiante
	"🧑‍💼",   // oficinista
	"🧑‍🔬",   // científico
	"🧑‍🍳",   // chef
	"🧑‍🚀",   // astronauta
	"🧑‍🚒",   // bombero
	"👮",            // policía
	"🕵️",            // detective
	"💂"             // guardia
};

#define NUM_EMOJIS (sizeof(Emojis) / sizeof(Emojis[0]))


int main()
{
    int numCajeros, *tiempoAtencion, tiempoCliente, tiempoUsuario, tiempoPreferente, separacionCajeros;
	elemento *cajeros;
	char tipo;
    int  i, noUsuarios = 0, tiempo = 0, numCliente = 0, numUsuario = 0, numPreferente = 0;
    cola clientes, usuarios, preferentes;
    elemento e;

    Initialize(&clientes);
    Initialize(&usuarios);
    Initialize(&preferentes);

	

    printf("\nIngrese el numero de cajeros:\n>> ");
    scanf("%d", &numCajeros);
    while (numCajeros < 1 || numCajeros > 10)
    {
        printf("\n[*]-- El numero de cajeros debe estar entre 1 y 10\n>> ");
        scanf("%d", &numCajeros);
    }

    tiempoAtencion = malloc(numCajeros * sizeof(int));
    cajeros = calloc(numCajeros, sizeof(elemento));

    for (i = 0; i < numCajeros; i++)
    {
        printf("\nIngrese el tiempo de atencion del cajero %d en milisegundos: \n>> ", i + 1);
        scanf("%d", &tiempoAtencion[i]);

        while (tiempoAtencion[i] % 10 != 0)
        {
            printf("\n[*]-- El tiempo de atencion debe ser un multiplo de 10 \n>> ");
            scanf("%d", &tiempoAtencion[i]);
        }
    }

    printf("\nIngrese el tiempo de llegada de los clientes del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoCliente);

    while (tiempoCliente % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoCliente);
    }

    printf("\nIngrese el tiempo de llegada de los usuarios del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoUsuario);

    while (tiempoUsuario % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoUsuario);
    }

    printf("\nIngrese el tiempo de llegada de los clientes preferentes del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoPreferente);

    while (tiempoPreferente % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoPreferente);
    }

	separacionCajeros = (ANCHO - anchoCajero * numCajeros) / (numCajeros + 1);

	if (separacionCajeros < 7)
	{
		separacionCajeros = 7; // Asegurar una separación minima
		printf("\n[!]-- Separación minima alcanzada, se recomienda ampliar el tamaño de la consola.");
	}

    printf("\n");
    system("pause");

	forzarUTF8();
	cacharCtrlC(cuandoCtrlC);
    BorrarPantalla();
    ocultarCursor();

	MoverCursor(1,15);
	cambiarColor(VERDE, NEGRO);
	printf("Clientes    ( C )");
	MoverCursor(1,17);
	cambiarColor(AMARILLO, NEGRO);
	printf("Preferentes ( P )");
	MoverCursor(1,19);
	cambiarColor(AZUL, NEGRO);
	printf("Usuarios    ( U )");

	MoverCursor(53,0);
	cambiarColor(VERDE, NEGRO);
	printf("Banco ");
	MoverCursor(60,0);
	cambiarColor(BLANCO, NEGRO);
	printf("de ");
	MoverCursor(63,0);
	cambiarColor(ROJO, NEGRO);
	printf("Mexico ");

	restaurarColor();

	for (i = 0; i < numCajeros; i++)
	{
		cajeros[i].i = 0;
		DibujaCajero(i, anchoCajero, altoCajero, separacionCajeros);
	}

    while(1)
    {
		EsperarMiliSeg(TIEMPO_BASE); // Esperar el tiempo base
        tiempo++;

		if(tiempo * 10 % tiempoCliente == 0)
		{
			numCliente ++;
			tipo = 'C';
			llegadaCliente(numCliente, &clientes, tipo);
		}
		if(tiempo * 10 % tiempoUsuario == 0)
		{
			numUsuario ++;
			tipo = 'U';
			llegadaCliente(numUsuario, &usuarios, tipo);
		}
		if(tiempo * 10 % tiempoPreferente == 0)
		{
			numPreferente ++;
			tipo = 'P';
			llegadaCliente(numPreferente, &preferentes, tipo);
		}

        for(i = 0; i < numCajeros; i++)
        {
			if(cajeros[i].i != 0)
			{
				if (tiempo * 10 % tiempoAtencion[i] == 0)
           		{
					limpiarCajero(separacionCajeros, i);
               		cajeros[i].i = 0;
                    //printf("Atendi a %c%d en la caja %d \n",e.tipo,e.i,i+1); No se como hacer para que sea el elemento que toca xd
           		}
			}
			else
            {
                if(noUsuarios >= 5 && !Empty(&usuarios))
                {
                    noUsuarios = 0;
                	atenderCliente(&usuarios, i, separacionCajeros, cajeros);
					tipo = 'U';
					actualizarColas(&usuarios, tipo);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&preferentes))
                {
                    noUsuarios++;
                	atenderCliente(&preferentes, i, separacionCajeros, cajeros);
					tipo = 'P';
					actualizarColas(&preferentes, tipo);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&clientes))
                {
                    noUsuarios++;
					atenderCliente(&clientes, i, separacionCajeros, cajeros);
					tipo = 'C';
					actualizarColas(&clientes, tipo);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
				if(!Empty(&usuarios))
				{
                    noUsuarios = 0;
					atenderCliente(&usuarios, i, separacionCajeros, cajeros);
					tipo = 'U';
					actualizarColas(&usuarios, tipo);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
				}
            }
        }
    }
    Destroy(&usuarios);
    Destroy(&clientes);
    Destroy(&preferentes);
    return 0;
}


void DibujaCajero(int num, int ancho, int alto, int separacion)
{
	int columna, fila, i, n = 3, divisor, mov = 1, posX;
	columna = separacion + num * (ancho + separacion);

	MoverCursor(columna, 2);
	printf("Cajero %d", num + 1);
	for (fila = 4; fila < alto + 3; fila++)
	{
		MoverCursor(columna, fila);
		printf("|");
		MoverCursor(columna + ancho, fila);
		printf("|");
	}
	for (i = 1; i < ancho; columna++, i++)
	{
		MoverCursor(columna + 1, 3);
		printf("_");
		MoverCursor(columna + 1, fila - 1);
		printf("_");
	}

	MoverCursor(columna - (ancho / 2), 5);
	printf("👤");

	while(n--)
	{
		if(n == 2)
		{
			divisor = 4;
		}
		else if(n == 1)
		{
			divisor = 2;
		}
		else
		{
			mov = 3;
			divisor = 4;
		}

		posX = ANCHO / divisor * mov - 3;
		for (fila = 13; fila < 27; fila++)
		{
			MoverCursor(posX - 1, fila);
			printf("|");
			MoverCursor(posX + 7, fila);
			printf("|");
		}
	}
	
}

void llegadaCliente(int numTipoCliente, cola *tipoCola, char tipoCliente)
{
	int posX, posY, emoji_indice, mov = 1, divisor;
	elemento e;

	if(tipoCliente == 'C')
	{
		divisor = 4;
	}
	else if(tipoCliente == 'P')
	{
		divisor = 2;
	}
	else
	{
		mov = 3;
		divisor = 4;
	}

	posX = ANCHO / divisor * mov - 3;
	emoji_indice = rand() % NUM_EMOJIS;

	e.i = numTipoCliente;
	e.tipo=tipoCliente;
	e.emoji = emoji_indice;

	Queue(tipoCola, e);

	// Calcula la posición vertical según la cantidad de usuarios en la cola
	if (Size(tipoCola) < 7)
	{
		posY = 11 + (Size(tipoCola) * DISTANCIA);
		MoverCursor(posX, posY);
		printf("%s%c%d", Emojis[emoji_indice], tipoCliente, numTipoCliente);
	}
	else
	{
		posY = 11 + 7 * DISTANCIA;
		MoverCursor(posX, posY);
		cambiarColor(GRIS_CLARO, NEGRO);
		printf("+%d", Size(tipoCola) - 6);
		restaurarColor();
	}
}

void atenderCliente(cola *tipoCola, int i, int separacion, elemento *cajeros)
{
	int posX, posY = 7;
	elemento e;

	posX = separacion + i * (anchoCajero + separacion);

	e = Dequeue(tipoCola);
	cajeros[i] = e;

	MoverCursor(posX, posY);
	printf("%s%c%d", Emojis[e.emoji], e.tipo, e.i);
}

void limpiarCajero(int separacion, int i)
{
	int posX, posY = 7;

	posX = separacion + i * (anchoCajero + separacion);

    MoverCursor(posX, posY);
    printf("      ");
}

void actualizarColas(cola *tipoCola, char tipoCliente)
{
	int posX, posY, emoji_indice, mov = 1, divisor, i;

	if(tipoCliente == 'C')
	{
		divisor = 4;
	}
	else if(tipoCliente == 'P')
	{
		divisor = 2;
	}
	else
	{
		mov = 3;
		divisor = 4;
	}

	posX = ANCHO / divisor * mov - 3;

    // Limpiar la cola de clientes
    for (i = 0; i < 9; i++)
    {
        MoverCursor(posX, 13 + i * DISTANCIA);
        printf("      ");
    }

	for (i = 1; i <= Size(tipoCola); i++)
	{
		if (i < 7)
		{
			posY = 11 + (i* DISTANCIA);
			MoverCursor(posX, posY);
			printf("%s%c%d", Emojis[Element(tipoCola, i).emoji],  tipoCliente, Element(tipoCola, i).i);
		}
		else
		{
			posY = 11 + 7 * DISTANCIA;
			MoverCursor(posX, posY);
			cambiarColor(GRIS_CLARO, NEGRO);
			printf("+%d", Size(tipoCola) - 6);
			restaurarColor();
		}
	}
	
}

void cuandoCtrlC(void)
{

    restaurarColor();
    mostrarCursor();
    MoverCursor(0, ALTO - 2);

    exit(0);
}