/*
================================================================================
TablaHash.h
Versión: 1.2
Fecha: Mayo 2025
Autor: Coyol Moreno Angel Zoe | Ramos Mendoza Miguel Angel | Ramirez Hernandez Christian Isaac

Descripción:
------------
Este archivo contiene las declaraciones de funciones definidas en
"TablaHash.c"

================================================================================
*/
#include <stdio.h>
#include "TAD Lista DL/TADListaDL.h"

#define TAM_TABLA 499

typedef struct
{
    lista *listas[TAM_TABLA];
} tablaHash;

// Inicializa la tabla hash.
void Initialize_TH(tablaHash *t);

// Inserta un elemento en la tabla hash.
void Insert_TH(tablaHash *t, elemento e);

// Busca un elemento por clave y lo retorna.
elemento Search_TH(tablaHash *t, char *clave);

// Devuelve el número de colisiones en la lista i.
int Collisions_TH(tablaHash *t, int i);

// Elimina un elemento de la tabla hash.
void Delete_TH(tablaHash *t, elemento e);

// Reemplaza un elemento existente por uno nuevo.
void Replace_TH(tablaHash *t, elemento new, elemento old);

// Libera la memoria de la tabla hash.
void Destroy_TH(tablaHash *t);

// Indica si la lista en la posición i está vacía.
boolean EmptyIndex_TH(tablaHash *t, int i);

// Verifica si un elemento existe en la tabla hash.
boolean Exists_TH(tablaHash *t, elemento e);

// Devuelve un puntero a la lista en la posición i.
lista *getLista(tablaHash *t, int i);

// Calculan el índice hash de una clave.
int Hash(char *clave);
int Hash2(char *clave);
int Hash3(char *clave);

// Devuelve la posición de un elemento en su lista.
int Posicion(tablaHash *t, elemento e);

// Imprime los elementos de la lista correspondiente al elemento dado.
void VerListadeElemnto(tablaHash *t, elemento e);