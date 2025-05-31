#ifndef CONSOLA_UTILS_H
#define CONSOLA_UTILS_H

#include <stdlib.h>

/*
================================================================================
consola_utils.h
Versión: 1.2
Fecha: Mayo 2025
Autor: Coyol Moreno Angel Zoe

Descripción:
------------
Este archivo contiene las declaraciones de utilidades multiplataforma para
manipular la consola.

Funcionalidades:
- Cambiar y restaurar colores de texto y fondo en consola.
- Ocultar y mostrar el cursor.
- Forzar la consola a usar codificación UTF-8.
- Capturar la señal Ctrl+C para ejecutar una función personalizada.

================================================================================
*/

// Colores básicos para la consola
enum Color
{
    NEGRO = 0,
    AZUL,
    VERDE,
    CIAN,
    ROJO,
    MAGENTA,
    AMARILLO,
    BLANCO,
    GRIS_CLARO
};

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
================================================================================
*/
void cambiarColor(int texto, int fondo);

/*
================================================================================
void restaurarColor(void)
Descripción:
------------
Restaura los colores de la consola a los valores predeterminados.
================================================================================
*/
void restaurarColor(void);

/*
================================================================================
void ocultarCursor(void)
Descripción:
------------
Oculta el cursor en la consola.
================================================================================
*/
void ocultarCursor(void);

/*
================================================================================
void mostrarCursor(void)
Descripción:
------------
Muestra el cursor en la consola.
================================================================================
*/
void mostrarCursor(void);

/*
================================================================================
void forzarUTF8(void)
Descripción:
------------
Configura la consola para soportar salida en UTF-8 (acentos, emojis, etc).
================================================================================
*/
void forzarUTF8(void);

/*
================================================================================
void cacharCtrlC(void (*funcion)(void))
Descripción:
------------
Establece una función que se ejecutará al presionar Ctrl + C (SIGINT).
================================================================================
*/
void cacharCtrlC(void (*funcion)(void));

#endif // CONSOLA_UTILS_H
