/*
================================================================================
RellenoConColor.c
Versión: 2.1 (actualizada a 1D)
Fecha: Abril 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel
================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BMP1D/BMP1D.h"
#include "pila_dinamica/pila_din.h"

#define IMAGEN_TRATADA "tratada.bmp"
#define TOLERANCIA 20

typedef char booleano;
#define true 1
#define false 0

typedef elemento coordenada;

void RellenoConColorRGB(unsigned char *R, unsigned char *G, unsigned char *B, int x, int y,
                        int r_orig, int g_orig, int b_orig,
                        int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

void RellenoConColorRGB_Iterativo(unsigned char *R, unsigned char *G, unsigned char *B, int x, int y,
                                  int r_orig, int g_orig, int b_orig,
                                  int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

booleano EsColorSimilar(int r_1, int g_1, int b_1, int r_2, int g_2, int b_2);

int main(int argc, char *argv[])
{
  BMP img;
  char IMAGEN[45];
  int r_o, g_o, b_o, x, y, r_n, g_n, b_n;
  clock_t t_inicio, t_final;
  double t_intervalo;

  if (argc != 7)
  {
    printf("\n[!]--- Error: Numero incorrecto de argumentos.\n");
    printf("Uso: %s x y R G B imagen.bmp\n", argv[0]);
    exit(1);
  }

  y = atoi(argv[1]);
  x = atoi(argv[2]);
  r_n = atoi(argv[3]);
  g_n = atoi(argv[4]);
  b_n = atoi(argv[5]);
  strcpy(IMAGEN, argv[6]);

  abrir_imagen(&img, IMAGEN);
  printf("Dimensiones: Alto=%d, Ancho=%d\n", img.alto, img.ancho);

  int idx = x * img.ancho + y;
  r_o = img.pixelR[idx];
  g_o = img.pixelG[idx];
  b_o = img.pixelB[idx];

  t_inicio = clock();

  RellenoConColorRGB_Iterativo(img.pixelR, img.pixelG, img.pixelB,
                               x, y, r_o, g_o, b_o, r_n, g_n, b_n,
                               img.ancho, img.alto);

  t_final = clock();

  t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
  printf("Tiempo medido: %.8f segundos.\n", t_intervalo);

  crear_imagen(&img, IMAGEN_TRATADA);
  printf("Imagen tratada guardada en: %s\n", IMAGEN_TRATADA);

  return 0;
}

void RellenoConColorRGB_Iterativo(unsigned char *R, unsigned char *G, unsigned char *B, int x, int y,
                                  int r_orig, int g_orig, int b_orig,
                                  int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
  if (x < 0 || x >= alto || y < 0 || y >= ancho)
    return;

  int idx = x * ancho + y;
  if (R[idx] == r_nuevo && G[idx] == g_nuevo && B[idx] == b_nuevo)
    return;

  pila rastro;
  Initialize(&rastro);

  R[idx] = r_nuevo;
  G[idx] = g_nuevo;
  B[idx] = b_nuevo;
  Push(&rastro, (coordenada){x, y});

  while (!Empty(&rastro))
  {
    coordenada coord = Pop(&rastro);
    int cx = coord.x;
    int cy = coord.y;
    int cidx;

    // Abajo
    if (cx + 1 < alto)
    {
      cidx = (cx + 1) * ancho + cy;
      if (EsColorSimilar(R[cidx], G[cidx], B[cidx], r_orig, g_orig, b_orig))
      {
        R[cidx] = r_nuevo;
        G[cidx] = g_nuevo;
        B[cidx] = b_nuevo;
        Push(&rastro, (coordenada){cx + 1, cy});
      }
    }
    // Arriba
    if (cx - 1 >= 0)
    {
      cidx = (cx - 1) * ancho + cy;
      if (EsColorSimilar(R[cidx], G[cidx], B[cidx], r_orig, g_orig, b_orig))
      {
        R[cidx] = r_nuevo;
        G[cidx] = g_nuevo;
        B[cidx] = b_nuevo;
        Push(&rastro, (coordenada){cx - 1, cy});
      }
    }
    // Derecha
    if (cy + 1 < ancho)
    {
      cidx = cx * ancho + (cy + 1);
      if (EsColorSimilar(R[cidx], G[cidx], B[cidx], r_orig, g_orig, b_orig))
      {
        R[cidx] = r_nuevo;
        G[cidx] = g_nuevo;
        B[cidx] = b_nuevo;
        Push(&rastro, (coordenada){cx, cy + 1});
      }
    }
    // Izquierda
    if (cy - 1 >= 0)
    {
      cidx = cx * ancho + (cy - 1);
      if (EsColorSimilar(R[cidx], G[cidx], B[cidx], r_orig, g_orig, b_orig))
      {
        R[cidx] = r_nuevo;
        G[cidx] = g_nuevo;
        B[cidx] = b_nuevo;
        Push(&rastro, (coordenada){cx, cy - 1});
      }
    }
  }

  Destroy(&rastro);
}

void RellenoConColorRGB(unsigned char *R, unsigned char *G, unsigned char *B, int x, int y,
                        int r_orig, int g_orig, int b_orig,
                        int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
  if (x < 0 || x >= alto || y < 0 || y >= ancho)
    return;

  int idx = x * ancho + y;
  if (R[idx] == r_nuevo && G[idx] == g_nuevo && B[idx] == b_nuevo)
    return;

  if (!EsColorSimilar(R[idx], G[idx], B[idx], r_orig, g_orig, b_orig))
    return;

  R[idx] = r_nuevo;
  G[idx] = g_nuevo;
  B[idx] = b_nuevo;

  RellenoConColorRGB(R, G, B, x + 1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
  RellenoConColorRGB(R, G, B, x - 1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
  RellenoConColorRGB(R, G, B, x, y + 1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
  RellenoConColorRGB(R, G, B, x, y - 1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
}

booleano EsColorSimilar(int r_1, int g_1, int b_1, int r_2, int g_2, int b_2)
{
  return abs(r_1 - r_2) <= TOLERANCIA &&
         abs(g_1 - g_2) <= TOLERANCIA &&
         abs(b_1 - b_2) <= TOLERANCIA;
}