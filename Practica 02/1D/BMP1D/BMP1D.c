// bmp.c
//*****************************************************************
// CREACIÓN BASADA EN: BMP.c
//*****************************************************************
// EDGARDO ADRIÁN FRANCO MARTÍNEZ
// (C) Marzo 2023 Versión 2.0 (Modificado con arreglo dinámico 1D)
// Lectura y tratamiento de imágenes BMP
//*****************************************************************

#include "BMP1D.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//************************************************************************
// FUNCIONES
//************************************************************************

void abrir_imagen(BMP *imagen, char *ruta)
{
    FILE *archivo;
    int i, j, k;
    unsigned char R, G, B, var;

    archivo = fopen(ruta, "rb");
    if (!archivo)
    {
        printf("La imagen %s no se encontró\n", ruta);
        exit(1);
    }

    fread(&imagen->bm, sizeof(char), 2, archivo);
    fread(&imagen->tamano, sizeof(int), 1, archivo);
    fread(&imagen->reservado, sizeof(int), 1, archivo);
    fread(&imagen->offset, sizeof(int), 1, archivo);
    fread(&imagen->tamanoMetadatos, sizeof(int), 1, archivo);
    fread(&imagen->alto, sizeof(int), 1, archivo);
    fread(&imagen->ancho, sizeof(int), 1, archivo);
    fread(&imagen->numeroPlanos, sizeof(short int), 1, archivo);
    fread(&imagen->profundidadColor, sizeof(short int), 1, archivo);
    fread(&imagen->tipoCompresion, sizeof(int), 1, archivo);
    fread(&imagen->tamanoEstructura, sizeof(int), 1, archivo);
    fread(&imagen->pxmh, sizeof(int), 1, archivo);
    fread(&imagen->pxmv, sizeof(int), 1, archivo);
    fread(&imagen->coloresUsados, sizeof(int), 1, archivo);
    fread(&imagen->coloresImportantes, sizeof(int), 1, archivo);

    if (imagen->bm[0] != 'B' || imagen->bm[1] != 'M')
    {
        printf("La imagen debe ser un bitmap.\n");
        exit(1);
    }
    if (imagen->profundidadColor != 24)
    {
        printf("La imagen debe ser de 24 bits.\n");
        exit(1);
    }

    imagen->padding = (4 - (imagen->ancho * 3) % 4) % 4;

    int totalPixeles = imagen->ancho * imagen->alto;
    imagen->pixelR = malloc(totalPixeles * sizeof(unsigned char));
    imagen->pixelG = malloc(totalPixeles * sizeof(unsigned char));
    imagen->pixelB = malloc(totalPixeles * sizeof(unsigned char));

    fseek(archivo, imagen->offset, SEEK_SET);

    for (i = imagen->alto - 1; i >= 0; i--)
    {
        for (j = 0; j < imagen->ancho; j++)
        {
            int idx = i * imagen->ancho + j;
            fread(&B, sizeof(char), 1, archivo);
            fread(&G, sizeof(char), 1, archivo);
            fread(&R, sizeof(char), 1, archivo);
            imagen->pixelR[idx] = R;
            imagen->pixelG[idx] = G;
            imagen->pixelB[idx] = B;
        }
        for (k = 0; k < imagen->padding; k++)
        {
            fread(&var, sizeof(char), 1, archivo);
        }
    }

    fclose(archivo);
}

void crear_imagen(BMP *imagen, char ruta[])
{
    FILE *archivo;
    int i, j, k;
    unsigned char var = 0x00;

    archivo = fopen(ruta, "wb");
    if (!archivo)
    {
        printf("La imagen %s no se pudo crear\n", ruta);
        exit(1);
    }

    fwrite(&imagen->bm, sizeof(char), 2, archivo);
    fwrite(&imagen->tamano, sizeof(int), 1, archivo);
    fwrite(&imagen->reservado, sizeof(int), 1, archivo);
    fwrite(&imagen->offset, sizeof(int), 1, archivo);
    fwrite(&imagen->tamanoMetadatos, sizeof(int), 1, archivo);
    fwrite(&imagen->alto, sizeof(int), 1, archivo);
    fwrite(&imagen->ancho, sizeof(int), 1, archivo);
    fwrite(&imagen->numeroPlanos, sizeof(short int), 1, archivo);
    fwrite(&imagen->profundidadColor, sizeof(short int), 1, archivo);
    fwrite(&imagen->tipoCompresion, sizeof(int), 1, archivo);
    fwrite(&imagen->tamanoEstructura, sizeof(int), 1, archivo);
    fwrite(&imagen->pxmh, sizeof(int), 1, archivo);
    fwrite(&imagen->pxmv, sizeof(int), 1, archivo);
    fwrite(&imagen->coloresUsados, sizeof(int), 1, archivo);
    fwrite(&imagen->coloresImportantes, sizeof(int), 1, archivo);

    fseek(archivo, imagen->offset, SEEK_SET);

    for (i = imagen->alto - 1; i >= 0; i--)
    {
        for (j = 0; j < imagen->ancho; j++)
        {
            int idx = i * imagen->ancho + j;
            fwrite(&imagen->pixelB[idx], sizeof(char), 1, archivo);
            fwrite(&imagen->pixelG[idx], sizeof(char), 1, archivo);
            fwrite(&imagen->pixelR[idx], sizeof(char), 1, archivo);
        }
        for (k = 0; k < imagen->padding; k++)
        {
            fwrite(&var, sizeof(char), 1, archivo);
        }
    }

    fclose(archivo);
}
