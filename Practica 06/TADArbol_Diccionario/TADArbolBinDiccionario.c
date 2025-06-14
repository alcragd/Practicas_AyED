#include "TADArbolBinDiccionario.h"
#include <string.h>
#include <stdlib.h>

void Initialize_ABB(arbol_bin_busqueda *A)
{
    *A = NULL;
    return;
}

void Insert_ABB(arbol_bin_busqueda *A, char *clave, elemento e)
{
    nodo *newNode;
    int cmp;

    newNode = malloc(sizeof(nodo));
    if (newNode == NULL)
    {
        printf("\nInsert_ABB(A,e): ERROR Desbordamiento de Arbol.");
        exit(1);
    }

    strcpy(newNode->clave, clave);
    newNode->e = e;
    newNode->left = NULL;
    newNode->right = NULL;

    if (Empty_ABB(&(*A)))
        *A = newNode;
    else
    {
        cmp = strcmp(clave, (*A)->clave);
        if (cmp < 0)
            (*A)->left = newNode;
        else if (cmp > 0)
            (*A)->right = newNode;
        else
        {
            printf("\nInsert_ABB(A,e): La clave '%s' ya existe.", clave);
        }
    }
    return;
}

boolean Empty_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return TRUE;
    return FALSE;
}

posicion Search_ABB(arbol_bin_busqueda *A, char *clave)
{
    int comp;
    posicion p = NULL;
    comp = strcmp(clave, (*A)->clave);

    if (comp < 0)
        p = Search_ABB(&((*A)->left), clave);
    else if (comp > 0)
        p = Search_ABB(&((*A)->right), clave);

    return p;
}

elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p)
{
    if (!NullNode(A, p))
        return p->e;
    else
    {
        printf("\nReadNode_ABB(A,e): ERROR Posición Invalida.");
        exit(1);
    }
}

boolean NullNode_ABB(arbol_bin_busqueda *A, posicion p)
{
    boolean b = TRUE;
    if (*A == NULL || p == NULL)
        return TRUE;
    if (*A == p)
        return FALSE;
    if ((*A)->left != NULL)
        b = NullNode(&((*A)->left), p);
    if ((*A)->right != NULL && b)
        b = NullNode(&((*A)->right), p);

    return b;
}

void Destroy_ABB(arbol_bin_busqueda *A)
{
    if ((*A)->left == NULL && (*A)->right == NULL)
        free(*A);
    else
    {
        if ((*A)->left != NULL)
            Destroy_ABB(&((*A)->left));
        if ((*A)->right != NULL)
            Destroy_ABB(&((*A)->right));
    }
    return;
}