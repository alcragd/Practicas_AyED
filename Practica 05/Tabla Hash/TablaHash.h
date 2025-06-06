#include <stdio.h>
#include "TAD Lista DL/TADListaDL.h"

#define TAM_TABLA 101

typedef struct
{
    lista *listas[TAM_TABLA];
} tablaHash;

void Initialize_TH(tablaHash *t);

void Insert_TH(tablaHash *t, elemento e);

int Search_TH(tablaHash *t, elemento e);

void Delete_TH(tablaHash *t, elemento e);

void Replace_TH(tablaHash *t, int i, elemento e);

void Destroy_TH(tablaHash *t);

int Hash(char clave);