/*
================================================================================
TablaHash.c
Versión: 1.2
Fecha: Mayo 2025
Autores: Coyol Moreno Angel Zoe | Ramos Mendoza Miguel Angel | Ramirez Hernandez Christian Isaac

Descripción:
------------
Este archivo implementa una tabla hash utilizando listas doblemente ligadas para
gestionar colisiones. Proporciona funciones para inicializar, insertar, buscar,
eliminar, reemplazar y liberar elementos, así como para calcular colisiones y
recorrer la tabla.

El sistema permite:
- Insertar, eliminar, buscar y reemplazar elementos por clave.
- Calcular el índice hash de una clave con tres funciones diferentes.
- Analizar la dispersión y colisiones en la tabla.
- Acceder y recorrer las listas internas de la tabla hash.

Compilación:
------------
gcc -o Diccionario.exe Diccionario.c ./Tabla Hash/TablaHash.c ./TAD Lista DL/TADListaDL.c

Uso:
----
Incluye "TablaHash.h" en tu archivo fuente y utiliza las funciones proporcionadas
para gestionar una tabla hash de elementos.

Observaciones:
--------------
- La tabla hash utiliza listas doblemente ligadas para manejar colisiones.
- El tamaño de la tabla está definido por TAM_TABLA y debe ser un número primo
  para mejorar la dispersión de claves.
- Se recomienda verificar duplicados antes de insertar elementos usando Exists_TH.
- Todas las funciones asumen que la tabla ha sido correctamente inicializada.
- Es importante liberar la memoria con Destroy_TH al finalizar el uso de la tabla
  para evitar fugas de memoria.
- Incluye tres funciones hash para comparar eficiencia y dispersión.
================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TablaHash.h"

/*
================================================================================
void Initialize_TH(tablaHash *t)

Descripción:
------------
Inicializa una tabla hash, reservando memoria para cada lista y llamando a su
función de inicialización.

Parámetros:
-----------
t : Puntero a la tabla hash a inicializar.

Salida:
-------
La tabla hash queda lista para usarse.

Observaciones:
--------------
- Debe llamarse antes de cualquier operación sobre la tabla hash.
================================================================================
*/
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

/*
================================================================================
void Insert_TH(tablaHash *t, elemento e)

Descripción:
------------
Inserta un elemento en la tabla hash, agregándolo a la lista correspondiente
según el índice hash del elemento.

Parámetros:
-----------
t : Puntero a la tabla hash.
e : Elemento a insertar.

Salida:
-------
El elemento es agregado a la tabla hash.

Observaciones:
--------------
- No verifica duplicados; se recomienda verificar con Exists_TH antes.
================================================================================
*/
void Insert_TH(tablaHash *t, elemento e)
{

    Add(t->listas[e.indice], e);

    return;
}

/*
================================================================================
boolean Exists_TH(tablaHash *t, char *clave)

Descripción:
------------
Verifica si una palabra (clave) ya existe en la tabla hash. Busca únicamente por la
clave en la lista correspondiente al índice hash de la palabra, evitando así duplicados
de palabras en el diccionario.

Parámetros:
-----------
t     : Puntero a la tabla hash.
clave : Cadena de caracteres que representa la palabra a buscar.

Salida:
-------
TRUE si la palabra ya existe en la tabla hash, FALSE en caso contrario.

Observaciones:
--------------
- Solo compara la clave (palabra), no la definición ni otros campos del elemento.
- Se recomienda llamar a esta función antes de insertar una nueva palabra para evitar duplicados.
================================================================================
*/
boolean Exists_TH(tablaHash *t, char *clave)
{
    int indice = Hash(clave);
    posicion p = First(t->listas[indice]);
    elemento aux;

    while (p != NULL)
    {
        aux = Position(t->listas[indice], p);
        if (strcmp(aux.p, clave) == 0)
            return TRUE;
        p = Following(t->listas[indice], p);
    }
    return FALSE;
}

/*
================================================================================
elemento Search_TH(tablaHash *t, char *clave)

Descripción:
------------
Busca un elemento en la tabla hash usando su clave.

Parámetros:
-----------
t     : Puntero a la tabla hash.
clave : Cadena clave a buscar.

Salida:
-------
Devuelve el elemento encontrado o un elemento nulo si no existe.

Observaciones:
--------------
- El elemento nulo tiene la clave vacía.
================================================================================
*/
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

/*
================================================================================
void Delete_TH(tablaHash *t, elemento e)

Descripción:
------------
Elimina un elemento de la tabla hash, si existe, de la lista correspondiente.

Parámetros:
-----------
t : Puntero a la tabla hash.
e : Elemento a eliminar.

Salida:
-------
El elemento es eliminado si se encuentra.

Observaciones:
--------------
- No hace nada si el elemento no existe.
================================================================================
*/
void Delete_TH(tablaHash *t, elemento e)
{
    posicion p;
    int indice;

    indice = e.indice;
    p = Search(t->listas[indice], e);

    if (ValidatePosition(t->listas[indice], p))
        Remove(t->listas[indice], p);

    return;
}

/*
================================================================================
void Replace_TH(tablaHash *t, elemento new, elemento old)

Descripción:
------------
Reemplaza un elemento existente en la tabla hash por uno nuevo.

Parámetros:
-----------
t   : Puntero a la tabla hash.
new : Nuevo elemento.
old : Elemento a reemplazar.

Salida:
-------
El elemento viejo es reemplazado por el nuevo.

Observaciones:
--------------
- Solo reemplaza si el elemento viejo existe.
================================================================================
*/
void Replace_TH(tablaHash *t, elemento new, elemento old)
{
    posicion p;
    int indice;

    indice = old.indice;
    p = Search(t->listas[indice], old);

    if (ValidatePosition(t->listas[indice], p))
        Replace(t->listas[indice], p, new);

    return;
}

/*
================================================================================
void Destroy_TH(tablaHash *t)

Descripción:
------------
Libera toda la memoria utilizada por la tabla hash y sus listas internas.

Parámetros:
-----------
t : Puntero a la tabla hash.

Salida:
-------
Toda la memoria asociada es liberada.

Observaciones:
--------------
- Debe llamarse al final del uso de la tabla para evitar fugas de memoria.
================================================================================
*/
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

/*
================================================================================
int Collisions_TH(tablaHash *t, int i)

Descripción:
------------
Devuelve el número de colisiones (elementos extra) en la lista de la posición i
de la tabla hash.

Parámetros:
-----------
t : Puntero a la tabla hash.
i : Índice de la lista.

Salida:
-------
Número de colisiones (elementos - 1, o 0 si está vacía).

Observaciones:
--------------
- Útil para análisis de dispersión de la tabla hash.
================================================================================
*/
int Collisions_TH(tablaHash *t, int i)
{
    int size;

    size = Size(t->listas[i]);

    return size == 0 ? size : size - 1;
}

/*
================================================================================
int Hash(char *clave)

Descripción:
------------
Calcula el valor hash de una cadena clave para determinar su posición en la
tabla hash.

Parámetros:
-----------
clave : Cadena de caracteres a hashear.

Salida:
-------
Índice hash correspondiente a la clave.

Observaciones:
--------------
- Utiliza operaciones de bits (desplazamiento y suma) en vez de solo sumas o multiplicaciones.
  Esto es preferible porque:
    * El desplazamiento de bits (<< 5) es equivalente a multiplicar por 32, pero es más eficiente
      en la mayoría de arquitecturas.
    * Mezcla mejor los bits de los caracteres, logrando una distribución más uniforme de claves
      y reduciendo colisiones en la tabla hash.
    * La simple suma (como en Hash2) tiende a agrupar claves similares en los mismos índices,
      mientras que la combinación de suma y desplazamiento dispersa mejor los valores.
================================================================================
*/
int Hash(char *clave)
{
    unsigned long sum = 101;
    int i = 0, r;
    while (clave[i] != '\0')
    {
        sum = ((sum << 4) + sum) + clave[i];
        i++;
    }
    r = (int)(sum % TAM_TABLA);

    return r;
}

/*
================================================================================
int Hash2(char *clave)

Descripción:
------------
Calcula el valor hash de una cadena clave usando la suma simple de los valores
ASCII de los caracteres.

Parámetros:
-----------
clave : Cadena de caracteres a hashear.

Salida:
-------
Índice hash correspondiente a la clave.

Observaciones:
--------------
- Es un método simple y puede generar más colisiones.
- Útil para comparar la eficiencia de diferentes funciones hash.
- Defecto: No toma en cuenta el orden de los caracteres, por lo que anagramas
  (palabras con las mismas letras en diferente orden) producirán el mismo hash.
- Defecto: Las claves similares tienden a agruparse, lo que reduce la dispersión
  y aumenta el riesgo de colisiones.
================================================================================
*/
int Hash2(char *clave)
{
    int i = 0, sum = 0;
    while (clave[i] != '\0')
    {
        sum += clave[i];
        i++;
    }
    sum %= TAM_TABLA;

    return sum;
}

/*
================================================================================
int Hash3(char *clave)

Descripción:
------------
Calcula el valor hash de una cadena clave multiplicando el valor ASCII de cada
carácter por su posición y sumando los resultados.

Parámetros:
-----------
clave : Cadena de caracteres a hashear.

Salida:
-------
Índice hash correspondiente a la clave.

Observaciones:
--------------
- Puede mejorar la dispersión respecto a Hash2, pero sigue siendo simple.
- Útil para comparar la eficiencia de diferentes funciones hash.
- Defecto: Si muchas claves comparten prefijos o sufijos comunes, pueden
  agruparse en los mismos índices.
- Defecto: Para claves cortas o con caracteres repetidos, la dispersión sigue
  siendo limitada y pueden ocurrir colisiones.
================================================================================
*/
int Hash3(char *clave)
{
    int i = 0, sum = 0;
    while (clave[i] != '\0')
    {
        sum += clave[i] * i;
        i++;
    }
    sum %= TAM_TABLA;

    return sum;
}

/*
================================================================================
boolean EmptyIndex_TH(tablaHash *t, int i)

Descripción:
------------
Verifica si la lista en la posición i de la tabla hash está vacía.

Parámetros:
-----------
t : Puntero a la tabla hash.
i : Índice de la lista.

Salida:
-------
TRUE si está vacía, FALSE en caso contrario.

Observaciones:
--------------
- Útil para recorrer solo listas no vacías.
================================================================================
*/
boolean EmptyIndex_TH(tablaHash *t, int i)
{
    if (!Size(t->listas[i]))
        return TRUE;

    return FALSE;
}

/*
================================================================================
int Posicion(tablaHash *t, elemento e)

Descripción:
------------
Devuelve la posición (índice) de un elemento dentro de su lista en la tabla hash.

Parámetros:
-----------
t : Puntero a la tabla hash.
e : Elemento a buscar.

Salida:
-------
Índice (posición) del elemento en su lista, o -1 si no se encuentra.

Observaciones:
--------------
- Útil para operaciones avanzadas sobre la lista.
================================================================================
*/
int Posicion(tablaHash *t, elemento e)
{
    int indice;
    int pos = 0;
    posicion p;
    elemento aux;
    indice = e.indice;

    p = First(t->listas[indice]);

    while (p != NULL)
    {
        aux = Position(t->listas[indice], p);
        if (strcmp(aux.p, e.p) == 0)
            return pos;

        p = Following(t->listas[indice], p);
        pos++;
    }
}

/*
================================================================================
void VerListadeElemnto(tablaHash *t, elemento e)

Descripción:
------------
Imprime en consola todos los elementos de la lista correspondiente al índice
hash del elemento dado.

Parámetros:
-----------
t : Puntero a la tabla hash.
e : Elemento de referencia.

Salida:
-------
Imprime los elementos de la lista en consola.

Observaciones:
--------------
- Útil para depuración y análisis de la tabla hash.
================================================================================
*/
void VerListadeElemnto(tablaHash *t, elemento e)
{
    int indice, i;
    elemento aux;
    posicion p;
    indice = e.indice;

    p = First(t->listas[indice]);
    for (i = 0; i < Size(t->listas[indice]); i++)
    {
        aux = Position(t->listas[indice], p);
        printf("\nLista[%d] Elemento %d: %s", indice, i, aux.p);
        p = Following(t->listas[indice], p);
    }
    return;
}

/*
================================================================================
lista *getLista(tablaHash *t, int i)

Descripción:
------------
Devuelve un puntero a la lista en la posición i de la tabla hash.

Parámetros:
-----------
t : Puntero a la tabla hash.
i : Índice de la lista.

Salida:
-------
Puntero a la lista solicitada.

Observaciones:
--------------
- Permite acceso directo a las listas internas de la tabla hash.
================================================================================
*/
lista *getLista(tablaHash *t, int i)
{
    return t->listas[i];
}