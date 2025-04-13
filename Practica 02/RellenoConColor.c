//RellenoConColor.c
//Compilacion: gcc -o Relleno.exe RellenoConColor.c BMP.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BMP.h"

#define IMAGEN_TRATADA "tratada.bmp"

typedef int booleano;  
#define true 1
#define false 0

typedef struct {
    int x;
    int y;
} Punto;

void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

void RellenoConColorRGB_Iterativo(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y,
        int r_orig, int g_orig, int b_orig,
        int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto);

booleano EsColorSimilar(int r1, int g1, int b1, int r2, int g2, int b2);


int main (int argc, char* argv[]) {	
    BMP img;
    char IMAGEN[45];
    int r_o, g_o, b_o, x, y, r_n, g_n, b_n;
    clock_t t_inicio, t_final;
    double t_intervalo;

    if (argc != 7) {
        printf("\n[!]--- Error: Numero incorrecto de argumentos.\n");
        printf("Uso: %s (x,y) (R,G,B) imagen.bmp\n", argv[0]);
        printf("Ejemplo: %s 10 20 255 0 0 imagen.bmp\n", argv[0]);
        printf("Donde:\n");
        printf("  (x,y) son las coordenadas de la imagen a cambiar\n");
        printf("  (R,G,B) son los valores del nuevo color\n");
        printf("  imagen.bmp es el nombre de la imagen a procesar\n");
        exit(1);
    }
    
    x = atoi(argv[1]);
    y = atoi(argv[2]);
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
    
    r_o = img.pixelR[y][x];
    g_o = img.pixelG[y][x];
    b_o = img.pixelB[y][x];            
    t_inicio = clock();

    // if (r_o != r_n || g_o != g_n || b_o != b_n) {
    //     RellenoConColorRGB(img.pixelR, img.pixelG, img.pixelB,
    //         x, y,
    //         r_o, g_o, b_o,
    //         r_n, g_n, b_n,
    //         img.ancho, img.alto);
    //     }

    if (r_o != r_n || g_o != g_n || b_o != b_n) {
        RellenoConColorRGB_Iterativo(img.pixelR, img.pixelG, img.pixelB,
            x, y,
            r_o, g_o, b_o,
            r_n, g_n, b_n,
            img.ancho, img.alto);
        }
    t_final = clock();
    
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("Tiempo medido: %.8f segundos.\n", t_intervalo);
    
    crear_imagen(&img, IMAGEN_TRATADA);
    printf("Imagen tratada guardada en: %s\n", IMAGEN_TRATADA);
    
    return 0;
}

void RellenoConColorRGB_Iterativo(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y,
    int r_orig, int g_orig, int b_orig,
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
    if (x < 0 || x >= ancho || y < 0 || y >= alto)
        return;

    if (R[x][y] == r_nuevo && G[x][y] == g_nuevo && B[x][y] == b_nuevo)
        return;

    // Verificación de memoria para la cola
    Punto* cola = malloc(ancho * alto * sizeof(Punto));
    if (cola == NULL) {
        printf("Error: No se pudo asignar memoria para la cola.\n");
        return;
    }

    // Crear matriz auxiliar para marcar píxeles visitados
    booleano** visitado = malloc(alto * sizeof(booleano*));
    for (int i = 0; i < alto; i++) {
        visitado[i] = calloc(ancho, sizeof(booleano));
    }

    int inicio = 0, fin = 0;
    cola[fin++] = (Punto){x, y};  // Comenzamos en el punto (x, y)
    visitado[y][x] = true;        // Marcar como visitado

    printf("Iniciando relleno desde (%d, %d)...\n", x, y);  // Debug de inicio

    while (inicio < fin) {
        Punto p = cola[inicio++];
        int px = p.x;
        int py = p.y;

        // Pintamos el píxel
        R[py][px] = r_nuevo;
        G[py][px] = g_nuevo;
        B[py][px] = b_nuevo;

        // Agregar vecinos (derecha, izquierda, abajo, arriba)
        if (px + 1 < ancho && !visitado[py][px + 1] &&
            EsColorSimilar(R[py][px + 1], G[py][px + 1], B[py][px + 1], r_orig, g_orig, b_orig)) {
            cola[fin++] = (Punto){px + 1, py};
            visitado[py][px + 1] = true;
        }
        if (px - 1 >= 0 && !visitado[py][px - 1] &&
            EsColorSimilar(R[py][px - 1], G[py][px - 1], B[py][px - 1], r_orig, g_orig, b_orig)) {
            cola[fin++] = (Punto){px - 1, py};
            visitado[py][px - 1] = true;
        }
        if (py + 1 < alto && !visitado[py + 1][px] &&
            EsColorSimilar(R[py + 1][px], G[py + 1][px], B[py + 1][px], r_orig, g_orig, b_orig)) {
            cola[fin++] = (Punto){px, py + 1};
            visitado[py + 1][px] = true;
        }
        if (py - 1 >= 0 && !visitado[py - 1][px] &&
            EsColorSimilar(R[py - 1][px], G[py - 1][px], B[py - 1][px], r_orig, g_orig, b_orig)) {
            cola[fin++] = (Punto){px, py - 1};
            visitado[py - 1][px] = true;
        }

        // Verificar si la cola se desborda
        if (fin >= ancho * alto) {
            printf("Error: La cola se desbordó.\n");
            break;
        }
    }

    // Liberar memoria
    free(cola);
    for (int i = 0; i < alto; i++) {
        free(visitado[i]);
    }
    free(visitado);

    printf("Relleno completado. Ahora guardando la imagen...\n");  // Debug de fin
}

void RellenoConColorRGB(unsigned char** R, unsigned char** G, unsigned char** B, int x, int y, 
    int r_orig, int g_orig, int b_orig, 
    int r_nuevo, int g_nuevo, int b_nuevo, int ancho, int alto)
{
double aproxR,aproxG,aproxB;
if(x < 0 || x >= ancho || y < 0 || y >= alto)
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


booleano EsColorSimilar(int r1, int g1, int b1, int r2, int g2, int b2) {
    int tolerancia = 20;  

    if (abs(r1 - r2) <= tolerancia && abs(g1 - g2) <= tolerancia && abs(b1 - b2) <= tolerancia)
        return true;
    else
        return false;
}
