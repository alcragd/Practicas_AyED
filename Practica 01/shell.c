/*
shell.c
V 1.0 Marzo 2025
Autor: Ramirez Hernandez Christian Isaac

Programa que lee n números desde la entrada estándar, los almacena en un arreglo dinámico,
aplica el algoritmo de ordenamiento Shell Sort y mide el tiempo de ejecución.

Compilación: 
Windows: gcc shell.c -o shell.exe
Linux: gcc shell.c -o shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipo de la función de ordenamiento Shell Sort
void shell(int *A, int n);

int main(int num_args, char *args[]) {
    clock_t t_inicio, t_final;
    double t_intervalo;
    int n, *A, i;
    
    // Verificación de argumentos
    if(num_args != 2) {
        exit(1);
    }
    
    // Convertir argumento a entero
    n = atoi(args[1]);
    
    // Reservar memoria dinámicamente
    A = malloc(n * sizeof(int));
    if(A == NULL) {
        printf("\n[!]-- Error al asignar memoria\n");
        exit(1);
    }
    
    // Leer los valores del arreglo
    for(i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // Inicia medición del tiempo
    t_inicio = clock();
    shell(A, n);
    t_final = clock();
    
    // Calcular tiempo transcurrido
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    
    // Imprimir el arreglo ordenado
    printf("\nArreglo ordenado:\n");
    for(i = 0; i < n; i++) {
        printf("%d\n", A[i]);
    }
    
    // Liberar memoria y mostrar tiempo de ejecución
    free(A);
    printf("\nTiempo medido: %.10f segundos.\n", t_intervalo);
    return 0;
}

/*
void shell(int *A, int n)
Recibe: int * Referencia al arreglo A, int tamaño del arreglo
Devuelve: void (No retorna valor explícito)
Observaciones: Ordena el arreglo usando el algoritmo Shell Sort.
*/
void shell(int *A, int n) {
    int k = n / 2, b, i, temp;
    while(k >= 1) {
        b = 1;
        while(b != 0) {
            b = 0;
            for(i = k; i <= n - 1; i++) {
                if(A[i - k] > A[i]) {
                    temp = A[i];
                    A[i] = A[i - k];
                    A[i - k] = temp;
                    b++;
                }
            }
        }
        k = k / 2;
    }
}



