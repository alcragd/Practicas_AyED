#include <stdio.h>
#include "TAD Lista DL/TADListaDL.h"

#define TAM_TABLA 499

typedef struct
{
    lista *listas[TAM_TABLA];
} tablaHash;

void Initialize_TH(tablaHash *t);

void Insert_TH(tablaHash *t, elemento e);

elemento Search_TH(tablaHash *t, char *clave);

int Collisions_TH(tablaHash *t, int i);

void Delete_TH(tablaHash *t, elemento e);

void Replace_TH(tablaHash *t, elemento new, elemento old);

void Destroy_TH(tablaHash *t);

boolean EmptyIndex_TH(tablaHash *t, int i);

boolean Exists_TH(tablaHash *t, elemento e);

lista *getLista(tablaHash *t, int i);

int Hash(char *clave);

int Posicion(tablaHash *t, elemento e);

void VerListadeElemnto(tablaHash *t, elemento e);