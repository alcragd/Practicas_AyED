#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include "Utils/consola_utils.h"

#define ANCHO 120
#define ALTO 30

#define altoCaja 12
#define anchoCaja 80

#define altoFaltantes 3
#define anchoFaltantes 17

void DibujarCaja(int x, int y, int ancho, int alto, char *texto);
void TextoCajaContador(int x, int y, int ancho, int alto, char *texto);


int main()
{
    cola porEjecutar, Ejecutando, Finalizados;
    int i, j, cantProcesos, tiempoEjecutar, tiempoTotal=0, InicioCajaX, InicioCajaY;
    char NombreProceso[45], actividad[200], ID[45], tiempoStr[32];
    elemento e;
    Initialize(&porEjecutar);
    Initialize(&Ejecutando);
    Initialize(&Finalizados);
    printf("Ingrese la cantidad de procesos a ejecutar: ");
    scanf("%d", &cantProcesos);
    getchar();
    for (i = 0; i < cantProcesos; i++)
    {
        printf("Ingrese el nombre del proceso %d: ", i + 1);
        fgets(NombreProceso, sizeof(NombreProceso), stdin);
        NombreProceso[strcspn(NombreProceso, "\n")] = 0; // Elimina el salto de línea

        printf("Ingrese su actividad a realizar: ");
        fgets(actividad, sizeof(actividad), stdin);
        actividad[strcspn(actividad, "\n")] = 0; // Elimina el salto de línea

        printf("Ingrese el ID del proceso %d: ", i + 1);
        fgets(ID, sizeof(ID), stdin);
        ID[strcspn(ID, "\n")] = 0; // Elimina el salto de línea

        printf("Ingrese el tiempo de ejecucion del proceso %d: ", i + 1);
        scanf("%d", &tiempoEjecutar);
        getchar();

        e.tiempoEjecucion = tiempoEjecutar;
        strcpy(e.nombre, NombreProceso);
        strcpy(e.actividad, actividad);
        strcpy(e.ID, ID);
        e.tiempoTotal = 0;

        Queue(&porEjecutar, e);
    }

    system("pause");
    BorrarPantalla();
    InicioCajaX = (ANCHO- anchoCaja) / 2 + 10;
    InicioCajaY = (ALTO - altoCaja) / 2 -5;

    DibujarCaja(2, 1, anchoFaltantes, 3, "Faltantes: 0");
    DibujarCaja(2, 12, anchoFaltantes, 3, "Tiempo: 0");
    DibujarCaja(2, 24, anchoFaltantes + 3, 3, "Terminados: 0");
    DibujarCaja(InicioCajaX, InicioCajaY - 4, anchoCaja, 3, "Anterior: ID SAMPLE 1");
    DibujarCaja(InicioCajaX, InicioCajaY, anchoCaja, altoCaja, "");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, "Siguiente: ID SAMPLE 1");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 6, anchoCaja, 5, "Ultimo Finalizado: Nombre/ID");
    MoverCursor(0, 29);
    while (!Empty(&porEjecutar))
    {
        Sleep(1000);
        tiempoTotal++;
        sprintf(tiempoStr, "Tiempo: %d", tiempoTotal);
        TextoCajaContador(2, 12, anchoFaltantes, 3, tiempoStr);
        e = Dequeue(&porEjecutar);
        if (e.tiempoEjecucion == 0)
        {
            e.tiempoTotal=tiempoTotal;
            Queue(&Finalizados, e);
            int tamFinalizados= Size(&Finalizados);
            char FinStr[32];
            sprintf(FinStr, "Terminados: %d", tamFinalizados);
            TextoCajaContador(2, 24, anchoFaltantes + 3, 3, FinStr);
            //printf("Proceso finalizado: %s\n", e.nombre);
        }
        else
        {
            e.tiempoTotal=tiempoTotal;
            Queue(&Ejecutando, e);
            // printf("\nEjecutando el proceso: %s\n", e.nombre);
            // printf("Actividad: %s\n", e.actividad);
            // printf("ID: %s\n", e.ID);
            // printf("Tiempo de ejecucion: %d\n", e.tiempoEjecucion);
            // printf("Tiempo total: %d\n", e.tiempoTotal);
           

            e = Dequeue(&Ejecutando);
            e.tiempoEjecucion--;
            Queue(&porEjecutar, e);
        }
        int tamfaltantes= Size(&porEjecutar)+Size(&Ejecutando);
        char FsltsntesStr[32];
        sprintf(FsltsntesStr, "Faltantes: %d", tamfaltantes);
        TextoCajaContador(2, 1, anchoFaltantes, 3, FsltsntesStr);
    }
/*
    printf("Los procesos finalizados son:\n");
    while (!Empty(&Finalizados))
    {
        e = Dequeue(&Finalizados);
        printf("Proceso finalizado:\n");
        printf("Nombre: %s\n", e.nombre);
        printf("Actividad: %s\n", e.actividad);
        printf("ID: %s\n", e.ID);
        printf("Tiempo total: %d\n\n", e.tiempoTotal);
    }

    Destroy(&porEjecutar);
    Destroy(&Ejecutando);
    Destroy(&Finalizados);
    return 0;
    */
   MoverCursor(1,29);
}

void DibujarCaja(int x, int y, int ancho, int alto, char *texto)
{
    int i, j;

    for (i = 0; i < ancho - 1; i++)
    {
        MoverCursor(x + i + 1, y);
        printf("_");
        MoverCursor(x + i + 1, y + alto);
        printf("_");
    }

    for (j = 0; j < alto; j++)
    {
        MoverCursor(x, y + j + 1);
        printf("|");
        MoverCursor(x + ancho, y + j + 1);
        printf("|");
    }

    int tituloLen = strlen(texto);
    int offsetTituloX = (ancho - tituloLen) / 2;
    int offsetTituloY = alto / 2 + 1;

    if (tituloLen > 0 && ancho > tituloLen)
    {
        MoverCursor(x + offsetTituloX + 1, y + offsetTituloY);
        printf("%s", texto);
    }
    
}
void TextoCajaContador(int x, int y, int ancho, int alto, char *texto)
{
    int tituloLen = strlen(texto);
    int offsetTituloX = (ancho - tituloLen) / 2;
    int offsetTituloY = alto / 2 + 1;

    if (tituloLen > 0 && ancho > tituloLen)
    {
        MoverCursor(x + offsetTituloX + 1, y + offsetTituloY);
        printf("%s", texto);
    }
}

