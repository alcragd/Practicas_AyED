/*
================================================================================
diccionario.c
Versión: 1.0
Fecha: Junio 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
------------
Este programa implementa un diccionario interactivo usando un Árbol Binario de
Búsqueda (ABB) para almacenar palabras y sus definiciones. Permite cargar
definiciones desde un archivo, agregar, buscar, modificar y eliminar palabras,
así como exportar el diccionario en diferentes recorridos.

Funcionalidades:
- Cargar definiciones desde un archivo de texto.
- Agregar nuevas palabras y definiciones.
- Buscar palabras y mostrar su definición.
- Modificar la definición de una palabra existente.
- Eliminar palabras del diccionario.
- Mostrar recorridos PreOrden, InOrden y PosOrden del ABB.
- Mostrar estadísticas del árbol (altura, cantidad de palabras, etc.).
- Exportar el diccionario a un archivo en diferentes recorridos.

Compilación:
------------
gcc -o diccionario.exe diccionario.c ./TADArbol_Diccionario/TADArbolBinDiccionario.c

Uso:
----
./diccionario.exe

El programa muestra un menú interactivo con las siguientes opciones:
  1) Cargar un archivo de definiciones
  2) Agregar una palabra y su definición
  3) Buscar una palabra y ver su definición
  4) Modificar una definición
  5) Eliminar una palabra
  6) Recorrido PreOrden
  7) Recorrido InOrden
  8) Recorrido PosOrden
  9) Estadísticas del ABB
 10) Exportar definiciones
  0) Salir

Salida:
-------
- Interfaz de texto en consola para gestionar el diccionario.
- Estadísticas y recorridos del árbol.
- Exportación de definiciones a archivos de texto.

Observaciones:
--------------
- El archivo de definiciones debe tener el formato: palabra: definición
- El programa utiliza UTF-8 para soportar caracteres especiales.
- Requiere la implementación del TAD ABB en la carpeta TADArbol_Diccionario.
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "TADArbol_Diccionario\TADArbolBinDiccionario.h"

#define ARCHIVO_DEFAULT "salida.txt"

void imprimirMenu();
void cargarArchivo(arbol_bin_busqueda *a);
void agregarPalabra(arbol_bin_busqueda *a);
void buscarPalabra(arbol_bin_busqueda *a);
void modificarDefinicion(arbol_bin_busqueda *a);
void eliminarPalabra(arbol_bin_busqueda *a);
void EstadisticasABB(arbol_bin_busqueda *a);
void AjustarTexto(char *texto, int max_ancho);
void exportarArchivo(arbol_bin_busqueda *a);
void menuExportarArchivo();
void fRecorridoPreOrden(arbol_bin_busqueda *A, FILE *f);
void fRecorridoInOrden(arbol_bin_busqueda *A, FILE *f);
void fRecorridoPostOrden(arbol_bin_busqueda *A, FILE *f);
void crearArchivo(arbol_bin_busqueda *a, char *nArchivo, int opc);

int main()
{
    int opc;
    arbol_bin_busqueda arbolD;
    Initialize_ABB(&arbolD);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (1)
    {
        system("cls");
        imprimirMenu();
        printf("\n>> ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 0:
            Destroy_ABB(&arbolD);
            exit(0);
        case 1:
            cargarArchivo(&arbolD);
            break;
        case 2:
            agregarPalabra(&arbolD);
            break;
        case 3:
            buscarPalabra(&arbolD);
            break;
        case 4:
            modificarDefinicion(&arbolD);
            break;
        case 5:
            eliminarPalabra(&arbolD);
            break;
        case 6:
            system("cls");
            printf("\n=============== Recorrido PreOrden ==============\n");
            RecorridoPreOrden(&arbolD);
            printf("\n\n");
            system("pause");
            break;
        case 7:
            system("cls");
            printf("\n=============== Recorrido InOrden ==============\n");
            RecorridoInOrden(&arbolD);
            printf("\n\n");
            system("pause");
            break;
        case 8:
            system("cls");
            printf("\n=============== Recorrido PostOrden ==============\n");
            RecorridoPosOrden(&arbolD);
            printf("\n\n");
            system("pause");
            break;
        case 9:
            EstadisticasABB(&arbolD);
            break;
        case 10:
            exportarArchivo(&arbolD);
            break;
        default:
            system("cls");
            printf("\nOPCIÓN INVALIDA\n");
            break;
        }
    }
}

/*
================================================================================
void imprimirMenu()
Descripción:
------------
Muestra el menú principal de opciones en la consola para interactuar con el
diccionario.

Parámetros:
-----------
Ninguno.

Salida:
-------
Imprime el menú en la consola.
================================================================================
*/
void imprimirMenu()
{
    printf("\n=============== DICCIONARIO ==============\n");
    printf("\n================== MENU ==================\n");
    printf("\n 1) Cargar un archivo de definiciones");
    printf("\n 2) Agregar una palabra y su definicion");
    printf("\n 3) Buscar una palabra y ver su definición");
    printf("\n 4) Modificar una definición");
    printf("\n 5) Eliminar una palabra");
    printf("\n 6) Recorrido PreOrden");
    printf("\n 7) Recorrido InOrden");
    printf("\n 8) Recorrido PosOrden");
    printf("\n 9) Estadísticas del ABB");
    printf("\n 10) Exportar definiciones");
    printf("\n\n 0) Salir");
    printf("\n==========================================\n");
}

/*
================================================================================
void agregarPalabra(arbol_bin_busqueda *a)
Descripción:
------------
Permite al usuario agregar una nueva palabra y su definición al diccionario.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Inserta la nueva palabra y definición en el ABB.
================================================================================
*/
void agregarPalabra(arbol_bin_busqueda *a)
{
    elemento e;
    char opc;
    char clave[101];
    system("cls");
    printf("\n=============== Agregar Palabra ==============\n");

    do
    {
        printf("Ingrese la palabra a definir\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("\nIngrese la definición\n>> ");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Insert_ABB(a, clave, e);
        printf("\nAltura del arbol: %d", Depth_ABB(a));

        printf("\n\n¿Agregar más palabras?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

/*
================================================================================
void buscarPalabra(arbol_bin_busqueda *a)
Descripción:
------------
Permite buscar una palabra en el diccionario y muestra su definición si existe.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Imprime la definición de la palabra buscada o un mensaje si no existe.
================================================================================
*/
void buscarPalabra(arbol_bin_busqueda *a)
{
    char clave[101];
    char opc;
    posicion p;
    elemento e;
    system("cls");
    printf("\n=============== Buscar Palabra ==============\n");
    do
    {
        printf("Ingrese la palabra a buscar\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';

        p = Search_ABB(a, clave);
        if (p == NULL)
        {
            printf("\n[!] No se encontró la palabra");
        }
        else
        {
            e = ReadNode_ABB(a, p);
            printf("\n==========================================================");
            printf("\n\"%s\"", clave);
            printf("\n\nDefinición: ");
            AjustarTexto(e.d, 58);
            printf("\n==========================================================");

            // EstadisticasGenerales(a, e);
        }
        printf("\n\n¿Realizar otra Busqueda?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

/*
================================================================================
void modificarDefinicion(arbol_bin_busqueda *a)
Descripción:
------------
Permite modificar la definición de una palabra existente en el diccionario.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Actualiza la definición de la palabra en el ABB.
================================================================================
*/
void modificarDefinicion(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    system("cls");
    printf("\n=============== Modificar Definición ==============\n");
    do
    {
        printf("Ingrese la palabra a modificar\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("Ingrese la nueva definición\n>> ");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Modify_ABB(a, clave, e);

        printf("\n\n¿Realizar otra modificación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

/*
================================================================================
void eliminarPalabra(arbol_bin_busqueda *a)
Descripción:
------------
Elimina una palabra y su definición del diccionario.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Elimina la palabra del ABB.
================================================================================
*/
void eliminarPalabra(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    system("cls");
    printf("\n=============== Eliminar Palabra ==============\n");
    do
    {
        printf("Ingrese la palabra a eliminar\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';

        Delete_ABB(a, clave);
        printf("\nAltura del arbol: %d", Depth_ABB(a));

        printf("\n\n¿Realizar otra eliminación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

/*
================================================================================
void EstadisticasABB(arbol_bin_busqueda *a)
Descripción:
------------
Muestra estadísticas del árbol binario de búsqueda, como cantidad de palabras,
altura y palabra más profunda.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Imprime estadísticas del ABB en la consola.
================================================================================
*/
void EstadisticasABB(arbol_bin_busqueda *a)
{
    posicion p;
    char *pal;
    system("cls");
    printf("\n=============== Estadísticas ==============\n");

    p = DeepestNode_ABB(a);
    pal = GetKey_ABB(a, p);

    printf("\nCantidad de palabras en el árbol: %d", NodeCount_ABB(a));
    printf("\nAltura del árbol: %d", Depth_ABB(a));
    printf("\nPalabra más profunda: %s", pal);
    printf("\nOrden máximo de busqueda: (Search(a,\"%s\"))", pal);
    Search_ABB(a, pal);

    printf("\n\n");
    system("pause");
}

/*
================================================================================
void AjustarTexto(char *texto, int max_ancho)
Descripción:
------------
Ajusta e imprime un texto largo en varias líneas, respetando un ancho máximo
por línea para mejor visualización en consola.

Parámetros:
-----------
texto     : Texto a ajustar.
max_ancho : Ancho máximo por línea.

Salida:
-------
Imprime el texto ajustado en la consola.
================================================================================
*/
void AjustarTexto(char *texto, int max_ancho)
{
    int len = strlen(texto);
    int inicio = 0;

    while (inicio < len)
    {
        char lineaTexto[max_ancho + 1];
        int i;

        // Copiar hasta max_ancho o hasta que se encuentre un espacio cercano al límite
        for (i = 0; i < max_ancho && (inicio + i) < len; i++)
            lineaTexto[i] = texto[inicio + i];

        // Si el texto no terminó, tratar de cortar en espacio
        if ((inicio + i) < len && texto[inicio + i] != ' ')
        {
            while (i > 0 && lineaTexto[i - 1] != ' ')
                i--;
        }

        lineaTexto[i] = '\0'; // Terminar línea

        printf("\n%s", lineaTexto);

        inicio += i;
        while (texto[inicio] == ' ')
            inicio++; // Saltar espacios
    }
}

/*
================================================================================
void menuExportarArchivo()
Descripción:
------------
Muestra el submenú para elegir el tipo de recorrido al exportar el diccionario.

Parámetros:
-----------
Ninguno.

Salida:
-------
Imprime el submenú en la consola.
================================================================================
*/
void menuExportarArchivo()
{

    printf("\n================== MENU ==================\n");
    printf("\n 1) Recorrido PreOrden");
    printf("\n 2) Recorrido InOrden(Orden alfabetico)");
    printf("\n 3) Recorrido PosOrden");

    printf("\n\n 0) Cancelar");
    printf("\n==========================================\n");
}

/*
================================================================================
void exportarArchivo(arbol_bin_busqueda *a)
Descripción:
------------
Permite exportar el diccionario a un archivo de texto en el recorrido elegido
por el usuario (PreOrden, InOrden o PosOrden).

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Crea un archivo de texto con las definiciones exportadas.
================================================================================
*/
void exportarArchivo(arbol_bin_busqueda *a)
{
    FILE *archivo;
    char nomArchivo[256];
    int opc = -1;

    system("cls");
    printf("\n=============== Exportar Archivo ==============\n");
    printf("\n\nIngrese el nombre del archivo: (default: %s)\n>> ", ARCHIVO_DEFAULT);
    fgets(nomArchivo, sizeof(nomArchivo), stdin);
    nomArchivo[strcspn(nomArchivo, "\n")] = '\0';

    if (nomArchivo[0] == '\0')
        strcpy(nomArchivo, ARCHIVO_DEFAULT);

    menuExportarArchivo();

    while (opc != 1 && opc != 2 && opc != 3 && opc != 0)
    {
        printf("\n>> ");
        scanf("%d", &opc);
        if (opc == 0)
            return;
        else if (opc != 1 && opc != 2 && opc != 3)
            printf("\nOPCIÓN INVÁLIDA\n");
    }

    crearArchivo(a, nomArchivo, opc);
    printf("\n\n");
    system("pause");
    return;
}

/*
================================================================================
void cargarArchivo(arbol_bin_busqueda *a)
Descripción:
------------
Carga definiciones de palabras desde un archivo de texto con formato
"palabra: definición" y las inserta en el ABB.

Parámetros:
-----------
a : Puntero al árbol binario de búsqueda.

Salida:
-------
Actualiza el ABB con las palabras y definiciones del archivo.
================================================================================
*/
void cargarArchivo(arbol_bin_busqueda *a)
{
    FILE *archivo;
    char linea[2048], palabra[101], definicion[1024], nombreArchivo[256], opc;
    elemento e;
    int c, cont = 0, total = 0;

    system("cls");
    printf("\n=============== Cargar Archivo ==============\n");
    do
    {
        total = 0;
        printf("\nIngrese la ruta del archivo\n>> ");
        fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
        nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';

        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL)
        {
            printf("[!]-- No se pudo abrir el archivo '%s'.\n", nombreArchivo);
            return;
        }
        while (fgets(linea, sizeof(linea), archivo))
        {
            if (sscanf(linea, "%[^:]: %[^\n]\n", palabra, definicion) == 2 ||
                sscanf(linea, "%[^:]:%[^\n]\n", palabra, definicion) == 2)
            {
                if (strlen(palabra) == 0 || strlen(definicion) == 0)
                {
                    printf("Línea problemática: '%s'\n", linea);
                    printf("palabra='%s', definicion='%s'\n", palabra, definicion);
                }

                strcpy(e.d, definicion);

                Insert_ABB(a, palabra, e);
                total++;
            }
            else
            {
                cont++;
                while ((c = fgetc(archivo)) != '\n' && c != EOF)
                {
                };
            }
        }

        fclose(archivo);

        printf("\nArchivo %s cargado extitosamente.", nombreArchivo);
        printf("\nPalabras agregadas: %d", total);
        if (cont)
            printf("\n[WARNING] Se encontraron %d lineas con formato incorrecto.", cont);
        printf("\nAltura del arbol: %d", Depth_ABB(a));

        printf("\n\n¿Desea cargar otro archivo?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

/*
================================================================================
void fRecorridoPreOrden(arbol_bin_busqueda *A, FILE *f)
Descripción:
------------
Exporta el diccionario en recorrido PreOrden al archivo especificado.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.
f : Archivo de salida.

Salida:
-------
Escribe las palabras y definiciones en el archivo en PreOrden.
================================================================================
*/
void fRecorridoPreOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fprintf(f, "%s: %s\n", (*A)->clave, (*A)->e.d);
        fRecorridoPreOrden(&((*A)->left), f);
        fRecorridoPreOrden(&((*A)->right), f);
    }
    return;
}

/*
================================================================================
void fRecorridoInOrden(arbol_bin_busqueda *A, FILE *f)
Descripción:
------------
Exporta el diccionario en recorrido InOrden (alfabético) al archivo especificado.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.
f : Archivo de salida.

Salida:
-------
Escribe las palabras y definiciones en el archivo en InOrden.
================================================================================
*/
void fRecorridoInOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fRecorridoInOrden(&((*A)->left), f);
        fprintf(f, "%s: %s\n", (*A)->clave, (*A)->e.d);
        fRecorridoInOrden(&((*A)->right), f);
    }
    return;
}

/*
================================================================================
void fRecorridoPostOrden(arbol_bin_busqueda *A, FILE *f)
Descripción:
------------
Exporta el diccionario en recorrido PosOrden al archivo especificado.

Parámetros:
-----------
A : Puntero al árbol binario de búsqueda.
f : Archivo de salida.

Salida:
-------
Escribe las palabras y definiciones en el archivo en PosOrden.
================================================================================
*/
void fRecorridoPostOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fRecorridoPostOrden(&((*A)->left), f);
        fRecorridoPostOrden(&((*A)->right), f);
        fprintf(f, "%s: %s\n", (*A)->clave, (*A)->e.d);
    }
    return;
}

/*
================================================================================
void crearArchivo(arbol_bin_busqueda *a, char *nArchivo, int opc)
Descripción:
------------
Crea y escribe el archivo de exportación del diccionario según el recorrido
elegido por el usuario.

Parámetros:
-----------
a       : Puntero al árbol binario de búsqueda.
nArchivo: Nombre del archivo de salida.
opc     : Opción de recorrido (1=PreOrden, 2=InOrden, 3=PosOrden).

Salida:
-------
Archivo de texto con las definiciones exportadas.
================================================================================
*/
void crearArchivo(arbol_bin_busqueda *a, char *nArchivo, int opc)
{
    FILE *archivo;
    archivo = fopen(nArchivo, "w");
    if (archivo == NULL)
    {
        printf("[!]-- No se pudo crear/editar el archivo '%s'.\n", nArchivo);
        return;
    }

    switch (opc)
    {
    case 1:
        fRecorridoPreOrden(a, archivo);
        break;
    case 2:
        fRecorridoInOrden(a, archivo);
        break;
    case 3:
        fRecorridoPostOrden(a, archivo);
        break;
    }

    fclose(archivo);
    printf("\nArchivo exportado exitosamente");

    return;
}