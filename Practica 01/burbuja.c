#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define SI 1
#define NO 0

void BurbujaOptimizada(int n, int *A);


int main(int num_args, char *args[]){
    if(num_args!=2)
        exit(1);

    clock_t t_inicio, t_final;
    double t_intervalo;
    int n, i, *A;
    n=atoi(args[1]);
    A=malloc(sizeof(int)*n);
    if(A==NULL){
        printf("\n[!]-- Error al asignar memoria");
        exit(1);
    }
    for(i=0;i<n;i++){
        scanf("%d",&A[i]);
    }

    for(i=0;i<n;i++){
        printf("%d\n",A[i]);
    }
    //Inicia medición del tiempo
	t_inicio = clock();
	
	//Llamar al algoritmo
	BurbujaOptimizada(n,A);
	
	//Termina medición del tiempo	
	t_final = clock();
	
	//Cálculo del tiempo y enviar mensaje a salida estandar con la medición  
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    

    printf("\n\nORDENADO:\n");
    for(i=0;i<n;i++){
        printf("%d\n",A[i]);
    }
    free(A);
    printf("\n\nTiempo medido: %.8f segundos.", t_intervalo);
}

void BurbujaOptimizada(int n, int *A){
    int i,j,aux,cambios;
    i=0;
    cambios=SI;
    while (i<=n-2 && cambios!=NO)
    {
        cambios=NO;
        for(j=0;j<=(n-2)-i;j++){
            if(A[j]>A[j+1]){
                aux=A[j];
                A[j]=A[j+1];
                A[j+1]=aux;
                cambios=SI;
            }
        }
        i++;
    }
}