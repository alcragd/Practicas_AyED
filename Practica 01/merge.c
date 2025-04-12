#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void MergeSort(int *A, int p, int r);
void Merge(int *A, int p, int q, int r);

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
    
        /*for(i=0;i<n;i++){
            printf("%d\n",A[i]);
        }*/
        //Inicia medición del tiempo
        t_inicio = clock();
        
        //Llamar al algoritmo
        MergeSort(A,0,n-1);
        
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

void MergeSort(int *A, int p, int r){
    int q;
    if(p<r){
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}

void Merge(int *A, int p, int q, int r){
    int i,j,l,k,*C;
    l=r-p+1;
    i=p;
    j=q+1;
    C=malloc(l*sizeof(int));
    for(k=0;k<=(l-1);k++){
        if(i<=q&&j<=r){
            if(A[i]<A[j]){
                C[k]=A[i];
                i++;
            }
            else{
                C[k]=A[j];
                j++;
            }
        }
        else if(i<=q){
            C[k]=A[i];
            i++;
        }
        else {
            C[k]=A[j];
            j++;
        }
    }
    k=p;
    for(i=0;i<=(l-1);i++){
        A[k]=C[i];
        k++;
    }
    free(C);
}
