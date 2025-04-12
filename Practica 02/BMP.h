// bmp.h
#ifndef BMP_H
#define BMP_H

#include <stdio.h>


typedef struct BMP {
    char bm[2];
    int tamano;
    int reservado;
    int offset;
    int tamanoMetadatos;
    int alto;
    int ancho;
    short int numeroPlanos;
    short int profundidadColor;
    int tipoCompresion;
    int tamanoEstructura;
    int pxmh;
    int pxmv;
    int coloresUsados;
    int coloresImportantes;
    int padding;
    unsigned char **pixelR;
    unsigned char **pixelG;
    unsigned char **pixelB;
} BMP;

void abrir_imagen(BMP *imagen, char *ruta);
void crear_imagen(BMP *imagen, char *ruta);


#endif
