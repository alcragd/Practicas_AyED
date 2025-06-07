#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabla Hash/TablaHash.h"

void imprimirMenu();
void cargarArchivo();
void agregarPalabra(tablaHash *t);
void buscarPalabra(tablaHash *t);
void modificarDefinicion(tablaHash *t);
void eliminarPalabra(tablaHash *t);
void verEstadisticasHash(tablaHash *t);

int main(int argc, char *argv[])
{
    int opc;
    tablaHash tablaH;

    Initialize_TH(&tablaH);

    while (1)
    {
        imprimirMenu();
        printf("\n>> ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            cargarArchivo();
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
            exit(0);
        default:
            printf("\nOPCIÓN INVALIDA\n");
            break;
        }
    }
}

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

        Insert_TH(t, e);

        printf("\n¿Agregar más palabras?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
    return;
}

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
            printf("\n[!]-- No se encontró la palabra");
        else
        {
            printf("\n%s ", e.p);
            printf("\n\tDefinición: %s", e.d);
        }
        printf("\n¿Hacer otra busqueda?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

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
            printf("\n[!]-- No se encontró la palabra");
        else
        {
            printf("\nIngrese la nueva definición\n>> ");
            fgets(e2.d, sizeof(e2.d), stdin);
            e2.d[strcspn(e2.d, "\n")] = '\0';

            Replace_TH(t, e2, e);
        }

        printf("\n¿Hacer otra modificación?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

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
            printf("\n[!]-- No se encontró la palabra");
        else
        {
            Delete_TH(t, e);
            printf("\nPalabra eliminada satisfactoriamente");
        }

        printf("\n¿Hacer otra eliminación?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

void imprimirMenu()
{
    printf("\n================ MENU ================");
    printf("\n 1) Cargar un archivo de definiciones");
    printf("\n 2) Agregar una palabra y su definicion");
    printf("\n 3) Buscar una palabra y ver su definición");
    printf("\n 4) Modificar una definición");
    printf("\n 5) Eliminar una palabra");
    printf("\n 6) Ver estadisticas Hash");
    printf("\n 7) Salir");
    printf("\n======================================");
}

void cargarArchivo()
{
}
void verEstadisticasHash(tablaHash *t)
{
}