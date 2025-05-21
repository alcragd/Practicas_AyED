/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include <time.h>

#define TIEMPO_BASE 1000

#define ANCHO 120 //
#define ALTO 30   // ANCHO y AlTO de la consola*
#define anchoCaja 6
#define altoCaja 8
#define DISTANCIA 2 // Distancia entre clientes

// #include "Cola Estática/TADColaEst.h"


void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion);
void AtenderCliente(cola *c, int numcola, int separacion);
void LlegadaCliente(int numcliente, int numcola, cola *c, int separacion);

int main()
{
    char nombreSuper[50];
    int numCajas, i, clientes = 0, tiempo = 0, clientesAtendidos = 0;
    int caja, separacionCajas;
    int *tiempoAtencion;
    int tiempoLlegada;

    cola *cajas;
    int repetir = 1;
    elemento e;

    srand(time(NULL));

    BorrarPantalla();

    printf("Ingrese el nombre del supermercado: ");
    scanf("%s", nombreSuper);
    printf("\nIngrese el numero de cajas: ");
    scanf("%d", &numCajas);
    if (numCajas < 1 || numCajas > 10)
    {
        printf("\nError: El numero de cajas debe ser entre 1 y 10");
        exit(1);
    }

    tiempoAtencion = malloc(numCajas * sizeof(int));
    cajas = malloc(numCajas * sizeof(cola));
    if (tiempoAtencion == NULL || cajas == NULL)
    {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    for (i = 0; i < numCajas; i++)
    {
        printf("\nIngrese el tiempo de atencion de la caja %d en milisegundos: ", i + 1);
        scanf("%d", &tiempoAtencion[i]);
        if (tiempoAtencion[i] % 10 != 0)
        {
            printf("\nError: El tiempo de atencion debe ser un multiplo de 10");
            exit(1);
        }
        Initialize(&cajas[i]);
    }
    printf("\nIngrese el tiempo de llegada de los clientes en milisegundos: ");
    scanf("%d", &tiempoLlegada);
    if (tiempoLlegada % 10 != 0)
    {
        printf("\nError: El tiempo de llegada debe ser un multiplo de 10");
        exit(1);
    }

    separacionCajas = (ANCHO - anchoCaja * numCajas) / (numCajas + 1);

    if (separacionCajas < 6)
    {
        separacionCajas = 6; // Asegurar una separación minima
        printf("\n[!]-- Separación minima alcanzada, se recomienda ampliar el tamaño de la consola.");
    }

    printf("\n");
    system("pause");

    BorrarPantalla();
    MoverCursor((ANCHO - strlen(nombreSuper) - 12) / 2, 0);
    printf("Supermercado %s", nombreSuper);
    // Espacio entre cajas
    for (i = 1; i <= numCajas; i++)
        DibujaCaja(i, i, anchoCaja, altoCaja, separacionCajas);
    MoverCursor(1, 26);

    while (repetir)
    {
        EsperarMiliSeg(TIEMPO_BASE); // Esperar el tiempo base
        tiempo++;                    // Incrementar el contador de tiempo
        for (i = 0; i < numCajas; i++)
        {
            if (tiempo * 10 % tiempoAtencion[i] == 0)
            {
                if (!Empty(&cajas[i]))
                {
                    clientesAtendidos++;
                    AtenderCliente(&cajas[i], i, separacionCajas);
                    // e = Dequeue(&cajas[i]);
                    // printf("\n\nAtendi a: %d en caja %d", e.i, i + 1);
                }
                // else
                // {
                //     // printf("\n\nNo hay alguien por atender en caja %d", i + 1);
                // }
            }
        }
        if (tiempo * 10 % tiempoLlegada == 0)
        {
            clientes++;
            if (clientes == 9999)
                break;
            // e.i = clientes;
            caja = rand() % numCajas;

            LlegadaCliente(clientes, caja, &cajas[caja], separacionCajas);
            // Queue(&cajas[caja], e);
            // printf("\n\nLlego el cliente: %d a la cola de la caja %d", e.i, caja + 1);
        }

        if (clientesAtendidos > 20)
        {
            repetir = 0;
            for (i = 0; i < numCajas; i++)
            {
                if (!Empty(&cajas[i]))
                {
                    repetir = 1;
                }
            }
        }
    }
    MoverCursor(0, ALTO);
    printf("\n\n\nClientes atendidos: %d", clientesAtendidos);
    printf("\nTienda %s cerrada", nombreSuper);
    free(tiempoAtencion);
    free(cajas);
    return 0;
}

void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion)
{
    int columna, fila, i;
    columna = separacion + (num - 1) * (ancho + separacion);

    MoverCursor(columna, 2);
    printf("Caja %d", num);
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

    // MoverCursor(columna + ancho / 2 - 1, 7);
    // printf("C%d", cliente);
}

void LlegadaCliente(int numcliente, int numcola, cola *c, int separacion)
{
    int columna, posX, posY;
    elemento e;

    columna = separacion + (numcola) * (anchoCaja + separacion);
    posX = columna + anchoCaja + 1;
    // Calcula la posición vertical según la cantidad de clientes en la cola
    if (Size(c) < 7)
    {
        if (Empty(c))
            posY = 7;
        else if (Size(c) == 1)
            posY = 7 + 4;
        else
            posY = 9 + (Size(c) * DISTANCIA);
        MoverCursor(posX, posY);
        printf("C%d", numcliente);
    }
    else
    {
        posY = 9 + 7 * DISTANCIA;
        MoverCursor(posX, posY);
        printf("+%d", Size(c) - 6);
    }

    e.i = numcliente;
    Queue(c, e);
}

void AtenderCliente(cola *c, int numcola, int separacion)
{
    int columna, posX, posY, i;
    columna = separacion + (numcola) * (anchoCaja + separacion);
    posX = columna + anchoCaja + 1;
    Dequeue(c);

    // Limpiar la cola de clientes
    for (i = 0; i < 9; i++)
    {
        MoverCursor(posX, 7 + i * DISTANCIA);
        printf("     ");
    }

    // Dibujar los clientes restantes en la cola
    for (i = 1; i <= Size(c); i++)
    {
        if (i <= 7)
        {
            if (i == 1)
                posY = 7;
            else if (i == 2)
                posY = 7 + 4;
            else
                posY = 9 + (i - 1) * DISTANCIA;

            MoverCursor(posX, posY);
            printf("C%d", Element(c, i).i);
        }

        else
        {
            posY = 9 + 7 * DISTANCIA;
            MoverCursor(posX, posY);
            printf("+%d", Size(c) - 6);
            break;
        }
    }
}