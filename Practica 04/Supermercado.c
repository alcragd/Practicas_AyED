/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinámica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include <time.h>

#define TIEMPO_BASE 1000

#define ANCHO 120 //
#define ALTO 30   // ANCHO y AlTO de la consola*

// #include "Cola Estática/TADColaEst.h"

void PintadoInicial(int cantCajas);
void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion);

int main()
{
    char nombreSuper[50];
    int numCajas, i, clientes = 0, tiempo = 0, clientesAtendidos = 0;
    int caja;
    int *tiempoAtencion;
    int tiempoLlegada;

    cola *cajas;
    int repetir = 1;
    elemento e;

    srand(time(NULL));

    printf("Ingrese el nombre del supermercado: ");
    scanf("%s", nombreSuper);
    printf("\nIngrese el numero de cajas: ");
    scanf("%d", &numCajas);
    if (numCajas < 1 || numCajas > 10)
    {
        printf("\nError: El numero de cajas debe ser entre 1 y 10");
        exit(1);
    }

    PintadoInicial(numCajas);
    MoverCursor(1, 26);
    system("pause");

    tiempoAtencion = malloc(numCajas * sizeof(int));
    cajas = malloc(numCajas * sizeof(cola));
    if (tiempoAtencion == NULL || cajas == NULL)
    {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    for (i = 0; i < numCajas; i++)
    {
        printf("\n Ingrese el tiempo de atencion de la caja %d en milisegundos: ", i + 1);
        scanf("%d", &tiempoAtencion[i]);
        Initialize(&cajas[i]);
    }
    printf("\nIngrese el tiempo de llegada de los clientes en milisegundos: ");
    scanf("%d", &tiempoLlegada);

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
                    e = Dequeue(&cajas[i]);
                    clientesAtendidos++;
                    printf("\n\nAtendi a: %d en caja %d", e.i, i + 1);
                }
                else
                {
                    printf("\n\nNo hay alguien por atender en caja %d", i + 1);
                }
            }
        }
        if (tiempo * 10 % tiempoLlegada == 0)
        {
            clientes++;
            e.i = clientes;
            caja = rand() % numCajas;
            Queue(&cajas[caja], e);
            printf("\n\nLlego el cliente: %d a la cola de la caja %d", e.i, caja + 1);
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
    printf("\n\n\nClientes atendidos: %d", clientesAtendidos);
    printf("\nTienda %s cerrada", nombreSuper);
    free(tiempoAtencion);
    free(cajas);
    return 0;
}

void PintadoInicial(int cantCajas)
{
    int i, separacion;
    int anchoCaja, altoCaja;

    anchoCaja = 5;
    altoCaja = 8;

    BorrarPantalla();
    separacion = (ANCHO - anchoCaja * cantCajas) / (cantCajas + 1);
    for (i = 1; i <= cantCajas; i++)
        DibujaCaja(i, i, anchoCaja, altoCaja, separacion);
}

void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion)
{
    int columna, fila, i;
    columna = num * (ancho + separacion);

    for (i = 0; i < ancho; columna++, i++)
    {
        for (fila = 1; fila < alto; fila++)
        {
            MoverCursor(columna, fila);
            printf("*");
        }
    }

    MoverCursor(num * (ancho + separacion) + (ancho / 2) - 2 + (ancho % 2), 2);
    printf("A:%d", cliente);
}