/*
================================================================================
consola_utils.c
Versión: 1.2
Fecha: Mayo 2025
Autor: Coyol Moreno Angel Zoe

Descripción:
------------
Este archivo contiene las declaraciones de funciones definidas en
"consola_utils.h"

================================================================================
*/

#include "consola_utils.h"
#include <stdio.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <locale.h>
#endif

// Variables y funciones internas para manejo de Ctrl+C
static void (*funcionCtrlC)(void) = NULL;

static void CtrlCAux(int sig)
{
    if (sig == SIGINT && funcionCtrlC != NULL)
    {
        funcionCtrlC();
    }
}

/*
================================================================================
void cambiarColor(int texto, int fondo)
Descripción:
------------
Cambia el color del texto y del fondo en la consola.

Parámetros:
-----------
texto : Código de color para el texto.
fondo : Código de color para el fondo.

Salida:
-------
La consola cambia los colores especificados.
================================================================================
*/
void cambiarColor(int texto, int fondo)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (fondo << 4) | texto);
#else
    int textoAnsi = 30 + texto;
    int fondoAnsi = 40 + fondo;
    printf("\033[0;%d;%dm", textoAnsi, fondoAnsi);
    fflush(stdout);
#endif
}

/*
================================================================================
void restaurarColor(void)
Descripción:
------------
Restaura los colores de la consola a los valores predeterminados.

Parámetros:
-----------
Ninguno.

Salida:
-------
La consola vuelve a los colores por defecto.
================================================================================
*/
void restaurarColor(void)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
#else
    printf("\033[0m");
    fflush(stdout);
#endif
}

/*
================================================================================
void ocultarCursor(void)
Descripción:
------------
Oculta el cursor en la consola.

Parámetros:
-----------
Ninguno.

Salida:
-------
El cursor de la consola se oculta.
================================================================================
*/
void ocultarCursor(void)
{
#ifdef _WIN32
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hCon, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
#else
    printf("\033[?25l");
    fflush(stdout);
#endif
}

/*
================================================================================
void mostrarCursor(void)
Descripción:
------------
Muestra el cursor en la consola.

Parámetros:
-----------
Ninguno.

Salida:
-------
El cursor de la consola se muestra.
================================================================================
*/
void mostrarCursor(void)
{
#ifdef _WIN32
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hCon, &cci);
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hCon, &cci);
#else
    printf("\033[?25h");
    fflush(stdout);
#endif
}

/*
================================================================================
void forzarUTF8(void)
Descripción:
------------
Configura la consola para soportar salida en UTF-8.

Parámetros:
-----------
Ninguno.

Salida:
-------
La consola acepta y muestra correctamente caracteres UTF-8.
================================================================================
*/
void forzarUTF8(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#else
    setlocale(LC_ALL, "");
#endif
}

/*
================================================================================
void cacharCtrlC(void (*funcion)(void))
Descripción:
------------
Permite capturar la señal Ctrl+C (SIGINT) y ejecutar una función personalizada
antes de finalizar el programa.

Parámetros:
-----------
funcion : Puntero a la función que se ejecutará al presionar Ctrl+C.

Salida:
-------
La función indicada se ejecuta al recibir SIGINT.
================================================================================
*/
void cacharCtrlC(void (*funcion)(void))
{
    funcionCtrlC = funcion;
    signal(SIGINT, CtrlCAux);
}
