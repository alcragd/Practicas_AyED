#include <stdio.h>
#include "TAD Lista DL/TADListaDL.h"

#define TAM_TABLA 101

typedef struct
{
    lista *listas[TAM_TABLA];
} tablaHash;

void Initialize_TH(tablaHash *t);

void Insert_TH(tablaHash *t, elemento e);

elemento Search_TH(tablaHash *t, char *clave);

int Collisions_TH(tablaHash *t, elemento e);

void Delete_TH(tablaHash *t, elemento e);

void Replace_TH(tablaHash *t, elemento new, elemento old);

void Destroy_TH(tablaHash *t);

int Hash(char *clave);