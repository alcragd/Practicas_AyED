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

    if (Empty_ABB(&(*A)))
    {
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
        *A = newNode;
    }
    else
    {
        cmp = strcmp(clave, (*A)->clave);
        if (cmp < 0)
            Insert_ABB(&((*A)->left), clave, e);
        else if (cmp > 0)
            Insert_ABB(&((*A)->right), clave, e);
        else
        {
            printf("\nInsert_ABB(A,e): La clave '%s' ya existe.", clave);
        }
    }
    return;
}

booleano Empty_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return TRUE;
    return FALSE;
}

// Función recursiva interna
posicion Search_ABB_recursiva(arbol_bin_busqueda *A, char *clave, int *contador)
{
    if (*A == NULL)
    {
        printf("\nSearch(A,c): Valor no encontrado");
        return NULL;
    }

    int comp = strcmp(clave, (*A)->clave);
    (*contador)++;

    if (comp < 0)
        return Search_ABB_recursiva(&((*A)->left), clave, contador);
    else if (comp > 0)
        return Search_ABB_recursiva(&((*A)->right), clave, contador);
    else
    {
        printf("\nSearch(A,c): Valor encontrado");
        printf("\nNumero de comparaciones: %d", *contador);
        return *A;
    }
}

posicion Search_ABB(arbol_bin_busqueda *A, char *clave)
{
    int contador = 0;
    return Search_ABB_recursiva(A, clave, &contador);
}

elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p)
{
    if (!NullNode_ABB(A, p))
        return p->e;
    else
    {
        printf("\nReadNode_ABB(A,e): ERROR Posición Invalida.");
        exit(1);
    }
}

booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p)
{
    booleano b = TRUE;
    if (*A == NULL || p == NULL)
        return TRUE;
    if (*A == p)
        return FALSE;
    if ((*A)->left != NULL)
        b = NullNode_ABB(&((*A)->left), p);
    if ((*A)->right != NULL && b)
        b = NullNode_ABB(&((*A)->right), p);

    return b;
}

void Destroy_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return;
    Destroy_ABB(&((*A)->left));
    Destroy_ABB(&((*A)->right));
    free(*A);
    *A = NULL;
}

void Modify_ABB(arbol_bin_busqueda *A, char *clave, elemento new)
{
    posicion p = Search_ABB(A, clave);
    if (p == NULL)
    {
        printf("\nNo se encontró la clave \"%s\" a modificar.\n", clave);
    }
    else
    {
        p->e = new;
        printf("\nElemento modificado correctamente para la clave \"%s\".\n", clave);
    }
    return;
}

void Delete_ABB(arbol_bin_busqueda *A, char *clave)
{
    int contador = 0;
    Delete_ABB_recursivo(A, clave, &contador, 1);
}

void Delete_ABB_recursivo(arbol_bin_busqueda *A, char *clave, int *contador, int imprimir)
{
    if (*A == NULL)
    {
        if (imprimir)
            printf("\nNo se encontró la clave \"%s\" para eliminar.\n", clave);
        return;
    }

    int cmp = strcmp(clave, (*A)->clave);
    (*contador)++;

    if (cmp < 0)
        Delete_ABB_recursivo(&((*A)->left), clave, contador, imprimir);
    else if (cmp > 0)
        Delete_ABB_recursivo(&((*A)->right), clave, contador, imprimir);
    else
    {
        nodo *temp;
        if (imprimir)
        {
            printf("\nDelete(A,c): Valor encontrado");
            printf("\nNumero de comparaciones: %d", *contador);
        }
        if ((*A)->left == NULL && (*A)->right == NULL)
        {
            free(*A);
            *A = NULL;
        }
        else if ((*A)->left == NULL)
        {
            temp = *A;
            *A = (*A)->right;
            free(temp);
        }
        else if ((*A)->right == NULL)
        {
            temp = *A;
            *A = (*A)->left;
            free(temp);
        }
        else
        {
            nodo *succParent = *A;
            nodo *succ = (*A)->right;
            while (succ->left != NULL)
            {
                succParent = succ;
                succ = succ->left;
            }
            strcpy((*A)->clave, succ->clave);
            (*A)->e = succ->e;
            // Eliminar el sucesor sin imprimir
            if (succParent->left == succ)
                Delete_ABB_recursivo(&(succParent->left), succ->clave, contador, 0);
            else
                Delete_ABB_recursivo(&(succParent->right), succ->clave, contador, 0);
        }
    }
}

void RecorridoPreOrden(arbol_bin_busqueda *A)
{
    if (*A != NULL)
    {
        printf("%s:\n%s\n", (*A)->clave, (*A)->e.d);
        RecorridoPreOrden(&((*A)->left));
        RecorridoPreOrden(&((*A)->right));
    }
    return;
}
void RecorridoInOrden(arbol_bin_busqueda *A)
{
    if (*A != NULL)
    {
        RecorridoInOrden(&((*A)->left));
        printf("%s:\n%s\n", (*A)->clave, (*A)->e.d);
        RecorridoInOrden(&((*A)->right));
    }
    return;
}
void RecorridoPosOrden(arbol_bin_busqueda *A)
{
    if (*A != NULL)
    {
        RecorridoPosOrden(&((*A)->left));
        RecorridoPosOrden(&((*A)->right));
        printf("%s:\n%s\n", (*A)->clave, (*A)->e.d);
    }
    return;
}

int Depth_ABB(arbol_bin_busqueda *a)
{
    int depth_r, depth_l;
    if (*a == NULL)
        return 0;

    depth_r = Depth_ABB(&((*a)->right));
    depth_l = Depth_ABB(&((*a)->left));

    return (depth_r > depth_l ? depth_r : depth_l) + 1;
}

int NodeCount_ABB(arbol_bin_busqueda *a)
{
    if (*a == NULL)
        return 0;
    else
        return (1 + NodeCount_ABB(&(*a)->left) + NodeCount_ABB(&(*a)->right));
}

posicion DeepestNode_ABB(arbol_bin_busqueda *a)
{
    int nivelMax = -1;
    posicion masProfundo = NULL;
    DeepestNode_ABB_recursivo(a, 0, &nivelMax, &masProfundo);
    return masProfundo;
}

void DeepestNode_ABB_recursivo(arbol_bin_busqueda *a, int nivelActual, int *nivelMax, posicion *masProfundo)
{
    if (*a == NULL)
        return;

    if (nivelActual > *nivelMax)
    {
        *nivelMax = nivelActual;
        *masProfundo = *a;
    }

    DeepestNode_ABB_recursivo(&((*a)->left), nivelActual + 1, nivelMax, masProfundo);
    DeepestNode_ABB_recursivo(&((*a)->right), nivelActual + 1, nivelMax, masProfundo);
    return;
}

char *GetKey_ABB(arbol_bin_busqueda *a, posicion p)
{
    if (!NullNode_ABB(a, p))
        return p->clave;
    else
        printf("\nGetKey_ABB(a,p): Posición invalida");
}