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
void verEstadisticasHash(arbol_bin_busqueda *a);
void EstadisticasGenerales(arbol_bin_busqueda *a, elemento e);
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
            RecorridoPreOrden(&arbolD);
            break;
        case 7:
            RecorridoInOrden(&arbolD);
            break;
        case 8:
            RecorridoPosOrden(&arbolD);
            break;
        case 9:
            verEstadisticasHash(&arbolD);
            break;
        case 10:
            exportarArchivo(&arbolD);
            break;
        default:
            printf("\nOPCIÓN INVALIDA\n");
            break;
        }
    }
}
void imprimirMenu()
{
    printf("\n=============== DICCIONARIO ==============");
    printf("\n================== MENU ==================");
    printf("\n 1) Cargar un archivo de definiciones");
    printf("\n 2) Agregar una palabra y su definicion");
    printf("\n 3) Buscar una palabra y ver su definición");
    printf("\n 4) Modificar una definición");
    printf("\n 5) Eliminar una palabra");
    printf("\n 6) Recorrido PreOrden");
    printf("\n 7) Recorrido InOrden");
    printf("\n 8) Recorrido PosOrden");
    printf("\n 9) Ver estadisticas Hash");
    printf("\n 10) Exportar definiciones");
    printf("\n\n 0) Salir");
    printf("\n==========================================");
}
void agregarPalabra(arbol_bin_busqueda *a)
{
    elemento e;
    char opc;
    char clave[101];
    do
    {
        printf("Ingrese la palabra a definir\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("\nIngrese la definición\n>> ");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Insert_ABB(a, clave, e);

        printf("\n\n¿Agregar más palabras?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

void buscarPalabra(arbol_bin_busqueda *a)
{
    char clave[101];
    char opc;
    posicion p;
    elemento e;
    do
    {
        printf("Ingrese la palabra a buscar\n>>");
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
void modificarDefinicion(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    do
    {
        printf("Ingrese la palabra a modificar\n>> ");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("Ingrese la nueva definición\n>>");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Modify_ABB(a, clave, e);

        printf("\n\n¿Realizar otra modificación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}
void eliminarPalabra(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    do
    {
        printf("Ingrese la palabra a eliminar\n>>");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';

        Delete_ABB(a, clave);

        printf("\n\n¿Realizar otra eliminación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n')
            ;
    } while (opc == 'Y' || opc == 'y');
}

void verEstadisticasHash(arbol_bin_busqueda *a)
{
}
void EstadisticasGenerales(arbol_bin_busqueda *a, elemento e)
{
}
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
void menuExportarArchivo()
{

    printf("\n================== MENU ==================");
    printf("\n 1) Recorrido PreOrden");
    printf("\n 2) Recorrido InOrden(Orden alfabetico)");
    printf("\n 3) Recorrido PosOrden");

    printf("\n\n 0) Cancelar");
    printf("\n==========================================");
}
void exportarArchivo(arbol_bin_busqueda *a)
{
    FILE *archivo;
    char nomArchivo[256];
    int opc = -1;

    printf("\n=============== Exportar Archivo ==============");
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
    return;
}
void cargarArchivo(arbol_bin_busqueda *a)
{
    FILE *archivo;
    char linea[2048], palabra[101], definicion[1024], nombreArchivo[256], opc;
    elemento e;
    int c, cont = 0, total = 0;

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

        printf("\n\n¿Desea cargar otro archivo?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

void fRecorridoPreOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fprintf(f, "%s:%s\n", (*A)->clave, (*A)->e.d);
        fRecorridoPreOrden(&((*A)->left), f);
        fRecorridoPreOrden(&((*A)->right), f);
    }
    return;
}
void fRecorridoInOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fRecorridoInOrden(&((*A)->left), f);
        fprintf(f, "%s:%s\n", (*A)->clave, (*A)->e.d);
        fRecorridoInOrden(&((*A)->right), f);
    }
    return;
}
void fRecorridoPostOrden(arbol_bin_busqueda *A, FILE *f)
{
    if (*A != NULL)
    {
        fRecorridoPostOrden(&((*A)->left), f);
        fRecorridoPostOrden(&((*A)->right), f);
        fprintf(f, "%s:%s\n", (*A)->clave, (*A)->e.d);
    }
    return;
}

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
    return;
}