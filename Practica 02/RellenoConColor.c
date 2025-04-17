/*
================================================================================
RellenoConColor.c
Versión: 2.1
Fecha: Abril 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
-----------
Este programa implementa un algoritmo de relleno de color en imágenes BMP 
utilizando dos enfoques: recursivo y iterativo. El objetivo es cambiar el color 
de una región conectada de píxeles que comparten un color similar al inicial.

El programa utiliza una matriz de píxeles RGB para representar la imagen y 
permite al usuario especificar las coordenadas iniciales y el nuevo color.

Compilación:
------------
Windows: gcc -o Relleno.exe RellenoConColor.c BMP.c pila_din.c
Linux/Mac: gcc -o Relleno RellenoConColor.c BMP.c pila_din.c

Uso:
----
./Relleno.exe x y R G B imagen.bmp

Donde:
  - x, y son las coordenadas iniciales del píxel a cambiar.
  - R, G, B son los valores del nuevo color.
  - imagen.bmp es el nombre de la imagen BMP a procesar.

Salida:
-------
El programa genera una nueva imagen BMP con el nombre `tratada.bmp`, donde 
la región conectada al píxel inicial ha sido rellenada con el nuevo color.

Observaciones:
--------------
- El algoritmo recursivo desborda la pila con imagenes grandes.
- Se implementó un algoritmo iterativo que utiliza una pika para evitar el desbordamiento de pila.
- Se define una tolerancia de color de la imagen en la función EsColorSimilar()
    lo que permite pintar colores similares
- Pueden haber problemas en imagenes rectangulares debido a limitaciones de BMP.c/BMP.h
- Funciona perfectamente en imagenes cuadradas
================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BMP.h"
#include "pila_din.h"

#define IMAGEN_TRATADA "tratada.bmp"
#define TOLERANCIA 20

typedef int booleano;  
#define true 1
#define false 0

typedef elemento coordenada;

void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

void RellenoConColorRGB_Iterativo(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y,
        int r_orig, int g_orig, int b_orig,
        int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

booleano EsColorSimilar(int r_1, int g_1, int b_1, int r_2, int g_2, int b_2);


int main (int argc, char* argv[]) {	
  BMP img;
  char IMAGEN[45];
  int r_o, g_o, b_o, x, y, r_n, g_n, b_n;
  clock_t t_inicio, t_final;
  double t_intervalo;

  if (argc != 7) {
    printf("\n[!]--- Error: Numero incorrecto de argumentos.\n");
    printf("Uso: %s x y R G B imagen.bmp\n", argv[0]);
    printf("Donde:\n");
    printf("  (x,y) son las coordenadas de la imagen a cambiar\n");
    printf("  (R,G,B) son los valores del nuevo color\n");
    printf("  imagen.bmp es el nombre de la imagen a procesar\n");
    exit(1);
    }
    
  y = atoi(argv[1]); // fila
  x = atoi(argv[2]); // columna
  r_n = atoi(argv[3]);
  g_n = atoi(argv[4]);
  b_n = atoi(argv[5]);
  strcpy(IMAGEN, argv[6]);
   

  abrir_imagen(&img, IMAGEN);
  printf("Dimensiones: Alto=%d, Ancho=%d\n", img.alto, img.ancho);
    
    
  // printf("Coordenadas de inicio (x y): ");
  // scanf("%d %d", &x, &y);
    
  // printf("Color nuevo RGB (r g b): ");
  // scanf("%d %d %d", &r_n, &g_n, &b_n);
    
  r_o = img.pixelR[x][y];
  g_o = img.pixelG[x][y];
  b_o = img.pixelB[x][y];            
  t_inicio = clock();

    
  // RellenoConColorRGB(img.pixelR, img.pixelG, img.pixelB,
  //   x, y,
  //   r_o, g_o, b_o,
  //   r_n, g_n, b_n,
  //   img.ancho, img.alto);
    

  RellenoConColorRGB_Iterativo(img.pixelR, img.pixelG, img.pixelB,
      x, y,
      r_o, g_o, b_o,
      r_n, g_n, b_n,
      img.ancho, img.alto); 

  t_final = clock();
    
  t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
  printf("Tiempo medido: %.8f segundos.\n", t_intervalo);
    
  crear_imagen(&img, IMAGEN_TRATADA);
  printf("Imagen tratada guardada en: %s\n", IMAGEN_TRATADA);
    
  return 0;
}



/*
--------------------------------------------------------------------------------
void RellenoConColorRGB_Iterativo(unsigned char** R, unsigned char** G, 
                                  unsigned char** B, int x, int y,
                                  int r_orig, int g_orig, int b_orig,
                                  int r_nuevo, int g_nuevo, int b_nuevo, 
                                  int ancho, int alto)
--------------------------------------------------------------------------------
Descripción:
  Implementa un algoritmo de relleno de color iterativo utilizando una pila 
  para procesar los píxeles. Cambia el color de una región conectada de píxeles 
  que comparten un color similar al inicial.

Recibe:
  - `R`, `G`, `B`: Matrices de los canales de color de la imagen.
  - `x`, `y`: Coordenadas iniciales del píxel a cambiar.
  - `r_orig`, `g_orig`, `b_orig`: Color original de la región.
  - `r_nuevo`, `g_nuevo`, `b_nuevo`: Nuevo color para la región.
  - `ancho`, `alto`: Dimensiones de la imagen.

Devuelve:
  - Nada. Modifica directamente las matrices de la imagen.

Observaciones:
  - Utiliza una pila dinámica para evitar desbordamientos de pila.
  
  
*/
void RellenoConColorRGB_Iterativo(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y,
  int r_orig, int g_orig, int b_orig,
  int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
  if (x < 0 || x >= alto || y < 0 || y >= ancho)
      return;

  if (R[x][y] == r_nuevo && G[x][y] == g_nuevo && B[x][y] == b_nuevo)
      return;

  
  pila rastro; 
  Initialize(&rastro);

  // Pintar el píxel inicial y marcarlo como visitado
  R[x][y] = r_nuevo;
  G[x][y] = g_nuevo;
  B[x][y] = b_nuevo;
  

  Push(&rastro, (coordenada){x, y});

  while (!Empty(&rastro)) {
      coordenada coord = Pop(&rastro);
      int cx = coord.x;
      int cy = coord.y;

      // Procesar vecinos
      if (cx + 1 < alto && EsColorSimilar(R[cx + 1][cy], G[cx + 1][cy], B[cx + 1][cy], r_orig, g_orig, b_orig)) {
          R[cx + 1][cy] = r_nuevo;
          G[cx + 1][cy] = g_nuevo;
          B[cx + 1][cy] = b_nuevo;
          
          Push(&rastro, (coordenada){cx + 1, cy});
      }
      if (cx - 1 >= 0 && EsColorSimilar(R[cx - 1][cy], G[cx - 1][cy], B[cx - 1][cy], r_orig, g_orig, b_orig)) {
          R[cx - 1][cy] = r_nuevo;
          G[cx - 1][cy] = g_nuevo;
          B[cx - 1][cy] = b_nuevo;
          
          Push(&rastro, (coordenada){cx - 1, cy});
      }
      if (cy + 1 < ancho && EsColorSimilar(R[cx][cy + 1], G[cx][cy + 1], B[cx][cy + 1], r_orig, g_orig, b_orig)) {
          R[cx][cy + 1] = r_nuevo;
          G[cx][cy + 1] = g_nuevo;
          B[cx][cy + 1] = b_nuevo;
          
          Push(&rastro, (coordenada){cx, cy + 1});
      }
      if (cy - 1 >= 0 && EsColorSimilar(R[cx][cy - 1], G[cx][cy - 1], B[cx][cy - 1], r_orig, g_orig, b_orig)) {
          R[cx][cy - 1] = r_nuevo;
          G[cx][cy - 1] = g_nuevo;
          B[cx][cy - 1] = b_nuevo;
          
          Push(&rastro, (coordenada){cx, cy - 1});
      }
  }

  // Liberar memoria
  Destroy(&rastro);
  
}


/*
--------------------------------------------------------------------------------
void RellenoConColorRGB(unsigned char** R, unsigned char** G, 
                        unsigned char** B, int x, int y,
                        int r_orig, int g_orig, int b_orig,
                        int r_nuevo, int g_nuevo, int b_nuevo, 
                        int ancho, int alto)
--------------------------------------------------------------------------------
Descripción:
  Implementa un algoritmo de relleno de color recursivo. Cambia el color de una 
  región conectada de píxeles que comparten un color similar al inicial.

Recibe:
  - `R`, `G`, `B`: Matrices de los canales de color de la imagen.
  - `x`, `y`: Coordenadas iniciales del píxel a cambiar.
  - `r_orig`, `g_orig`, `b_orig`: Color original de la región.
  - `r_nuevo`, `g_nuevo`, `b_nuevo`: Nuevo color para la región.
  - `ancho`, `alto`: Dimensiones de la imagen.

Devuelve:
  - Nada. Modifica directamente las matrices de la imagen.

Observaciones:
  - Puede causar desbordamiento de pila si la región a rellenar es grande.

*/
void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
    if(x < 0 || x >= alto || y < 0 || y >= ancho)
    return;
    if (R[x][y] == r_nuevo && G[x][y] == g_nuevo && B[x][y] == b_nuevo)
      return;

    if(!EsColorSimilar(R[x][y], G[x][y], B[x][y], r_orig, g_orig, b_orig))
    return;
    // if(R[x][y] != r_orig || G[x][y] != g_orig || B[x][y] != b_orig)
    // return;


    R[x][y] = r_nuevo;
    G[x][y] = g_nuevo;
    B[x][y] = b_nuevo;

    RellenoConColorRGB(R, G, B, x+1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
    RellenoConColorRGB(R, G, B, x-1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
    RellenoConColorRGB(R, G, B, x, y+1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
    RellenoConColorRGB(R, G, B, x, y-1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
    }


/*
--------------------------------------------------------------------------------
booleano EsColorSimilar(int r1, int g1, int b1, int r2, int g2, int b2)
--------------------------------------------------------------------------------
Descripción:
  Compara dos colores RGB y determina si son similares dentro de una tolerancia 
  predefinida.

Recibe:
  - `r_1`, `g_1`, `b_1`: Primer color a comparar.
  - `r_2`, `g_2`, `b_2`: Segundo color a comparar.

Devuelve:
  - `true` si los colores son similares, `false` en caso contrario.

Observaciones:
  - La tolerancia está definida por la constante TOLERANCIA para no tener que buscar en todo
  el codigo para cambiarla.

*/
booleano EsColorSimilar(int r_1, int g_1, int b_1, int r_2, int g_2, int b_2) {
  if (abs(r_1 - r_2) <= TOLERANCIA && abs(g_1 - g_2) <= TOLERANCIA && abs(b_1 - b_2) <= TOLERANCIA)
      return true;
  else
      return false;
}
