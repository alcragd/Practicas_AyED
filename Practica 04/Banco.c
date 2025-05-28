#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cola Dinamica/TADColaDin.h"
#include "Presentacion/presentacion.h"
#include "Utils/consola_utils.h"
#include <time.h>

#define TIEMPO_BASE 10 // 10ms

int main()
{
    int numCajeros, *cajeros, *tiempoAtencion, tiempoCliente, tiempoUsuario, tiempoPreferente;
    int  i, noUsuarios = 0, tiempo = 0, numCliente = 0, numUsuario = 0, numPreferente = 0;
    cola clientes, usuarios, preferentes;
    elemento e;

    Initialize(&clientes);
    Initialize(&usuarios);
    Initialize(&preferentes);

    printf("\nIngrese el numero de cajeros:\n>> ");
    scanf("%d", &numCajeros);
    while (numCajeros < 1 || numCajeros > 10)
    {
        printf("\n[*]-- El numero de cajeros debe estar entre 1 y 10\n>> ");
        scanf("%d", &numCajeros);
    }

    tiempoAtencion = malloc(numCajeros * sizeof(int));
    cajeros = calloc(numCajeros, sizeof(int));

    for (i = 0; i < numCajeros; i++)
    {
        printf("\nIngrese el tiempo de atencion del cajero %d en milisegundos: \n>> ", i + 1);
        scanf("%d", &tiempoAtencion[i]);

        while (tiempoAtencion[i] % 10 != 0)
        {
            printf("\n[*]-- El tiempo de atencion debe ser un multiplo de 10 \n>> ");
            scanf("%d", &tiempoAtencion[i]);
        }
    }

    printf("\nIngrese el tiempo de llegada de los clientes del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoCliente);

    while (tiempoCliente % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoCliente);
    }

    printf("\nIngrese el tiempo de llegada de los usuarios del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoUsuario);

    while (tiempoUsuario % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoUsuario);
    }

    printf("\nIngrese el tiempo de llegada de los clientes preferentes del banco en milisegundos:\n>>  ");
    scanf("%d", &tiempoPreferente);

    while (tiempoPreferente % 10 != 0)
    {
        printf("\n[*]-- El tiempo de llegada debe ser un multiplo de 10\n>> ");
        scanf("%d", &tiempoPreferente);
    }

    printf("\n");
    system("pause");

    BorrarPantalla();
    ocultarCursor();

    while(1)
    {
		EsperarMiliSeg(TIEMPO_BASE); // Esperar el tiempo base
        tiempo++;

		if(tiempo * 10 % tiempoCliente == 0)
		{
			numCliente ++;
			e.i = numCliente;
            e.tipo='C';
			Queue(&clientes, e);
		}
		if(tiempo * 10 % tiempoUsuario == 0)
		{
			numUsuario ++;
			e.i = numUsuario;
            e.tipo='U';
			Queue(&usuarios, e);
		}
		if(tiempo * 10 % tiempoPreferente == 0)
		{
			numPreferente ++;
			e.i = numPreferente;
            e.tipo='P';
			Queue(&preferentes, e);
		}

        for(i = 0; i < numCajeros; i++)
        {
			if(cajeros[i] == 1)
			{
				if (tiempo * 10 % tiempoAtencion[i] == 0)
           		{
               		cajeros[i] = 0;
                    //printf("Atendi a %c%d en la caja %d \n",e.tipo,e.i,i+1); No se como hacer para que sea el elemento que toca xd
           		}
			}
			else
            {
                if(noUsuarios >= 5 && !Empty(&usuarios))
                {
                    e=Dequeue(&usuarios);
                    noUsuarios = 0;
					cajeros[i] = 1;
                    printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&preferentes))
                {
                    e=Dequeue(&preferentes);
                    noUsuarios++;
					cajeros[i] = 1;
                    printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
                if(!Empty(&clientes))
                {
                    e=Dequeue(&clientes);
                    noUsuarios++;
					cajeros[i] = 1;
                    printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
                }
				if(!Empty(&usuarios))
				{
					e=Dequeue(&usuarios);
                    noUsuarios = 0;
					cajeros[i] = 1;
                    printf("Atendiendo a %c%d en la caja %d\n",e.tipo,e.i,i+1);
                    continue;
				}
            }
        }
    }
    Destroy(&usuarios);
    Destroy(&clientes);
    Destroy(&preferentes);
    return 0;
}
