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

posicion Search_ABB(arbol_bin_busqueda *A, char *clave)
{
    int comp;
    if (*A == NULL)
        return NULL;
    comp = strcmp(clave, (*A)->clave);
    if (comp < 0)
        return Search_ABB(&((*A)->left), clave);
    else if (comp > 0)
        return Search_ABB(&((*A)->right), clave);
    else
        return *A;
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
    if (p == NULL) {
        printf("No se encontró la clave \"%s\" a modificar.\n", clave);
    } else {
        p->e = new;
        printf("Elemento modificado correctamente para la clave \"%s\".\n", clave);
    }
    return;
}

void Delete_ABB(arbol_bin_busqueda *A, char *clave)
{
    if (*A == NULL) {
        printf("No se encontró la clave \"%s\" para eliminar.\n", clave);
        return;
    }

    int cmp = strcmp(clave, (*A)->clave);

    if (cmp < 0) {
        Delete_ABB(&((*A)->left), clave);
    } else if (cmp > 0) {
        Delete_ABB(&((*A)->right), clave);
    } else {
        // Nodo encontrado
        nodo *temp;
        if ((*A)->left == NULL && (*A)->right == NULL) {
            // Caso 1: Sin hijos
            free(*A);
            *A = NULL;
            
        } else if ((*A)->left == NULL) {
            // Caso 2: Solo hijo derecho
            temp = *A;
            *A = (*A)->right;
            free(temp);
            
        } else if ((*A)->right == NULL) {
            // Caso 2: Solo hijo izquierdo
            temp = *A;
            *A = (*A)->left;
            free(temp);
            
        } else {
            // Caso 3: Dos hijos
            // Buscar el sucesor inorden (el menor del subárbol derecho)
            nodo *succParent = *A;
            nodo *succ = (*A)->right;
            while (succ->left != NULL) {
                succParent = succ;
                succ = succ->left;
            }
            // Copiar datos del sucesor
            strcpy((*A)->clave, succ->clave);
            (*A)->e = succ->e;
            // Eliminar el sucesor
            if (succParent->left == succ)
                Delete_ABB(&(succParent->left), succ->clave);
            else
                Delete_ABB(&(succParent->right), succ->clave);
            
        }
    }
}
void RecorridoPreOrden(arbol_bin_busqueda *A)
{  
    if(*A!=NULL)
    {
        printf("%s:\n%s\n",(*A)->clave,(*A)->e.d);
        RecorridoPreOrden(&((*A)->left));
        RecorridoPreOrden(&((*A)->right));
    }
    return;
}
void RecorridoInOrden(arbol_bin_busqueda *A)
{
    if(*A!=NULL)
    {
        RecorridoInOrden(&((*A)->left));
        printf("%s:\n%s\n",(*A)->clave,(*A)->e.d);
        RecorridoInOrden(&((*A)->right));
    }
    return;
}
void RecorridoPosOrden(arbol_bin_busqueda *A)
{
    if(*A!=NULL)
    {
        RecorridoPosOrden(&((*A)->left));
        RecorridoPosOrden(&((*A)->right));
        printf("%s:\n%s\n",(*A)->clave,(*A)->e.d);
    }
    return;
}