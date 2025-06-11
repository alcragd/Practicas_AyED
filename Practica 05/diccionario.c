/*
================================================================================
diccionario.c
Versión: 1.0
Fecha: Junio 2025
Autor: Ramirez Hernandez Christian Isaac| Coyol Moreno Angel Zoe | Ramos Mendoza Miguel Angel

Descripción:
------------
Este programa implementa un diccionario interactivo basado en una tabla hash.
Permite cargar definiciones desde archivos, agregar, buscar, modificar y eliminar
palabras, así como exportar el diccionario y ver estadísticas de la tabla hash.
La interfaz es completamente en consola y soporta acentos y caracteres especiales.

Funcionalidades:
- Cargar definiciones desde archivos de texto.
- Agregar palabras y definiciones manualmente.
- Buscar palabras y mostrar su definición.
- Modificar la definición de palabras existentes.
- Eliminar palabras del diccionario.
- Exportar todas las definiciones a un archivo de texto.
- Mostrar estadísticas de la tabla hash (colisiones, listas vacías, etc.).
- Ajustar visualmente el texto de las definiciones para una mejor presentación.

Compilación:
------------
Windows:
gcc -o diccionario.exe diccionario.c  "Tabla Hash/TablaHash.c" "Tabla Hash/TAD Lista DL/TADListaDL.c"

Linux:
gcc -o diccionario diccionario.c  "Tabla Hash/TablaHash.c" "Tabla Hash/TAD Lista DL/TADListaDL.c"

Uso:
----
./diccionario.exe

El programa solicitará:
  - Seleccionar una opción del menú (cargar archivo, agregar palabra, buscar, etc.).
  - Ingresar rutas de archivos, palabras y definiciones según la opción elegida.

Salida:
-------
- Mensajes en consola con resultados de las operaciones.
- Estadísticas y advertencias sobre el estado de la tabla hash.
- Archivo exportado con todas las definiciones si se elige esa opción.

Observaciones:
--------------
- Se recomienda ejecutar en consola con soporte UTF-8 para acentos y caracteres especiales.
- El tamaño máximo de palabra y definición está limitado por el programa.
- El formato de archivo esperado es: palabra: definición (una por línea).
================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tabla Hash/TablaHash.h"

#define ARCHIVO_DEFAULT "salida.txt"

void imprimirMenu();
void cargarArchivo(tablaHash *t);
void agregarPalabra(tablaHash *t);
void buscarPalabra(tablaHash *t);
void modificarDefinicion(tablaHash *t);
void eliminarPalabra(tablaHash *t);
void verEstadisticasHash(tablaHash *t);
void EstadisticasGenerales(tablaHash *t, elemento e);
void AjustarTexto(char *texto, int max_ancho);
void exportarArchivo(tablaHash *t);

int main(int argc, char *argv[])
{
    int opc;
    tablaHash tablaH;

    Initialize_TH(&tablaH);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (1)
    {
        imprimirMenu();
        printf("\n>> ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 0:
            Destroy_TH(&tablaH);
            exit(0);
        case 1:
            cargarArchivo(&tablaH);
            break;
        case 2:
            agregarPalabra(&tablaH);
            break;
        case 3:
            buscarPalabra(&tablaH);
            break;
        case 4:
            modificarDefinicion(&tablaH);
            break;
        case 5:
            eliminarPalabra(&tablaH);
            break;
        case 6:
            verEstadisticasHash(&tablaH);
            break;
        case 7:
            exportarArchivo(&tablaH);
            break;
        default:
            printf("\nOPCIÓN INVALIDA\n");
            break;
        }
    }
}
/*
================================================================================
void agregarPalabra(tablaHash *t)

Descripción:
------------
Permite al usuario agregar manualmente una palabra y su definición al diccionario.

Parámetros:
-----------
t : Puntero a la tabla hash donde se insertará la palabra.

Salida:
-------
Actualiza la tabla hash con la nueva palabra y definición.

Observaciones:
--------------
- Permite agregar varias palabras en una sola sesión.
- Muestra estadísticas de la tabla hash después de cada inserción.
================================================================================
*/
void agregarPalabra(tablaHash *t)
{
    elemento e;
    char opc;

    do
    {
        printf("\nIngrese la palabra a definir\n>> ");
        fgets(e.p, sizeof(e.p), stdin);
        e.p[strcspn(e.p, "\n")] = '\0';
        printf("\nIngrese la definición\n>> ");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';
        e.indice = Hash(e.p);

        if (!Exists_TH(t, e))
            Insert_TH(t, e);

        EstadisticasGenerales(t, e);

        printf("\n\n¿Agregar más palabras?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
    return;
}
/*
================================================================================
void buscarPalabra(tablaHash *t)

Descripción:
------------
Permite al usuario buscar una palabra en el diccionario y muestra su definición
si existe.

Parámetros:
-----------
t : Puntero a la tabla hash donde se buscará la palabra.

Salida:
-------
Imprime la definición de la palabra buscada y estadísticas de búsqueda.

Observaciones:
--------------
- Permite realizar varias búsquedas en una sola sesión.
- Si la palabra no existe, informa al usuario.
================================================================================
*/
void buscarPalabra(tablaHash *t)
{
    elemento e;
    char palabra[101], opc;

    do
    {
        printf("\nIngrese la palabra a buscar\n>> ");
        fgets(palabra, sizeof(palabra), stdin);
        palabra[strcspn(palabra, "\n")] = '\0';

        e = Search_TH(t, palabra);

        if (e.p[0] == '\0')
            printf("\n[!] No se encontró la palabra");
        else
        {
            printf("\n==========================================================");
            printf("\n\"%s\"", e.p);
            printf("\n\nDefinición: ");
            AjustarTexto(e.d, 58);
            printf("\n==========================================================");

            EstadisticasGenerales(t, e);
        }
        printf("\n\n¿Hacer otra busqueda?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}
/*
================================================================================
void modificarDefinicion(tablaHash *t)

Descripción:
------------
Permite al usuario modificar la definición de una palabra existente en el diccionario.

Parámetros:
-----------
t : Puntero a la tabla hash donde se modificará la definición.

Salida:
-------
Actualiza la definición de la palabra en la tabla hash.

Observaciones:
--------------
- Permite modificar varias definiciones en una sola sesión.
- Si la palabra no existe, informa al usuario.
================================================================================
*/
void modificarDefinicion(tablaHash *t)
{
    char opc;
    elemento e, e2;

    do
    {
        printf("\nIngrese la palabra a modificar\n>> ");
        fgets(e2.p, sizeof(e2.p), stdin);
        e2.p[strcspn(e2.p, "\n")] = '\0';

        e = Search_TH(t, e2.p);

        if (e.p[0] == '\0')
            printf("\n[!] No se encontró la palabra");
        else
        {
            printf("\nIngrese la nueva definición\n>> ");
            fgets(e2.d, sizeof(e2.d), stdin);
            e2.d[strcspn(e2.d, "\n")] = '\0';
            e2.indice = Hash(e2.p);

            Replace_TH(t, e2, e);
            EstadisticasGenerales(t, e2);
        }

        printf("\n\n¿Hacer otra modificación?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}
/*
================================================================================
void eliminarPalabra(tablaHash *t)

Descripción:
------------
Permite al usuario eliminar una palabra y su definición del diccionario.

Parámetros:
-----------
t : Puntero a la tabla hash donde se eliminará la palabra.

Salida:
-------
Elimina la palabra de la tabla hash.

Observaciones:
--------------
- Permite eliminar varias palabras en una sola sesión.
- Si la palabra no existe, informa al usuario.
================================================================================
*/
void eliminarPalabra(tablaHash *t)
{
    char palabra[101], opc;
    elemento e;

    do
    {
        printf("\nIngrese la palabra a eliminar\n>> ");
        fgets(palabra, sizeof(palabra), stdin);
        palabra[strcspn(palabra, "\n")] = '\0';

        e = Search_TH(t, palabra);

        if (e.p[0] == '\0')
            printf("\n[!] No se encontró la palabra");
        else
        {
            EstadisticasGenerales(t, e);
            Delete_TH(t, e);
            printf("\nPalabra eliminada satisfactoriamente");
        }

        printf("\n\n¿Hacer otra eliminación?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}
/*
================================================================================
void imprimirMenu()

Descripción:
------------
Muestra en pantalla el menú principal de opciones para el usuario.

Parámetros:
-----------
Ninguno.

Salida:
-------
Imprime el menú en consola.

Observaciones:
--------------
Ninguna.
================================================================================
*/
void imprimirMenu()
{
    printf("\n================== MENU ==================");
    printf("\n 1) Cargar un archivo de definiciones");
    printf("\n 2) Agregar una palabra y su definicion");
    printf("\n 3) Buscar una palabra y ver su definición");
    printf("\n 4) Modificar una definición");
    printf("\n 5) Eliminar una palabra");
    printf("\n 6) Ver estadisticas Hash");
    printf("\n 7) Exportar definiciones");
    printf("\n\n 0) Salir");
    printf("\n==========================================");
}
/*
================================================================================
void cargarArchivo(tablaHash *t)

Descripción:
------------
Permite al usuario cargar un archivo de definiciones al diccionario. Lee cada línea,
verifica el formato, y agrega las palabras y definiciones válidas a la tabla hash.

Parámetros:
-----------
t : Puntero a la tabla hash donde se insertarán las definiciones.

Salida:
-------
Actualiza la tabla hash con las palabras y definiciones del archivo.

Observaciones:
--------------
- Informa al usuario si hay líneas con formato incorrecto.
- Permite cargar varios archivos en una sola sesión.
================================================================================
*/
void cargarArchivo(tablaHash *t)
{
    FILE *archivo;
    char linea[2048], palabra[101], definicion[1024], nombreArchivo[256], opc;
    elemento e;
    int c, cont = 0, total = 0;

    do
    {
        printf("\nIngrese la ruta del archivo\n>> ");
        fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
        nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';

        // C:\Users\chris\OneDrive\Escritorio\ESCOM\Algoritmos y Estructura\Practicas_AyED\Practica 05\Palabras

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
                strcpy(e.p, palabra);
                strcpy(e.d, definicion);
                e.indice = Hash(e.p);
                if (!Exists_TH(t, e))
                {
                    Insert_TH(t, e);
                    total++;
                }
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

        printf("\n\n¿Desea cargar otro archivo?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}
/*
================================================================================
void verEstadisticasHash(tablaHash *t)

Descripción:
------------
Muestra estadísticas sobre la distribución de las palabras en la tabla hash,
como colisiones, listas vacías, y promedios.

Parámetros:
-----------
t : Puntero a la tabla hash a analizar.

Salida:
-------
Imprime estadísticas en consola.

Observaciones:
--------------
Ninguna.
================================================================================
*/
void verEstadisticasHash(tablaHash *t)
{
    int colisiones, i, empty = 0, sum, min = (int)1e19, max = -1;
    double prom;

    printf("\nEstadisticas Hash:");
    printf("\n\tColisiones:");
    for (i = 0; i < TAM_TABLA; i++)
    {
        colisiones = Collisions_TH(t, i);
        if (!EmptyIndex_TH(t, i))
        {
            printf("\n\t\tLista [%d]:\t%d", i, colisiones);

            sum += colisiones;
            min = (min < colisiones ? min : colisiones);
            max = (max > colisiones ? max : colisiones);
        }
        else
        {
            printf("\n\t\tLista [%d]:\tVACIA", i);
            empty++;
        }
    }
    prom = sum / (TAM_TABLA - empty);
    printf("\n\n\tMáximo de colisiones:\t%d", max);
    printf("\n\tMinimo de colisiones:\t%d", min);
    printf("\n\tColisiones Promedio:\t%.2lf", prom);

    printf("\nListas Vacias:\t%d", empty);
}
/*
================================================================================
void EstadisticasGenerales(tablaHash *t, elemento e)

Descripción:
------------
Muestra estadísticas detalladas sobre la posición y búsqueda de un elemento
específico en la tabla hash.

Parámetros:
-----------
t : Puntero a la tabla hash.
e : Elemento del cual se mostrarán estadísticas.

Salida:
-------
Imprime estadísticas en consola.

Observaciones:
--------------
Ninguna.
================================================================================
*/
void EstadisticasGenerales(tablaHash *t, elemento e)
{
    int pos;
    pos = Posicion(t, e);

    printf("\n\n==========================================================");
    printf("\nEstadisticas hash:\n");
    VerListadeElemnto(t, e);
    printf("\n\n-Indice de la lista de la tabla: %d", e.indice);
    printf("\n-Se encontro detras de %d palabras", pos);
    printf("\n-Numero de comparaciones: %d", pos + 1);
    printf("\n-El resultado del hash de la palabra %s fue: %d", e.p, e.indice);
    printf("\n==========================================================");
    return;
}

/*
================================================================================
void AjustarTexto(char *texto, int x, int y, int max_ancho, int max_lineas)

Descripción:
------------
Imprime un texto largo en la consola ajustándolo para que no sobrepase un ancho
máximo y dividiéndolo en varias líneas.

Parámetros:
-----------
texto       : Cadena de texto a mostrar.
max_ancho   : Máximo ancho (caracteres) permitido por línea.

Salida:
-------
Imprime el texto ajustado en consola.

Observaciones:
--------------
- Intenta no cortar palabras a la mitad, buscando un espacio cercano para cortar.
- Si el texto es más largo que el permitido, se trunca.
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
void exportarArchivo(tablaHash *t)

Descripción:
------------
Permite exportar todas las palabras y definiciones del diccionario a un archivo de texto.

Parámetros:
-----------
t : Puntero a la tabla hash a exportar.

Salida:
-------
Crea o sobrescribe un archivo de texto con las definiciones.

Observaciones:
--------------
- El usuario puede elegir el nombre del archivo.
- Si no se especifica, se usa un nombre por defecto.
================================================================================
*/
void exportarArchivo(tablaHash *t)
{
    FILE *archivo;
    char nomArchivo[256];
    posicion p;
    elemento e;
    lista *l;

    int i;
    printf("\nIngrese el nombre del archivo: (default: %s)\n>> ", ARCHIVO_DEFAULT);
    fgets(nomArchivo, sizeof(nomArchivo), stdin);
    nomArchivo[strcspn(nomArchivo, "\n")] = '\0';

    if (nomArchivo[0] == '\0')
        strcpy(nomArchivo, ARCHIVO_DEFAULT);

    archivo = fopen(nomArchivo, "w");
    if (archivo == NULL)
    {
        printf("[!]-- No se pudo crear/editar el archivo '%s'.\n", nomArchivo);
        return;
    }

    for (i = 0; i < TAM_TABLA; i++)
    {
        l = getLista(t, i);
        p = First(l);
        while (ValidatePosition(l, p))
        {
            e = Position(l, p);
            fprintf(archivo, "%s: %s\n", e.p, e.d);
            p = Following(l, p);
        }
    }

    fclose(archivo);

    printf("\nArchivo '%s' exportado exitosamente.", nomArchivo);
}