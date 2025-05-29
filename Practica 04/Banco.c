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
void llegadaCliente(int numCliente, cola *clientes);
void llegadaPreferente(int numPreferente, cola *preferentes);
void llegadaUsuario(int numUsuario, cola *usuarios);
void atenderCliente(cola *tipoCola, int i, int separacion, elemento *cajeros);

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

    BorrarPantalla();
    ocultarCursor();

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
			llegadaCliente(numCliente, &clientes);
		}
		if(tiempo * 10 % tiempoUsuario == 0)
		{
			numUsuario ++;
			llegadaUsuario(numUsuario, &usuarios);
		}
		if(tiempo * 10 % tiempoPreferente == 0)
		{
			numPreferente ++;
			llegadaPreferente(numPreferente, &preferentes);
		}

        for(i = 0; i < numCajeros; i++)
        {
			if(cajeros[i].i != 0)
			{
				if (tiempo * 10 % tiempoAtencion[i] == 0)
           		{
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
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&preferentes))
                {
                    noUsuarios++;
                	atenderCliente(&preferentes, i, separacionCajeros, cajeros);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&clientes))
                {
                    noUsuarios++;
					atenderCliente(&clientes, i, separacionCajeros, cajeros);
                    //printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
				if(!Empty(&usuarios))
				{
                    noUsuarios = 0;
					atenderCliente(&usuarios, i, separacionCajeros, cajeros);
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
	int columna, fila, i;
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
}

void llegadaCliente(int numCliente, cola *clientes)
{
	int posX, posY, emoji_indice;
	elemento e;

	posX = ANCHO / 4 - 3;
	emoji_indice = rand() % NUM_EMOJIS;

	e.i = numCliente;
	e.tipo='C';
	e.emoji = emoji_indice;

	Queue(clientes, e);

	// Calcula la posición vertical según la cantidad de clientes en la cola
	if (Size(clientes) < 7)
	{
		posY = 11 + (Size(clientes) * DISTANCIA);
		MoverCursor(posX, posY);
		printf("%sC%d", Emojis[emoji_indice], numCliente);
	}
	else
	{
		posY = 11 + 7 * DISTANCIA;
		MoverCursor(posX, posY);
		cambiarColor(GRIS_CLARO, NEGRO);
		printf("+%d", Size(clientes) - 6);
		restaurarColor();
	}
}

void llegadaPreferente(int numPreferente, cola *preferentes)
{
	int posX, posY, emoji_indice;
	elemento e;

	posX = ANCHO / 2 - 3;
	emoji_indice = rand() % NUM_EMOJIS;

	e.i = numPreferente;
	e.tipo='P';
	e.emoji = emoji_indice;

	Queue(preferentes, e);

	// Calcula la posición vertical según la cantidad de preferentes en la cola
	if (Size(preferentes) < 7)
	{
		posY = 11 + (Size(preferentes) * DISTANCIA);
		MoverCursor(posX, posY);
		printf("%sP%d", Emojis[emoji_indice], numPreferente);
	}
	else
	{
		posY = 11 + 7 * DISTANCIA;
		MoverCursor(posX, posY);
		cambiarColor(GRIS_CLARO, NEGRO);
		printf("+%d", Size(preferentes) - 6);
		restaurarColor();
	}
}

void llegadaUsuario(int numUsuario, cola *usuarios)
{
	int posX, posY, emoji_indice;
	elemento e;

	posX = ANCHO / 4 * 3 - 3;
	emoji_indice = rand() % NUM_EMOJIS;

	e.i = numUsuario;
	e.tipo='U';
	e.emoji = emoji_indice;

	Queue(usuarios, e);

	// Calcula la posición vertical según la cantidad de usuarios en la cola
	if (Size(usuarios) < 7)
	{
		posY = 11 + (Size(usuarios) * DISTANCIA);
		MoverCursor(posX, posY);
		printf("%sU%d", Emojis[emoji_indice], numUsuario);
	}
	else
	{
		posY = 11 + 7 * DISTANCIA;
		MoverCursor(posX, posY);
		cambiarColor(GRIS_CLARO, NEGRO);
		printf("+%d", Size(usuarios) - 6);
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