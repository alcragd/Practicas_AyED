/*
================================================================================
Supermercado.c
Versión: 1.0
Fecha: Mayo 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
------------
Este programa simula el funcionamiento de un supermercado con múltiples cajas 
de atención, gestionando dinámicamente las colas de clientes y mostrando de 
forma visual su llegada y atención en la consola.

El sistema permite:
- Configurar el número de cajas y su tiempo de atención.
- Definir el intervalo de llegada de nuevos clientes.
- Dibujar gráficamente las cajas y las colas en consola.
- Mostrar en tiempo real cuántos clientes han sido atendidos y cuántos están
  formados.
- Usar emojis aleatorios para representar gráficamente a los clientes.
- Finalizar automáticamente cuando se atienden al menos 100 clientes y no
  queden personas en espera.

Compilación:
------------
gcc -o Supermercado.exe Supermercado.c
    ./Cola Dinamica/TADColaDin.c ./Presentacion/presentacion.c
    ./Utils/consola_utils.c

Uso:
----
./Supermercado.exe

El programa solicitará:
  - Nombre del supermercado.
  - Número de cajas (1 a 10).
  - Tiempo de atención por caja (múltiplo de 10ms).
  - Tiempo de llegada de clientes (múltiplo de 10ms).

Salida:
-------
- Interfaz gráfica en consola representando cajas y clientes.
- Número de clientes atendidos y en espera, actualizados en tiempo real.
- Finalización con un resumen de clientes atendidos.

Observaciones:
--------------
- Asegúrate de que la consola tenga un tamaño mínimo de 120x30 caracteres.
- Los tiempos deben ser múltiplos de 10 para sincronización con el sistema.
- Usa colas dinámicas (`TADColaDin.h`) para gestionar a los clientes.
- El uso de Ctrl+C es interceptado para limpiar la consola y restaurar el cursor.
================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include "Utils/consola_utils.h"
#include <time.h>
// #include "Cola Estática/TADColaEst.h"
#define TIEMPO_BASE 10 // 10ms

#define ANCHO 120 //
#define ALTO 30   // ANCHO y AlTO de la consola*
#define anchoCaja 5
#define altoCaja 8
#define DISTANCIA 2 // Distancia entre clientes

//Prototipos
void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion);
void AtenderCliente(cola *c, int numcola, int separacion);
void LlegadaCliente(int numcliente, int numcola, cola *c, int separacion);
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
    char nombreSuper[50];
    int numCajas, i, clientes = 0, tiempo = 0, clientesAtendidos = 0, colAtendidos, colFormados;
    int caja, separacionCajas;
    int *tiempoAtencion;
    int tiempoLlegada;

    cola *cajas;
    int repetir = 1;
    elemento e;

    srand(time(NULL));

    forzarUTF8();
    BorrarPantalla();

    cacharCtrlC(cuandoCtrlC);

    printf("Ingrese el nombre del supermercado: \n>> ");
    fgets(nombreSuper, sizeof(nombreSuper), stdin);
    nombreSuper[strcspn(nombreSuper, "\n")] = 0;

    printf("\nIngrese el numero de cajas:\n>> ");
    scanf("%d", &numCajas);

    while (numCajas < 1 || numCajas > 10)
    {
        printf("\n[*]-- El numero de cajas debe estar entre 1 y 10\n>> ");
        scanf("%d", &numCajas);
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
        printf("\nIngrese el tiempo de atencion de la caja %d en milisegundos: \n>> ", i + 1);
        scanf("%d", &tiempoAtencion[i]);

        while (tiempoAtencion[i] % 10 != 0)
        {
            printf("\n[*]-- El tiempo de atencion debe ser un multiplo de 10 \n>> ");
            scanf("%d", &tiempoAtencion[i]);
        }

        Initialize(&cajas[i]);
    }
    printf("\nIngrese el tiempo de llegada de los clientes en milisegundos:\n>> ");
    scanf("%d", &tiempoLlegada);

    while (tiempoLlegada % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoLlegada);
    }

    separacionCajas = (ANCHO - anchoCaja * numCajas) / (numCajas + 1);

    if (separacionCajas < 7)
    {
        separacionCajas = 7; // Asegurar una separación minima
        printf("\n[!]-- Separación minima alcanzada, se recomienda ampliar el tamaño de la consola.");
    }

    printf("\n");
    system("pause");

    BorrarPantalla();
    ocultarCursor();

    MoverCursor((ANCHO - strlen(nombreSuper) - 13) / 2, 0); // Centrar nombre del supermercado
    printf("Supermercado ");
    cambiarColor(VERDE, NEGRO);
    printf("%s", nombreSuper);
    restaurarColor();
    // Espacio entre cajas
    for (i = 1; i <= numCajas; i++)
        DibujaCaja(i, i, anchoCaja, altoCaja, separacionCajas);

    MoverCursor(1, 11 + 7 * DISTANCIA);
    printf("Clientes Atendidos: 0");
    MoverCursor(1, 12 + 7 * DISTANCIA);
    printf("Clientes Formados: 0");

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

                    if (clientesAtendidos >= 100)
                        colAtendidos = VERDE;
                    else if (clientesAtendidos >= 50)
                        colAtendidos = AMARILLO;
                    else
                        colAtendidos = ROJO;

                    if (clientes - clientesAtendidos >= clientesAtendidos)
                        colFormados = ROJO;
                    else if (clientes - clientesAtendidos >= clientesAtendidos / 2)
                        colFormados = AMARILLO;
                    else
                        colFormados = VERDE;

                    cambiarColor(colAtendidos, NEGRO);
                    MoverCursor(21, 11 + 7 * DISTANCIA);
                    printf("%d", clientesAtendidos);

                    cambiarColor(colFormados, NEGRO);
                    MoverCursor(20, 12 + 7 * DISTANCIA);
                    printf("%d", clientes - clientesAtendidos);

                    restaurarColor();
                    // e = Dequeue(&cajas[i]);
                    // printf("\n\nAtendi a: %d en caja %d", e.i, i + 1);
                }
                // else
                // {
                //     // printf("\n\nNo hay alguien por atender en caja %d", i + 1);
                // }
            }
        }

        if ((tiempo * 10 % tiempoLlegada == 0) && repetir)
        {
            clientes++;

            caja = rand() % numCajas;

            LlegadaCliente(clientes, caja, &cajas[caja], separacionCajas);

            if (clientes - clientesAtendidos >= clientesAtendidos)
                colFormados = ROJO;
            else if (clientes - clientesAtendidos >= clientesAtendidos / 2)
                colFormados = AMARILLO;
            else
                colFormados = VERDE;

            cambiarColor(colFormados, NEGRO);
            MoverCursor(20, 12 + 7 * DISTANCIA);
            printf("%d", clientes - clientesAtendidos);

            restaurarColor();

            if (clientes == 9999) //Si el numero de clientes llega a 9999 termina la animacion
                break;

            // e.i = clientes;
            // Queue(&cajas[caja], e);
            // printf("\n\nLlego el cliente: %d a la cola de la caja %d", e.i, caja + 1);
        }

        if (clientesAtendidos >= 100)
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
    MoverCursor(0, ALTO - 2);
    printf("\n\n\nClientes atendidos: %d", clientesAtendidos);
    printf("\nTienda %s cerrada", nombreSuper);
    mostrarCursor();
    free(tiempoAtencion);
    free(cajas);
    return 0;
}
/*
void DibujaCaja(int num, int cliente, int ancho, int alto, int separacion)
Recibe:
    int num: número de caja (1 a N).
    int cliente: número de cliente (no usado directamente en esta versión).
    int ancho: ancho del dibujo de la caja.
    int alto: alto del dibujo de la caja.
    int separacion: espacio horizontal entre cajas.
Devuelve:
    Nada.
Observaciones:
    Dibuja gráficamente una caja en la consola utilizando caracteres.
*/
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

    MoverCursor(columna - (ancho / 2), 5);
    printf("🗃️");
    // MoverCursor(columna + ancho / 2 - 1, 7);
    // printf("C%d", cliente);
}
/*
void LlegadaCliente(int numcliente, int numcola, cola *c, int separacion)
Recibe:
    int numcliente: número de cliente actual.
    int numcola: número de la cola (índice de caja).
    cola *c: puntero a la estructura de cola donde se insertará el cliente.
    int separacion: espacio horizontal entre cajas.
Devuelve:
    Nada.
Observaciones:
    Inserta un nuevo cliente a la cola correspondiente y lo muestra visualmente en la consola.
*/
void LlegadaCliente(int numcliente, int numcola, cola *c, int separacion)
{
    int columna, posX, posY, emoji_indice;
    elemento e;

    columna = separacion + (numcola) * (anchoCaja + separacion);
    posX = columna + anchoCaja + 1;
    emoji_indice = rand() % NUM_EMOJIS;

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
        printf("%s%d", Emojis[emoji_indice], numcliente);
    }
    else
    {
        posY = 9 + 7 * DISTANCIA;
        MoverCursor(posX, posY);
        cambiarColor(GRIS_CLARO, NEGRO);
        printf("+%d", Size(c) - 6);
        restaurarColor();
    }

    e.i = numcliente;
    e.emoji = emoji_indice;

    Queue(c, e);
}
/*
void AtenderCliente(cola *c, int numcola, int separacion)
Recibe:
    cola *c: puntero a la estructura de cola de la caja que está atendiendo.
    int numcola: índice de la caja (0 a N-1).
    int separacion: espacio horizontal entre cajas.
Devuelve:
    Nada.
Observaciones:
    Elimina al primer cliente de la cola, limpia su visualización y reorganiza gráficamente a los demás clientes.
*/
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
        printf("      ");
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

            printf("%s%d", Emojis[Element(c, i).emoji], Element(c, i).i);
        }

        else
        {
            posY = 9 + 7 * DISTANCIA;
            MoverCursor(posX, posY);
            cambiarColor(GRIS_CLARO, NEGRO);
            printf("+%d", Size(c) - 6);
            restaurarColor();
            break;
        }
    }
}
/*
void cuandoCtrlC(void)
Recibe:
    Nada.
Devuelve:
    Nada.
Observaciones:
    Maneja la interrupción Ctrl+C restaurando el cursor y los colores antes de terminar el programa.
*/
void cuandoCtrlC(void)
{

    restaurarColor();
    mostrarCursor();
    MoverCursor(0, ALTO - 2);

    exit(0);
}