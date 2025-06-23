/*
================================================================================
TADArbolBinDiccionario.h
Versión: 1.0
Fecha: Junio 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
------------
Este archivo contiene las declaraciones de funciones y estructuras para el manejo
de un Árbol Binario de Búsqueda (ABB) orientado a diccionarios de palabras y
definiciones. Permite inicializar, insertar, buscar, modificar, eliminar y recorrer
el árbol, así como obtener estadísticas como altura, cantidad de nodos y el nodo
más profundo.

================================================================================
*/

#ifndef __TAD_ARBOL_BIN_BUSQUEDA_DICC
#define __TAD_ARBOL_BIN_BUSQUEDA_DICC
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef char booleano;

// Estructura para almacenar la definición de una palabra.
typedef struct elemento
{
    char d[1024]; // Definición de la palabra
    // Puedes agregar más campos si lo deseas
} elemento;

// Nodo del árbol binario de búsqueda.
typedef struct nodo
{
    char clave[101];    // Palabra clave
    elemento e;         // Definición asociada
    struct nodo *left;  // Hijo izquierdo
    struct nodo *right; // Hijo derecho
} nodo;

typedef nodo *arbol_bin_busqueda; // Puntero al árbol
typedef nodo *posicion;           // Puntero a un nodo (posición)

/*
================================================================================
void Initialize_ABB(arbol_bin_busqueda *A)
Inicializa el árbol binario de búsqueda, dejándolo vacío.
================================================================================
*/
void Initialize_ABB(arbol_bin_busqueda *A);

/*
================================================================================
void Destroy_ABB(arbol_bin_busqueda *A)
Libera toda la memoria utilizada por el árbol binario de búsqueda.
================================================================================
*/
void Destroy_ABB(arbol_bin_busqueda *A);

/*
================================================================================
void Insert_ABB(arbol_bin_busqueda *A, char *clave, elemento e)
Inserta un elemento en el árbol según la clave dada.
================================================================================
*/
void Insert_ABB(arbol_bin_busqueda *A, char *clave, elemento e);

/*
================================================================================
posicion Search_ABB(arbol_bin_busqueda *A, char *clave)
Busca un nodo en el árbol usando la clave dada.
================================================================================
*/
posicion Search_ABB(arbol_bin_busqueda *A, char *clave);

/*
================================================================================
posicion Search_ABB_recursiva(arbol_bin_busqueda *A, char *clave, int *contador)
Función recursiva interna para buscar un nodo por clave y contar comparaciones.
================================================================================
*/
posicion Search_ABB_recursiva(arbol_bin_busqueda *A, char *clave, int *contador);

/*
================================================================================
booleano Empty_ABB(arbol_bin_busqueda *A)
Verifica si el árbol está vacío.
================================================================================
*/
booleano Empty_ABB(arbol_bin_busqueda *A);

/*
================================================================================
elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p)
Devuelve el elemento almacenado en la posición dada del árbol.
================================================================================
*/
elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p);

/*
================================================================================
booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p)
Verifica si una posición es nula o inválida en el árbol.
================================================================================
*/
booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p);

/*
================================================================================
void Modify_ABB(arbol_bin_busqueda *A, char *clave, elemento new)
Modifica el elemento asociado a una clave existente en el árbol.
================================================================================
*/
void Modify_ABB(arbol_bin_busqueda *A, char *clave, elemento new);

/*
================================================================================
void Delete_ABB(arbol_bin_busqueda *A, char *clave)
Elimina un nodo del árbol según la clave dada.
================================================================================
*/
void Delete_ABB(arbol_bin_busqueda *A, char *clave);

/*
================================================================================
void Delete_ABB_recursivo(arbol_bin_busqueda *A, char *clave, int *contador, int imprimir)
Función recursiva interna para eliminar un nodo por clave y contar comparaciones.
================================================================================
*/
void Delete_ABB_recursivo(arbol_bin_busqueda *A, char *clave, int *contador, int imprimir);

/*
================================================================================
void RecorridoPreOrden(arbol_bin_busqueda *A)
Imprime el recorrido PreOrden del árbol.
================================================================================
*/
void RecorridoPreOrden(arbol_bin_busqueda *A);

/*
================================================================================
void RecorridoInOrden(arbol_bin_busqueda *A)
Imprime el recorrido InOrden (alfabético) del árbol.
================================================================================
*/
void RecorridoInOrden(arbol_bin_busqueda *A);

/*
================================================================================
void RecorridoPosOrden(arbol_bin_busqueda *A)
Imprime el recorrido PosOrden del árbol.
================================================================================
*/
void RecorridoPosOrden(arbol_bin_busqueda *A);

/*
================================================================================
int Depth_ABB(arbol_bin_busqueda *a)
Calcula la altura (profundidad máxima) del árbol.
================================================================================
*/
int Depth_ABB(arbol_bin_busqueda *a);

/*
================================================================================
int NodeCount_ABB(arbol_bin_busqueda *a)
Cuenta el número total de nodos en el árbol.
================================================================================
*/
int NodeCount_ABB(arbol_bin_busqueda *a);

/*
================================================================================
posicion DeepestNode_ABB(arbol_bin_busqueda *a)
Obtiene la posición del nodo más profundo en el árbol.
================================================================================
*/
posicion DeepestNode_ABB(arbol_bin_busqueda *a);

/*
================================================================================
void DeepestNode_ABB_recursivo(arbol_bin_busqueda *a, int nivelActual, int *nivelMax, posicion *masProfundo)
Función recursiva interna para encontrar el nodo más profundo del árbol.
================================================================================
*/
void DeepestNode_ABB_recursivo(arbol_bin_busqueda *a, int nivelActual, int *nivelMax, posicion *masProfundo);

/*
================================================================================
char *GetKey_ABB(arbol_bin_busqueda *a, posicion p)
Devuelve la clave (palabra) almacenada en la posición dada del árbol.
================================================================================
*/
char *GetKey_ABB(arbol_bin_busqueda *a, posicion p);

#endif //__TAD_ARBOL_BIN_BUSQUEDA_DICC