#include "consola_utils.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
