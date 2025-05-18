/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinámica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include <time.h>

#define TIEMPO_BASE 1000
// #include "Cola Estática/TADColaEst.h"

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

    BorrarPantalla();

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
