/*
================================================================================
TADArbolBinDiccionario.c
Versión: 1.0
Fecha: Junio 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac

Descripción:
------------
Este archivo implementa un Árbol Binario de Búsqueda (ABB) para gestionar un
diccionario de palabras y definiciones. Proporciona funciones para inicializar,
insertar, buscar, modificar, eliminar y recorrer el árbol, así como obtener
estadísticas como altura, cantidad de nodos y el nodo más profundo.

El sistema permite:
- Insertar, eliminar, buscar y modificar elementos por clave.
- Recorrer el árbol en PreOrden, InOrden y PosOrden.
- Obtener estadísticas como altura, cantidad de nodos y palabra más profunda.
- Liberar la memoria utilizada por el árbol.

Compilación:
------------
gcc -o diccionario.exe diccionario.c ./TADArbol_Diccionario/TADArbolBinDiccionario.c

Uso:
----
Incluye "TADArbolBinDiccionario.h" en tu archivo fuente y utiliza las funciones
proporcionadas para gestionar un árbol binario de búsqueda de elementos.

Observaciones:
--------------
- El ABB almacena claves (palabras) y sus definiciones.
- Todas las funciones asumen que el árbol ha sido correctamente inicializado.
- Es importante liberar la memoria con Destroy_ABB al finalizar el uso del árbol
  para evitar fugas de memoria.
================================================================================
*/

#include "TADArbolBinDiccionario.h"
#include <string.h>
#include <stdlib.h>

/*
================================================================================
void Initialize_ABB(arbol_bin_busqueda *A)

Descripción:
------------
Inicializa un árbol binario de búsqueda, dejándolo vacío y listo para usarse.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda a inicializar.

Salida:
-------
El árbol queda vacío y preparado para operaciones.

Observaciones:
--------------
- Debe llamarse antes de cualquier operación sobre el árbol.
================================================================================
*/
void Initialize_ABB(arbol_bin_busqueda *A)
{
    *A = NULL;
    return;
}

/*
================================================================================
void Insert_ABB(arbol_bin_busqueda *A, char *clave, elemento e)

Descripción:
------------
Inserta un elemento en el árbol binario de búsqueda según la clave dada.

Parámetros:
-----------
A     : Puntero al árbol binario de búsqueda.
clave : Clave (palabra) del elemento.
e     : Elemento a insertar (definición).

Salida:
-------
El elemento es agregado al árbol en la posición correspondiente.

Observaciones:
--------------
- No permite claves duplicadas.
================================================================================
*/
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

/*
================================================================================
booleano Empty_ABB(arbol_bin_busqueda *A)

Descripción:
------------
Verifica si el árbol binario de búsqueda está vacío.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.

Salida:
-------
TRUE si el árbol está vacío, FALSE en caso contrario.
================================================================================
*/
booleano Empty_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return TRUE;
    return FALSE;
}

/*
================================================================================
posicion Search_ABB(arbol_bin_busqueda *A, char *clave)

Descripción:
------------
Busca un nodo en el árbol binario de búsqueda usando la clave dada.

Parámetros:
-----------
A     : Puntero al árbol binario de búsqueda.
clave : Clave (palabra) a buscar.

Salida:
-------
Devuelve la posición del nodo encontrado o NULL si no existe.

Observaciones:
--------------
- Imprime el número de comparaciones realizadas.
================================================================================
*/
posicion Search_ABB(arbol_bin_busqueda *A, char *clave)
{
    int contador = 0;
    return Search_ABB_recursiva(A, clave, &contador);
}

/*
================================================================================
posicion Search_ABB_recursiva(arbol_bin_busqueda *A, char *clave, int *contador)

Descripción:
------------
Función recursiva interna para buscar un nodo por clave y contar comparaciones.

Parámetros:
-----------
A        : Puntero al árbol binario de búsqueda.
clave    : Clave (palabra) a buscar.
contador : Puntero al contador de comparaciones.

Salida:
-------
Devuelve la posición del nodo encontrado o NULL si no existe.
================================================================================
*/
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

/*
================================================================================
elemento ReadNode_ABB(arbol_bin_busqueda *A, posicion p)

Descripción:
------------
Devuelve el elemento almacenado en la posición dada del árbol.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.
p : Posición del nodo.

Salida:
-------
Elemento almacenado en el nodo.

Observaciones:
--------------
- Termina el programa si la posición es inválida.
================================================================================
*/
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

/*
================================================================================
booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p)

Descripción:
------------
Verifica si una posición es nula o inválida en el árbol.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.
p : Posición a verificar.

Salida:
-------
TRUE si la posición es nula o inválida, FALSE en caso contrario.
================================================================================
*/
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

/*
================================================================================
void Destroy_ABB(arbol_bin_busqueda *A)

Descripción:
------------
Libera toda la memoria utilizada por el árbol binario de búsqueda.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.

Salida:
-------
Toda la memoria asociada es liberada.

Observaciones:
--------------
- Debe llamarse al final del uso del árbol para evitar fugas de memoria.
================================================================================
*/
void Destroy_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return;
    Destroy_ABB(&((*A)->left));
    Destroy_ABB(&((*A)->right));
    free(*A);
    *A = NULL;
}

/*
================================================================================
void Modify_ABB(arbol_bin_busqueda *A, char *clave, elemento new)

Descripción:
------------
Modifica el elemento asociado a una clave existente en el árbol.

Parámetros:
-----------
A    : Puntero al árbol binario de búsqueda.
clave: Clave (palabra) a modificar.
new  : Nuevo elemento (definición).

Salida:
-------
Actualiza el elemento si la clave existe.
================================================================================
*/
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

/*
================================================================================
void Delete_ABB(arbol_bin_busqueda *A, char *clave)

Descripción:
------------
Elimina un nodo del árbol binario de búsqueda según la clave dada.

Parámetros:
-----------
A    : Puntero al árbol binario de búsqueda.
clave: Clave (palabra) a eliminar.

Salida:
-------
El nodo es eliminado si existe.
================================================================================
*/
void Delete_ABB(arbol_bin_busqueda *A, char *clave)
{
    int contador = 0;
    Delete_ABB_recursivo(A, clave, &contador, 1);
}

/*
================================================================================
void Delete_ABB_recursivo(arbol_bin_busqueda *A, char *clave, int *contador, int imprimir)

Descripción:
------------
Función recursiva interna para eliminar un nodo por clave y contar comparaciones.

Parámetros:
-----------
A        : Puntero al árbol binario de búsqueda.
clave    : Clave (palabra) a eliminar.
contador : Puntero al contador de comparaciones.
imprimir : Si es 1, imprime mensajes; si es 0, no imprime.

Salida:
-------
El nodo es eliminado si existe.
================================================================================
*/
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

/*
================================================================================
void RecorridoPreOrden(arbol_bin_busqueda *A)

Descripción:
------------
Imprime el recorrido PreOrden del árbol binario de búsqueda.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.

Salida:
-------
Imprime las claves y definiciones en PreOrden.
================================================================================
*/
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

/*
================================================================================
void RecorridoInOrden(arbol_bin_busqueda *A)

Descripción:
------------
Imprime el recorrido InOrden (alfabético) del árbol binario de búsqueda.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.

Salida:
-------
Imprime las claves y definiciones en InOrden.
================================================================================
*/
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

/*
================================================================================
void RecorridoPosOrden(arbol_bin_busqueda *A)

Descripción:
------------
Imprime el recorrido PosOrden del árbol binario de búsqueda.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.

Salida:
-------
Imprime las claves y definiciones en PosOrden.
================================================================================
*/
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

/*
================================================================================
int Depth_ABB(arbol_bin_busqueda *a)

Descripción:
------------
Calcula la altura (profundidad máxima) del árbol binario de búsqueda.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Altura del árbol.
================================================================================
*/
int Depth_ABB(arbol_bin_busqueda *a)
{
    int depth_r, depth_l;
    if (*a == NULL)
        return 0;

    depth_r = Depth_ABB(&((*a)->right));
    depth_l = Depth_ABB(&((*a)->left));

    return (depth_r > depth_l ? depth_r : depth_l) + 1;
}

/*
================================================================================
int NodeCount_ABB(arbol_bin_busqueda *a)

Descripción:
------------
Cuenta el número total de nodos en el árbol binario de búsqueda.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Cantidad de nodos en el árbol.
================================================================================
*/
int NodeCount_ABB(arbol_bin_busqueda *a)
{
    if (*a == NULL)
        return 0;
    else
        return (1 + NodeCount_ABB(&(*a)->left) + NodeCount_ABB(&(*a)->right));
}

/*
================================================================================
posicion DeepestNode_ABB(arbol_bin_busqueda *a)

Descripción:
------------
Obtiene la posición del nodo más profundo en el árbol binario de búsqueda.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Posición del nodo más profundo.
================================================================================
*/
posicion DeepestNode_ABB(arbol_bin_busqueda *a)
{
    int nivelMax = -1;
    posicion masProfundo = NULL;
    DeepestNode_ABB_recursivo(a, 0, &nivelMax, &masProfundo);
    return masProfundo;
}

/*
================================================================================
void DeepestNode_ABB_recursivo(arbol_bin_busqueda *a, int nivelActual, int *nivelMax, posicion *masProfundo)

Descripción:
------------
Función recursiva interna para encontrar el nodo más profundo del árbol.

Parámetros:
-----------
a           : Puntero al árbol binario de búsqueda.
nivelActual : Nivel actual en la recursión.
nivelMax    : Puntero al nivel máximo encontrado.
masProfundo : Puntero a la posición del nodo más profundo.

Salida:
-------
Actualiza masProfundo con el nodo más profundo.
================================================================================
*/
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

/*
================================================================================
char *GetKey_ABB(arbol_bin_busqueda *a, posicion p)

Descripción:
------------
Devuelve la clave (palabra) almacenada en la posición dada del árbol.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.
p : Posición del nodo.

Salida:
-------
Clave almacenada en el nodo.

Observaciones:
--------------
- Imprime un mensaje si la posición es inválida.
================================================================================
*/
char *GetKey_ABB(arbol_bin_busqueda *a, posicion p)
{
    if (!NullNode_ABB(a, p))
        return p->clave;
    else
        printf("\nGetKey_ABB(a,p): Posición invalida");
}