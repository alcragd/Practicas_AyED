#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tabla Hash/TablaHash.h"

void imprimirMenu();
void cargarArchivo(tablaHash *t);
void agregarPalabra(tablaHash *t);
void buscarPalabra(tablaHash *t);
void modificarDefinicion(tablaHash *t);
void eliminarPalabra(tablaHash *t);
void verEstadisticasHash(tablaHash *t);
void EstadisticasGenerales(tablaHash *t, elemento e);


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
            Destroy_TH(&tablaH);
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
        e.indice=Hash(e.p);

        if (!Exists_TH(t, e))
            Insert_TH(t, e);
        
        EstadisticasGenerales(t,e);

        printf("\n\n¿Agregar más palabras?(Y/N)\n>> ");
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
            printf("\n[!] No se encontró la palabra");
        else
        {
            printf("\n\"%s\"", e.p);
            printf("\nDefinición: %s", e.d);
            EstadisticasGenerales(t,e);
        }
        printf("\n\n¿Hacer otra busqueda?(Y/N)\n>> ");
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
            printf("\n[!] No se encontró la palabra");
        else
        {
            printf("\nIngrese la nueva definición\n>> ");
            fgets(e2.d, sizeof(e2.d), stdin);
            e2.d[strcspn(e2.d, "\n")] = '\0';
            e2.indice=Hash(e2.p);

            Replace_TH(t, e2, e);
            EstadisticasGenerales(t,e2);
        }

        printf("\n\n¿Hacer otra modificación?(Y/N)\n>> ");
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
            printf("\n[!] No se encontró la palabra");
        else
        {
            EstadisticasGenerales(t,e);
            Delete_TH(t, e);
            printf("\nPalabra eliminada satisfactoriamente");
        }

        printf("\n\n¿Hacer otra eliminación?(Y/N)\n>> ");
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

void cargarArchivo(tablaHash *t)
{
    FILE *archivo;
    char palabra[101], definicion[251], nombreArchivo[256], opc;
    elemento e;
    int c, cont = 0;

    do
    {
        printf("\nIngrese la ruta del archivo\n>> ");
        fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
        nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';

        //C:\Users\chris\OneDrive\Escritorio\ESCOM\Algoritmos y Estructura\Practicas_AyED\Practica 05\Palabras

        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL)
        {
            printf("[!]-- No se pudo abrir el archivo '%s'.\n", nombreArchivo);
            return;
        }
        while (!feof(archivo))
        {
            if (fscanf(archivo, "%100[^:]: %250[^\n]\n", palabra, definicion) == 2 ||
                fscanf(archivo, "%100[^:]:%250[^\n]\n", palabra, definicion) == 2)
            {
                strcpy(e.p,palabra);
                strcpy(e.d,definicion);
                e.indice=Hash(e.p);
                if (!Exists_TH(t, e))
                    Insert_TH(t, e);
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
        if (cont)
            printf("\n[WARNING] Se encontraron %d lineas con formato incorrecto.", cont);

        printf("\n\n¿Desea cargar otro archivo?(Y/N)\n>> ");
        scanf("%c", &opc);
        getchar();
    } while (opc == 'Y' || opc == 'y');
}

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
void EstadisticasGenerales(tablaHash *t, elemento e)
{
    int pos;
    pos=Posicion(t,e);
    VerListadeElemnto(t,e);
    printf("\nIndice de la lista de la tabla: %d",e.indice);
    printf("\nSe encontro detras de %d palabras",pos);
    printf("\nNumero de comparaciones: %d",pos+1);
    printf("\nEl resultado del hash de la palabra %s fue: %d",e.p,e.indice);
    return;
}