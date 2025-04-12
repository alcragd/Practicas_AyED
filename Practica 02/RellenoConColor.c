//RellenoConColor.c
//Compilacion: gcc -o Relleno.exe RellenoConColor.c BMP.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BMP.h"

#define IMAGEN_TRATADA "tratada.bmp"

void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);


    

int main (int argc, char* argv[]) {	
    BMP img;
    char IMAGEN[45];
    if (argc != 2) {
        printf("\nUso: %s imagen.bmp\n", argv[0]);
        exit(1);
    }
    strcpy(IMAGEN, argv[1]);

    abrir_imagen(&img, IMAGEN);
    printf("Dimensiones: Alto=%d, Ancho=%d\n", img.alto, img.ancho);
    
    int x, y, r_n, g_n, b_n;
    printf("Coordenadas de inicio (x y): ");
    scanf("%d %d", &x, &y);
    
    printf("Color nuevo RGB (r g b): ");
    scanf("%d %d %d", &r_n, &g_n, &b_n);
    
    int r_o = img.pixelR[y][x];
    int g_o = img.pixelG[y][x];
    int b_o = img.pixelB[y][x];
    
    clock_t t_inicio = clock();
    if (r_o != r_n || g_o != g_n || b_o != b_n) {
        RellenoConColorRGB(img.pixelR, img.pixelG, img.pixelB,
            x, y,
            r_o, g_o, b_o,
            r_n, g_n, b_n,
            img.ancho, img.alto);
        }
    clock_t t_final = clock();
    
    double t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("Tiempo medido: %.8f segundos.\n", t_intervalo);
    
    crear_imagen(&img, IMAGEN_TRATADA);
    printf("Imagen tratada guardada en: %s\n", IMAGEN_TRATADA);
    
    return 0;
}


void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
if(x < 0 || x >= ancho || y < 0 || y >= alto)
return;

if(R[y][x] != r_orig || G[y][x] != g_orig || B[y][x] != b_orig)
return;

R[y][x] = r_nuevo;
G[y][x] = g_nuevo;
B[y][x] = b_nuevo;

RellenoConColorRGB(R, G, B, x+1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
RellenoConColorRGB(R, G, B, x-1, y, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
RellenoConColorRGB(R, G, B, x, y+1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
RellenoConColorRGB(R, G, B, x, y-1, r_orig, g_orig, b_orig, r_nuevo, g_nuevo, b_nuevo, ancho, alto);
}
