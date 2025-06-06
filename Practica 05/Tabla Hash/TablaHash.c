#include <stdio.h>
#include "TablaHash.h"

void Initialize_TH(tablaHash *t)
{
    int i;
    for (i = 0; i < TAM_TABLA; i++)
        Initialize(t->listas[i]);

    return;
}

void Insert_TH(tablaHash *t, elemento e)
{
    int indice;
    indice = Hash(e.p);

    Add(t->listas[indice], e);

    return;
}