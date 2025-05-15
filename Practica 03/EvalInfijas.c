/*
================================================================================
EvalInfijas.c
Versión: 1.0
Fecha: Mayo 2025
Autores: Coyol Moreno Angel Zoe | Ramirez Hernandez Christian Isaac | Ramos Mendoza Miguel Angel

Descripción:
-----------
Este programa evalúa expresiones matemáticas en notación infija. Convierte la
expresión infija a postfija, solicita valores para las variables y evalúa el
resultado de la expresión postfija.

El programa utiliza una pila dinámica para manejar operadores y operandos,
y valida la correcta apertura y cierre de paréntesis en la expresión.

Compilación:
------------
Pila Estatica:
    Windows: gcc -o EvalInfijas.exe EvalInfijas.c ./pila_estatica/pila_est.c
    Linux/Mac: gcc -o EvalInfijas EvalInfijas.c ./pila_estatica/pila_est.c
Pila Dinamica:
    Windows: gcc -o EvalInfijas.exe EvalInfijas.c ./pila_dinamica/pila_din.c
    Linux/Mac: gcc -o EvalInfijas EvalInfijas.c ./pila_dinamica/pila_din.c
Uso:
----
./EvalInfijas.exe "EXPRESION"

Donde:
  - EXPRESION es la expresión matemática en notación infija.
  - Las variables deben estar en el rango de A-Z.
  - La expresión debe estar entre comillas si contiene paréntesis.

Salida:
-------
El programa imprime la expresión en notación postfija y el resultado de su evaluación.

Observaciones:
--------------
- La expresión debe ser válida y no contener espacios.
- Las operaciones soportadas son: +, -, *, /, ^ y paréntesis.
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #define double long double

#include "pila_dinamica/pila_din.h"

// #include "pila_estatica/pila_est.h"

#define INF INFINITY

void infijoAPostfijo(char *expr, char *postfijo);
void pedirValores(char *expr, double *valores);
double EvalPostfija(char *expr, double *valores);
boolean ValidaParentesis(char *expr);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("[!]-- ERROR: Numero de argumentos incorrecto\n");
        printf("    USO: %s _EXPRESIÓN_\n", argv[0]);
        printf("    Sin espacios\n");
        printf("    Letras de A-Z\n");
        printf("    Ejemplo: %s A+B*C\n", argv[0]);
        printf("    En caso de contener parentesis enviar la expresión entre comillas.\n");
        printf("    Ejemplo: %s \"(A+B)*C\"\n", argv[0]);

        exit(1);
    }

    char *expr, *postfijo;
    double *valores, res;
    expr = malloc(strlen(argv[1]) + 1);
    postfijo = malloc(strlen(argv[1]) + 1);
    valores = malloc(('Z' - 'A' + 1) * sizeof(double));
    strcpy(expr, argv[1]);

    if (!ValidaParentesis(expr))
    {
        printf("\nError al validar parentesis.");
        exit(1);
    }

    infijoAPostfijo(expr, postfijo);

    printf("\nExpresión Postfija: %s", postfijo);

    pedirValores(postfijo, valores);

    res = EvalPostfija(postfijo, valores);

    if (res != INF)
        printf("\nResultado: %.2lf", res);
    else
        exit(1);

    free(expr);
    free(postfijo);
    free(valores);

    return 0;
}

/*
--------------------------------------------------------------------------------
void infijoAPostfijo(char *expr, char *postfijo)
--------------------------------------------------------------------------------
Descripción:
  Convierte una expresión en notación infija a notación postfija utilizando una
  pila para manejar operadores y paréntesis.

Recibe:
  - `expr`: Cadena con la expresión en notación infija.
  - `postfijo`: Cadena donde se almacenará la expresión en notación postfija.

Devuelve:
  - Nada. Modifica directamente la cadena `postfijo`.
--------------------------------------------------------------------------------
*/
void infijoAPostfijo(char *expr, char *postfijo)
{
    pila operadores;
    elemento e, top;
    int i, j = 0;
    Initialize(&operadores);

    for (i = 0; i < strlen(expr); i++)
    {
        if (expr[i] >= 'A' && expr[i] <= 'Z') // if(expr[i]!='(' && expr[i]!=')' && expr[i]!='*' && expr[i]!='/' && expr[i]!='+' && expr[i]!='-' && expr[i]!='^')
            postfijo[j++] = expr[i];
        else if (expr[i] == '(')
        {
            e.op = '(';
            e.priority = 0;
            Push(&operadores, e);
        }
        else if (expr[i] == ')')
        {
            while (Top(&operadores).op != '(')
                postfijo[j++] = Pop(&operadores).op;

            Pop(&operadores); // Sacar el parentesis de apertura de la pila
        }
        else
        {
            e.op = expr[i];

            // ^   prioridad 3
            // *,/ prioridad 2
            // +,- prioridad 1
            switch (expr[i])
            {
            case '^':
                e.priority = 3;
                break;
            case '*':
            case '/':
                e.priority = 2;
                break;
            case '+':
            case '-':
                e.priority = 1;
                break;
            }

            if (!Empty(&operadores))
                top = Top(&operadores);

            if (Empty(&operadores) || top.priority < e.priority)
                Push(&operadores, e);
            else
            {
                if (expr[i] == '^')
                {
                    /*
                    Las potencias se agrupan o asocian de derecha a izquierda,
                    ej: A^B^C = A^(B^C) != (A^B)^C
                    por lo que sacar una potencia de la pila al intentar meter otra
                    (porque tienen la misma prioridad) seria incorrecto.
                    */
                    while (!Empty(&operadores) && Top(&operadores).priority > e.priority)
                        postfijo[j++] = Pop(&operadores).op;
                }
                else
                {
                    while (!Empty(&operadores) && Top(&operadores).priority >= e.priority)
                        postfijo[j++] = Pop(&operadores).op;
                }
                Push(&operadores, e);
            }
        }
    }
    while (!Empty(&operadores))
        postfijo[j++] = Pop(&operadores).op;

    postfijo[j] = '\0'; // Indicar el fin de la cadena postfijo para no imprimir basura

    Destroy(&operadores);
    return;
}

/*
--------------------------------------------------------------------------------
void pedirValores(char *expr, double *valores)
--------------------------------------------------------------------------------
Descripción:
  Solicita al usuario los valores de las variables presentes en la expresión
  postfija.

Recibe:
  - `expr`: Cadena con la expresión en notación postfija.
  - `valores`: Arreglo donde se almacenarán los valores de las variables.

Devuelve:
  - Nada. Modifica directamente el arreglo `valores`.
--------------------------------------------------------------------------------
*/
void pedirValores(char *expr, double *valores)
{
    if (expr[0] == '\0')
        return;
    int i, len;
    for (i = 0; i <= 'Z' - 'A'; i++)
        valores[i] = INF;

    printf("\nAsignar valores:\n");

    len = strlen(expr);
    for (i = 0; i < len; i++)
    {
        if (expr[i] >= 'A' && expr[i] <= 'Z' && valores[expr[i] - 'A'] == INF)
        {
            printf("%c = ", expr[i]);
            scanf("%lf", &valores[expr[i] - 'A']);
        }
    }
}

/*
--------------------------------------------------------------------------------
double EvalPostfija(char *expr, double *valores)
--------------------------------------------------------------------------------
Descripción:
  Evalúa una expresión en notación postfija utilizando una pila para manejar
  los operandos.

Recibe:
  - `expr`: Cadena con la expresión en notación postfija.
  - `valores`: Arreglo con los valores de las variables.

Devuelve:
  - El resultado de la evaluación de la expresión.
--------------------------------------------------------------------------------
*/
double EvalPostfija(char *expr, double *valores)
{
    if (expr[0] == '\0')
        return 0;
    pila operandos;
    elemento e;
    double op1, op2, result;
    int i, len;

    Initialize(&operandos);
    len = strlen(expr);

    for (i = 0; i < len; i++)
    {
        if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            e.val = valores[expr[i] - 'A'];
            Push(&operandos, e);
        }
        else
        {
            if (!Empty(&operandos))
                op2 = Pop(&operandos).val;
            else
            {
                result = INF;
                break;
            }

            if (!Empty(&operandos))
                op1 = Pop(&operandos).val;
            else
            {
                result = INF;
                break;
            }
            switch (expr[i])
            {
            case '^':
                e.val = pow(op1, op2);
                break;
            case '*':
                e.val = op1 * op2;
                break;
            case '/':
                e.val = op1 / op2;
                break;
            case '+':
                e.val = op1 + op2;
                break;
            case '-':
                e.val = op1 - op2;
                break;
            }
            Push(&operandos, e);
        }
    }
    if (result == INF)
        printf("\nExpresión invalida: Demasiados operadores.");

    if (!Empty(&operandos))
    {
        result = Pop(&operandos).val;
        if (!Empty(&operandos))
        {
            printf("\nExpresión invalida: Muy pocos operadores."); // AB*AAA
            result = INF;
        }
    }

    Destroy(&operandos);
    return result;
}

/*
--------------------------------------------------------------------------------
boolean ValidaParentesis(char *expr)
--------------------------------------------------------------------------------
Descripción:
  Valida que los paréntesis en la expresión estén correctamente balanceados.

Recibe:
  - `expr`: Cadena con la expresión en notación infija.

Devuelve:
  - `TRUE` si los paréntesis están balanceados.
  - `FALSE` en caso contrario.
--------------------------------------------------------------------------------
*/
boolean ValidaParentesis(char *expr)
{
    pila parentesis;
    elemento e;
    char veredict[45] = "\nParentesis: OK.";
    boolean r;
    int i, len;
    r = TRUE;

    Initialize(&parentesis);
    len = strlen(expr);

    for (i = 0; i < len; i++)
    {
        if (expr[i] == '(')
            Push(&parentesis, e);
        else if (expr[i] == ')')
        {
            if (!Empty(&parentesis))
                Pop(&parentesis);
            else
            {
                strcpy(veredict, "\n[!]-- Hay parentesis sin abrir.");
                r = FALSE;
                break;
            }
        }
    }
    if (!Empty(&parentesis))
    {
        strcpy(veredict, "\n[!]-- Hay parentesis sin cerrar.");
        r = FALSE;
    }
    Destroy(&parentesis);
    printf("%s", veredict);
    return r;
}