// Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac 2025
#ifndef __TAD_ARBOL_BIN_BUSQUEDA_DICC
#define __TAD_ARBOL_BIN_BUSQUEDA_DICC
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef char booleano;

typedef struct elemento
{
    char d[1024];
    // Lo que el usuario guste
} elemento;

typedef struct nodo
{
    char clave[101];
    elemento e;
    struct nodo *left;
    struct nodo *right;
} nodo;

typedef nodo *arbol_bin_busqueda;

typedef nodo *posicion;

void Initialize_ABB(arbol_bin_busqueda *A);
void Destroy_ABB(arbol_bin_busqueda *A);
void Insert_ABB(arbol_bin_busqueda *A, char *clave, elemento e);
posicion Search_ABB(arbol_bin_busqueda *A, char *clave);
posicion Search_ABB_recursiva(arbol_bin_busqueda *A, char *clave, int *contador);
booleano Empty_ABB(arbol_bin_busqueda *A);
elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p);
booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p);
void Modify_ABB(arbol_bin_busqueda *A, char *clave, elemento new);
void Delete_ABB(arbol_bin_busqueda *A, char *clave);
void Delete_ABB_recursivo(arbol_bin_busqueda *A, char *clave, int *contador, int imprimir);
void RecorridoPreOrden(arbol_bin_busqueda *A);
void RecorridoInOrden(arbol_bin_busqueda *A);
void RecorridoPosOrden(arbol_bin_busqueda *A);
int Depth_ABB(arbol_bin_busqueda *a);
int NodeCount_ABB(arbol_bin_busqueda *a);
posicion DeepestNode_ABB(arbol_bin_busqueda *a);
void DeepestNode_ABB_recursivo(arbol_bin_busqueda *a, int nivelActual, int *nivelMax, posicion *masProfundo);
char *GetKey_ABB(arbol_bin_busqueda *a, posicion p);

#endif //__TAD_ARBOL_BIN_BUSQUEDA_DICC