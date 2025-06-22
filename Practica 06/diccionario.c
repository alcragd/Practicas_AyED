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

int main(){
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
    do{
        printf("Ingrese la palabra a definir\n>>");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("\nIngrese la definición\n>> ");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Insert_ABB(a,clave,e);

        printf("\n\n¿Agregar más palabras?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n');
        } while(opc== 'Y'|| opc=='y');
}

void buscarPalabra(arbol_bin_busqueda *a)
{
    char clave[101];
    char opc;
    posicion p;
    elemento e;
    do{
        printf("Ingrese la palabra a buscar\n>>");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        
        p=Search_ABB(a,clave);
        if(p==NULL)
        {
            printf("\n[!] No se encontró la palabra");
        }
        else
        {
            e=ReadNode_ABB(a,p);
            printf("\n==========================================================");
            printf("\n\"%s\"", clave);
            printf("\n\nDefinición: ");
            AjustarTexto(e.d, 58);
            printf("\n==========================================================");

            // EstadisticasGenerales(a, e);
        }
        printf("\n\n¿Realizar otra Busqueda?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n');
        } while(opc== 'Y'|| opc=='y');

}
void modificarDefinicion(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    do{
        printf("Ingrese la palabra a modificar\n>>");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
        printf("Ingrese la nueva definición\n>>");
        fgets(e.d, sizeof(e.d), stdin);
        e.d[strcspn(e.d, "\n")] = '\0';

        Modify_ABB(a,clave,e);
        
        
        printf("\n\n¿Realizar otra modificación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n');
        } while(opc== 'Y'|| opc=='y');
}
void eliminarPalabra(arbol_bin_busqueda *a)
{
    char opc;
    elemento e;
    char clave[101];
    do{
        printf("Ingrese la palabra a eliminar\n>>");
        fgets(clave, sizeof(clave), stdin);
        clave[strcspn(clave, "\n")] = '\0';
       

        Delete_ABB(a,clave);
        
        
        printf("\n\n¿Realizar otra eliminación?(Y/N)\n>> ");
        scanf(" %c", &opc);
        while (getchar() != '\n');
        } while(opc== 'Y'|| opc=='y');
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
void exportarArchivo(arbol_bin_busqueda *a)
{

}
void cargarArchivo(arbol_bin_busqueda *a)
{

}