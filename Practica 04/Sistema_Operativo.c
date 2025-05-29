/*
================================================================================
Sistema_Operativo.c
Versión: 1.0
Fecha: Mayo 2025
Autor: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
------------
Este programa simula la ejecución de procesos en un sistema, mostrando en consola
una interfaz visual con información de los procesos que están por ejecutarse,
los que están en ejecución y los finalizados.

Funcionalidades:
- Permite ingresar una cantidad determinada de procesos con sus datos: ID, nombre,
  actividad y tiempo de ejecución.
- Muestra en tiempo real la ejecución de cada proceso, actualizando su estado,
  tiempo restante y tiempo total ejecutado.
- Presenta información visual de procesos anteriores, actuales, siguientes y últimos
  finalizados mediante "cajas" en consola.
- Ajusta textos largos para mostrar las actividades de los procesos en varias líneas.
- Al terminar, muestra el orden de finalización de los procesos.

Compilación:
------------
gcc -o Sistema_Operativo.exe Sistema_Operativo.c
    ./Cola Dinamica/TADColaDin.c ./Presentacion/presentacion.c
    ./Utils/consola_utils.c
-libraries: windows.h para EsperarMiliSeg y manipulación de consola.

Uso:
----
./Sistema_Operativo.exe

El programa solicitará:
  - Cantidad de procesos a ejecutar.
  - Para cada proceso: ID, nombre, actividad y tiempo de ejecución (en segundos).

Salida:
-------
- Visualización en consola del estado de los procesos en ejecución.
- Información dinámica actualizada del tiempo transcurrido y procesos pendientes.
- Listado final de procesos en orden de finalización.

Observaciones:
--------------
- Se recomienda ejecutar en consola con tamaño mínimo 120x30.
- Utiliza colas dinámicas para gestionar los procesos.
- La interfaz gráfica usa caracteres ASCII para dibujar cajas y mostrar textos.
- Requiere los archivos y librerías auxiliares indicados para funcionar correctamente.
================================================================================
*/
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
#define anchoMiniCajas 21

// Prototipos de funciones
void DibujarCaja(int x, int y, int ancho, int alto, char *texto);
void UpdateTextoCaja(int x, int y, int ancho, int alto, char *texto);
void UpdateCajaPrincipal(int x, int y, elemento e);
void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas);
void cuandoCtrlC(void);

const char *emojisReloj[] = {
    "🕛", // 12:00
    "🕧", // 12:30
    "🕐", // 1:00
    "🕜", // 1:30
    "🕑", // 2:00
    "🕝", // 2:30
    "🕒", // 3:00
    "🕞", // 3:30
    "🕓", // 4:00
    "🕟", // 4:30
    "🕔", // 5:00
    "🕠", // 5:30
    "🕕", // 6:00
    "🕡", // 6:30
    "🕖", // 7:00
    "🕢", // 7:30
    "🕗", // 8:00
    "🕣", // 8:30
    "🕘", // 9:00
    "🕤", // 9:30
    "🕙", // 10:00
    "🕥", // 10:30
    "🕚", // 11:00
    "🕦"  // 11:30
};
#define NUM_EMOJIS_RELOJ (sizeof(emojisReloj) / sizeof(emojisReloj[0]))

int main()
{
    cola porEjecutar, Ejecutando, Finalizados;
    int i, cantProcesos, tiempoEjecutar, tiempoTotal = 0;
    int InicioCajaX, InicioCajaY;
    char NombreProceso[45], actividad[200], ID[45];
    char tiempoStr[32], FinStr[32], FaltantesStr[32], UltFin[32], Ant[32], Sig[32];
    elemento e, e_ant, e_sig;

    // Inicializa colas dinámicas
    Initialize(&porEjecutar);
    Initialize(&Ejecutando);
    Initialize(&Finalizados);

    cacharCtrlC(cuandoCtrlC);

    // Solicita cantidad de procesos
    printf("Ingrese la cantidad de procesos a ejecutar: ");
    scanf("%d", &cantProcesos);
    getchar();

    // Lectura de datos de cada proceso
    for (i = 0; i < cantProcesos; i++)
    {
        printf("Ingrese el ID del proceso %d: ", i + 1);
        fgets(ID, sizeof(ID), stdin);
        ID[strcspn(ID, "\n")] = 0;

        printf("Ingrese el nombre del proceso %d: ", i + 1);
        fgets(NombreProceso, sizeof(NombreProceso), stdin);
        NombreProceso[strcspn(NombreProceso, "\n")] = 0;

        printf("Ingrese su actividad a realizar: ");
        fgets(actividad, sizeof(actividad), stdin);
        actividad[strcspn(actividad, "\n")] = 0;

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

    // Configura consola y ubicación para dibujar cajas
    ocultarCursor();
    forzarUTF8();
    BorrarPantalla();
    InicioCajaX = (ANCHO - anchoCaja) / 2 + 10;
    InicioCajaY = (ALTO - altoCaja) / 2 - 5;

    // Dibuja cajas fijas para información
    DibujarCaja(2, 1, anchoMiniCajas, 3, "📝 Faltantes: -");
    DibujarCaja(2, 12, anchoMiniCajas, 3, "🕛 Tiempo: -");
    DibujarCaja(2, 24, anchoMiniCajas + 3, 3, "⚙️ Terminados: -");
    DibujarCaja(InicioCajaX, InicioCajaY - 4, anchoCaja, 3, "↩️ Anterior: -");
    DibujarCaja(InicioCajaX, InicioCajaY, anchoCaja, altoCaja, "");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, "↪️ Siguiente: -");
    DibujarCaja(InicioCajaX, altoCaja + InicioCajaY + 6, anchoCaja, 5, "📀 Ultimo Finalizado: -");
    MoverCursor(0, 29);

    // Ciclo principal: ejecuta procesos hasta que se terminen todos
    while (!Empty(&porEjecutar))
    {
        EsperarMiliSeg(1000); // Simula 1 segundo de ejecución
        tiempoTotal++;
        sprintf(tiempoStr, "%s Tiempo: %d", emojisReloj[tiempoTotal % NUM_EMOJIS_RELOJ], tiempoTotal);
        UpdateTextoCaja(2, 12, anchoMiniCajas, 3, tiempoStr);

        e = Dequeue(&porEjecutar);
        e.tiempoEjecucion--;
        e.tiempoTotal = tiempoTotal;

        UpdateCajaPrincipal(InicioCajaX, InicioCajaY, e);

        // Maneja procesos anterior y siguiente
        if (!Empty(&porEjecutar))
        {
            e_sig = Front(&porEjecutar);
            e_ant = Final(&porEjecutar);

            sprintf(Sig, "↪️ Siguiente: %s %s", e_sig.ID, e_sig.nombre);
            UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, Sig);
        }
        else
        {
            if (e.tiempoEjecucion <= 0)
            {
                UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, "↪️ Siguiente: -");
            }
            else
            {
                e_sig = e;
                sprintf(Sig, "↪️ Siguiente: %s %s", e_sig.ID, e_sig.nombre);
                UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 1, anchoCaja, 3, Sig);
            }
            e_ant = e;
        }
        sprintf(Ant, "↩️ Anterior: %s %s", e_ant.ID, e_ant.nombre);
        UpdateTextoCaja(InicioCajaX, InicioCajaY - 4, anchoCaja, 3, Ant);

        // Verifica si el proceso actual terminó
        if (e.tiempoEjecucion <= 0)
        {
            Queue(&Finalizados, e);
            int tamFinalizados = Size(&Finalizados);
            sprintf(FinStr, "🗒️ Terminados: %d", tamFinalizados);
            UpdateTextoCaja(2, 24, anchoMiniCajas + 3, 3, FinStr);

            sprintf(UltFin, "📀 Ultimo Finalizado: %s %s", e.ID, e.nombre);
            UpdateTextoCaja(InicioCajaX, altoCaja + InicioCajaY + 6, anchoCaja, 5, UltFin);
        }
        else
        {
            Queue(&porEjecutar, e);
        }

        int tamfaltantes = Size(&porEjecutar);
        sprintf(FaltantesStr, "📝 Faltantes: %d", tamfaltantes);
        UpdateTextoCaja(2, 1, anchoMiniCajas, 3, FaltantesStr);
    }

    EsperarMiliSeg(1000);
    BorrarPantalla();

    // Muestra orden de finalización
    MoverCursor((ANCHO - 21) / 2, 5);
    printf("Orden de Finalización:\n");

    i = 1;

    while (!Empty(&Finalizados))
    {
        EsperarMiliSeg(300);
        e = Dequeue(&Finalizados);
        printf("\n%d. ID: %s\tNombre: %s\t Tiempo de ejecución: %d", i, e.ID, e.nombre, e.tiempoTotal);
        i++;
    }

    // Limpieza de colas
    Destroy(&porEjecutar);
    Destroy(&Ejecutando);
    Destroy(&Finalizados);

    MoverCursor(0, 29);
    printf("\n");
    return 0;
}
/*
================================================================================
void DibujarCaja(int x, int y, int ancho, int alto, char *texto)

Descripción:
------------
Dibuja una caja rectangular con bordes usando caracteres ASCII en la consola.
Coloca un texto centrado vertical y horizontalmente dentro de la caja.

Parámetros:
-----------
x       : Posición horizontal (columna) en la consola donde inicia la caja.
y       : Posición vertical (fila) en la consola donde inicia la caja.
ancho   : Ancho total de la caja (en caracteres).
alto    : Alto total de la caja (en líneas).
texto   : Cadena de texto que se mostrará centrada dentro de la caja.

Salida:
-------
Dibuja la caja y el texto en la consola.

Observaciones:
--------------
- Usa funciones para mover el cursor en consola.
- Los bordes se dibujan con caracteres '_' y '|'.
- El texto se centra solo si cabe dentro de la caja.
================================================================================
*/
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
/*
================================================================================
void UpdateTextoCaja(int x, int y, int ancho, int alto, char *texto)

Descripción:
------------
Actualiza el texto que se muestra dentro de una caja ya dibujada en la consola.
Limpia la línea donde se colocará el texto y luego imprime el nuevo texto centrado.

Parámetros:
-----------
x       : Posición horizontal (columna) de la caja.
y       : Posición vertical (fila) de la caja.
ancho   : Ancho de la caja (en caracteres).
alto    : Alto de la caja (en líneas).
texto   : Texto nuevo a mostrar dentro de la caja.

Salida:
-------
Actualiza el texto dentro de la caja en consola.

Observaciones:
--------------
- Asume que la caja ya está dibujada.
- Limpia la línea de texto para evitar restos de texto anterior.
================================================================================
*/
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
/*
================================================================================
void UpdateCajaPrincipal(int x, int y, elemento e)

Descripción:
------------
Actualiza el contenido de la caja principal que muestra los detalles del proceso
actual en ejecución.

Parámetros:
-----------
x : Posición horizontal (columna) donde se dibuja la caja.
y : Posición vertical (fila) donde se dibuja la caja.
e : Estructura que contiene los datos del proceso (nombre, ID, actividad,
    tiempo total y tiempo restante).

Salida:
-------
Actualiza la información del proceso dentro de la caja principal en consola.

Observaciones:
--------------
- Limpia el área de la caja antes de actualizar para evitar restos.
- Muestra texto en varias líneas para los diferentes campos.
- Usa la función AjustarTexto para mostrar la actividad en múltiples líneas.
================================================================================
*/
void UpdateCajaPrincipal(int x, int y, elemento e)
{
    int i, j;

    for (i = 1; i < anchoCaja; i++)
        for (j = 1; j < altoCaja; j++)
        {
            MoverCursor(x + i, y + j);
            printf(" ");
        }

    MoverCursor(x + 4, y + 2);
    printf("🆔 ID: %s", e.ID);
    MoverCursor(x + 4, y + 3);
    printf("✅ Nombre: %s", e.nombre);
    MoverCursor(x + 4, y + 4);
    printf("ℹ️ Actividad:");

    AjustarTexto(e.actividad, x + 8, y + 5, 70, 3);

    MoverCursor(x + 4, y + 8);
    printf("⏱️ Tiempo Total: %d", e.tiempoTotal);
    MoverCursor(x + 4, y + 9);
    printf("⌛ Tiempo Restante: %d", e.tiempoEjecucion);
}
/*
================================================================================
void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas)

Descripción:
------------
Imprime un texto largo en la consola ajustándolo para que no sobrepase un ancho
máximo y dividiéndolo en varias líneas, hasta un número máximo de líneas.

Parámetros:
-----------
texto       : Cadena de texto a mostrar.
x           : Posición horizontal (columna) donde inicia el texto.
y           : Posición vertical (fila) donde inicia el texto.
max_ancho   : Máximo ancho (caracteres) permitido por línea.
max_lineas  : Máximo número de líneas a mostrar.

Salida:
-------
Imprime el texto ajustado en consola.

Observaciones:
--------------
- Intenta no cortar palabras a la mitad, buscando un espacio cercano para cortar.
- Si el texto es más largo que el permitido, se trunca.
================================================================================
*/
void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas)
{
    int len = strlen(texto);
    int inicio = 0, linea = 0;

    while (inicio < len && linea < max_lineas)
    {
        char lineaTexto[max_ancho + 1];
        int i;

        // Copiar hasta max_ancho o hasta que se encuentre un espacio cercano al límite
        for (i = 0; i < max_ancho && (inicio + i) < len; i++)
            lineaTexto[i] = texto[inicio + i];

        // Si el texto no terminó, tratar de cortar en espacio
        if ((inicio + i) < len && texto[inicio + i] != ' ')
        {
            while (i > 0 && lineaTexto[i - 1] != ' ')
                i--;
        }

        lineaTexto[i] = '\0'; // Terminar línea
        MoverCursor(x, y + linea);
        printf("%s", lineaTexto);

        inicio += i;
        while (texto[inicio] == ' ')
            inicio++; // Saltar espacios

        linea++;
    }
}

void cuandoCtrlC(void)
{

    restaurarColor();
    mostrarCursor();
    MoverCursor(0, ALTO - 2);

    exit(0);
}