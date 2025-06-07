#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TablaHash.h"

void Initialize_TH(tablaHash *t)
{
    int i;

    for (i = 0; i < TAM_TABLA; i++)
    {
        t->listas[i] = malloc(sizeof(lista));
        Initialize(t->listas[i]);
    }
    return;
}

void Insert_TH(tablaHash *t, elemento e)
{
    int indice;
    indice = Hash(e.p);

    Add(t->listas[indice], e);

    return;
}

boolean Exists_TH(tablaHash *t, elemento e)
{
    int indice;
    posicion p;
    indice = Hash(e.p);

    p = Search(t->listas[indice], e);
    if (ValidatePosition(t, p))
        return TRUE;

    return FALSE;
}

elemento Search_TH(tablaHash *t, char *clave)
{
    int indice;
    posicion p;
    elemento aux, enull;

    enull.p[0] = '\0';
    indice = Hash(clave);

    p = First(t->listas[indice]);

    while (p != NULL)
    {
        aux = Position(t->listas[indice], p);
        if (strcmp(aux.p, clave) == 0)
            return aux;

        p = Following(t->listas[indice], p);
    }

    return enull;
}

void Delete_TH(tablaHash *t, elemento e)
{
    posicion p;
    int indice;

    indice = Hash(e.p);
    p = Search(t->listas[indice], e);

    if (ValidatePosition(t->listas[indice], p))
        Remove(t->listas[indice], p);

    return;
}

void Replace_TH(tablaHash *t, elemento new, elemento old)
{
    posicion p;
    int indice;

    indice = Hash(old.p);
    p = Search(t->listas[indice], old);

    if (ValidatePosition(t->listas[indice], p))
        Replace(t->listas[indice], p, new);

    return;
}

void Destroy_TH(tablaHash *t)
{
    int i;
    for (i = 0; i < TAM_TABLA; i++)
    {
        Destroy(t->listas[i]);
        free(t->listas[i]);
    }

    return;
}

int Collisions_TH(tablaHash *t, int i)
{
    int size;

    size = Size(t->listas[i]);

    return size == 0 ? size : size - 1;
}

int Hash(char *clave)
{
    int sum = 0, i = 0;
    while (clave[i] != '\0')
    {
        sum += clave[i];
        i++;
    }
    sum %= TAM_TABLA; // sum = sum % TAM_TABLA;

    return sum;
}

boolean EmptyIndex_TH(tablaHash *t, int i)
{
    if (!Size(t->listas[i]))
        return TRUE;

    return FALSE;
}