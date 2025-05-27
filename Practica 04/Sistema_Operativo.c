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

#define altoMiniCajas 3
#define anchoMiniCajas 17

#define MAX_LINEA_ACTIVIDAD 70

void DibujarCaja(int x, int y, int ancho, int alto, char *texto);
void UpdateTextoCaja(int x, int y, int ancho, int alto, char *texto);
void UpdateCajaPrincipal(int x, int y, elemento e);
void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas);


int main()
{
    cola porEjecutar, Ejecutando, Finalizados;
    int i, j, cantProcesos, tiempoEjecutar, tiempoTotal = 0, InicioCajaX, InicioCajaY, tamFinalizados, tamfaltantes;
    char NombreProceso[45], actividad[200], ID[45], tiempoStr[32], FinStr[32], FaltantesStr[32], UltFin[32], Ant[32], Sig[32];
    elemento e, e_ant, e_sig;
    Initialize(&porEjecutar);
    Initialize(&Ejecutando);
    Initialize(&Finalizados);
    printf("Ingrese la cantidad de procesos a ejecutar: ");
    scanf("%d", &cantProcesos);
    getchar();
    for (i = 0; i < cantProcesos; i++)
    {
        printf("Ingrese el ID del proceso %d: ", i + 1);
        fgets(ID, sizeof(ID), stdin);
        ID[strcspn(ID, "\n")] = 0; // Elimina el salto de línea

        printf("Ingrese el nombre del proceso %d: ", i + 1);
        fgets(NombreProceso, sizeof(NombreProceso), stdin);
        NombreProceso[strcspn(NombreProceso, "\n")] = 0; // Elimina el salto de línea

        printf("Ingrese su actividad a realizar: ");
        fgets(actividad, sizeof(actividad), stdin);
        actividad[strcspn(actividad, "\n")] = 0; // Elimina el salto de línea

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

    ocultarCursor();
    forzarUTF8();
    BorrarPantalla();
    InicioCajaX = (ANCHO - anchoCaja) / 2 + 10;
    InicioCajaY = (ALTO - altoCaja) / 2 - 5;

    DibujarCaja(2, 1, anchoMiniCajas, 3, "Faltantes: 0");
    DibujarCaja(2, 12, anchoMiniCajas, 3, "Tiempo: 0");
    DibujarCaja(2, 24, anchoMiniCajas + 3, 3, "Terminados: 0");
    DibujarCaja(InicioCajaX, InicioCajaY - 4, anchoCaja, 3, "Anterior: ");
    DibujarCaja(InicioCajaX, InicioCajaY, anchoCaja, altoCaja, "");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, "Siguiente: ");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 6, anchoCaja, 5, "Ultimo Finalizado:");
    MoverCursor(0, 29);
    while (!Empty(&porEjecutar))
    {
        Sleep(1000);
        tiempoTotal++;
        sprintf(tiempoStr, "Tiempo: %d", tiempoTotal);
        UpdateTextoCaja(2, 12, anchoMiniCajas, 3, tiempoStr);
        e = Dequeue(&porEjecutar);
        e.tiempoEjecucion--;
        e.tiempoTotal = tiempoTotal;

        UpdateCajaPrincipal(InicioCajaX,InicioCajaY,e);

        if(!Empty(&porEjecutar))
        {
            e_sig = Front(&porEjecutar);
            e_ant = Final(&porEjecutar);            
        }
        else {
            if(e.tiempoEjecucion<=0)
                {
                    UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, "Siguiente: -");
                }
            else
                {
                    e_sig = e;
                    sprintf(Sig, "Siguiente: %s %s", e_sig.ID, e_sig.nombre);
                    UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, Sig);
                }


            e_ant = e;
        }
        sprintf(Ant, "Anterior: %s %s", e_ant.ID, e_ant.nombre);
        

        UpdateTextoCaja(InicioCajaX, InicioCajaY - 4, anchoCaja, 3, Ant);
        
        

        if (e.tiempoEjecucion <= 0)
        {
            Queue(&Finalizados, e);
            tamFinalizados = Size(&Finalizados);
            sprintf(FinStr, "Terminados: %d", tamFinalizados);
            UpdateTextoCaja(2, 24, anchoMiniCajas + 3, 3, FinStr);

            sprintf(UltFin, "Ultimo Finalizado: %s %s", e.ID, e.nombre);
            UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 6, anchoCaja, 5, UltFin);
        }
        else
        {
            Queue(&porEjecutar, e);
        }
        tamfaltantes = Size(&porEjecutar);
        FaltantesStr[32];
        sprintf(FaltantesStr, "Faltantes: %d", tamfaltantes);
        UpdateTextoCaja(2, 1, anchoMiniCajas, 3, FaltantesStr);
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
    MoverCursor(1, 28);
    mostrarCursor();
    return 0;
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

void UpdateTextoCaja(int x, int y, int ancho, int alto, char *texto)
{
    int tituloLen = strlen(texto);
    int offsetTituloX = (ancho - tituloLen) / 2;
    int offsetTituloY = alto / 2 + 1;
    int i;

    MoverCursor(x + 1, y + offsetTituloY);
    for (i = 0; i < ancho - 1; i++)
        printf(" ");
    if (tituloLen > 0 && ancho > tituloLen)
    {
        MoverCursor(x + offsetTituloX + 1, y + offsetTituloY);

        printf("%s", texto);
    }
}

void UpdateCajaPrincipal(int x, int y, elemento e)
{
    int i,j;
    
    for (i=1;i<anchoCaja;i++)
        for (j=1;j<altoCaja;j++)
            {
                MoverCursor(x+i,y+j);
                printf(" ");
            }

    
     MoverCursor(x+2,y+2);
    printf("Nombre: %s",e.nombre);
    MoverCursor(x+2,y+3);
    printf("ID: %s",e.ID);
    MoverCursor(x+2,y+4);
    printf("Actividad:");

    
    AjustarTexto(e.actividad, x+4, y+5, MAX_LINEA_ACTIVIDAD, 3);

    MoverCursor(x+2,y+8);
    printf("Tiempo Total: %d",e.tiempoTotal);
    MoverCursor(x+2,y+9);
    printf("Tiempo Restante: %d",e.tiempoEjecucion);

}

void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas)
{
    int len = strlen(texto);
    int inicio = 0, linea = 0;

    while (inicio < len && linea < max_lineas)
    {
        char lineaTexto[MAX_LINEA_ACTIVIDAD + 1];
        int i;

        // Copiar hasta max_ancho o hasta que se encuentre un espacio cercano al límite
        for (i = 0; i < max_ancho && (inicio + i) < len; i++)
        {
            lineaTexto[i] = texto[inicio + i];
        }

        // Si el texto no terminó, tratar de cortar en espacio
        if ((inicio + i) < len && texto[inicio + i] != ' ')
        {
            while (i > 0 && lineaTexto[i - 1] != ' ')
                i--;
        }

        lineaTexto[i] = '\0';  // Terminar línea
        MoverCursor(x, y + linea);
        printf("%s", lineaTexto);

        inicio += i;
        while (texto[inicio] == ' ') inicio++; // Saltar espacios

        linea++;
    }
}
