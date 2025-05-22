#ifndef CONSOLA_UTILS_H
#define CONSOLA_UTILS_H

#include <stdlib.h>
// Colores básicos
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

// Cambiar color de texto y fondo
void cambiarColor(int texto, int fondo);

// Restaurar color predeterminado
void restaurarColor(void);

// Ocultar cursor de la consola
void ocultarCursor(void);

// Mostrar cursor de la consola
void mostrarCursor(void);

// Configura la consola para usar codificación UTF-8(Acentos, emojis, ...)
void forzarUTF8(void);

// Establece una función que se ejecutará al presionar Ctrl + C
void cacharCtrlC(void (*funcion)(void));

#endif // CONSOLA_UTILS_H
