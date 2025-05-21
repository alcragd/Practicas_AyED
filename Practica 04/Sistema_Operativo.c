#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include<time.h>



int main()
{
cola porEjecutar, Ejecutando, Finalizados;
int i, cantProcesos, tiempoEjecutar, tiempoTotal;
char NombreProceso[45], actividad[200], ID[45];
elemento e;
Initialize(&porEjecutar);
Initialize(&Ejecutando);
Initialize(&Finalizados);
printf("Ingrese la cantidad de procesos a ejecutar: ");
scanf("%d", &cantProcesos);
getchar();
for(i=0;i<cantProcesos;i++)
{
    printf("Ingrese el nombre del proceso %d: ", i+1);
    fgets(NombreProceso, sizeof(NombreProceso), stdin);
    NombreProceso[strcspn(NombreProceso, "\n")] = 0; // Elimina el salto de línea
    printf("Ingrese su actividad a realizar: ");
    fgets(actividad, sizeof(actividad), stdin);
    actividad[strcspn(actividad, "\n")] = 0; // Elimina el salto de línea
    printf("Ingrese el ID del proceso %d: ", i+1);
    fgets(ID, sizeof(ID), stdin);
    ID[strcspn(ID, "\n")] = 0; // Elimina el salto de línea
    printf("Ingrese el tiempo de ejecucion del proceso %d: ", i+1);
    scanf("%d", &tiempoEjecutar);
    getchar();
    e.tiempoEjecucion = tiempoEjecutar;
    strcpy(e.nombre, NombreProceso);
    strcpy(e.actividad, actividad);
    strcpy(e.ID, ID);
    e.tiempoTotal = 0;
    Queue(&porEjecutar, e);
}
    while(!Empty(&porEjecutar))
    {
        e=Dequeue(&porEjecutar);
        if(e.tiempoEjecucion == 0)
        {
            Queue(&Finalizados, e);
            printf("Proceso finalizado: %s\n", e.nombre);
        }
        else
        {
            Queue(&Ejecutando, e);
            printf("\nEjecutando el proceso: %s\n", e.nombre);
            printf("Actividad: %s\n", e.actividad);
            printf("ID: %s\n", e.ID);
            printf("Tiempo de ejecucion: %d\n", e.tiempoEjecucion);
            printf("Tiempo total: %d\n", e.tiempoTotal);
            Sleep(1000);

            e=Dequeue(&Ejecutando);
            e.tiempoEjecucion--;
            e.tiempoTotal++;
            e.tiempoTotal= e.tiempoTotal+Size(&porEjecutar);
            Queue(&porEjecutar, e);
            
        }
    }

    printf("Los procesos finalizados son:\n");
    while(!Empty(&Finalizados))
    {
        e=Dequeue(&Finalizados);
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
}