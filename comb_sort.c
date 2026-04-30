/*
CODIGO DE: https://fvcalderan.github.io/myworks/articles/comb_sort.pdf

cmp = comparaciones
mov = movimientos/intercambios 
gap = distancia entre los elementos comparados
n = tamaño del arreglo (cantidad de elementos a ordenar)
sm = indice del elemento lejano
aux = variable temporal para intercambiar 

EXPLICACION DEL ALGORITMO: https://www.youtube.com/watch?v=DX-dXwtIGa0

*/

#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct{
    uint64_t cmp;
    uint64_t mov;
} sort;

sort comb_sort(int *A, int n){
    int sorted = 0, gap = n, i , sm, aux;
    sort s = {.cmp = 0, .mov = 0};

    while(!sorted){
        gap = (int)floor(gap/1.3);
        if(gap <= 1){
            gap = 1;
            sorted = 1;
        }

        for(i = 0; i < n - gap; i++){
            sm = gap + i;
            if(s.cmp++, A[i] > A[sm]){
                aux = A[sm];
                A[sm] = A[i];
                A[i] = aux;
                s.mov += 3;
                sorted = 0;
            }
        }
    }
    return s;
}

int main(){
    int A[] = {40,28,23,5,5,17,80};
    int n = 7;

    sort s = comb_sort(A,n);

    for (int i = 0; i < n; i++){
        printf("%d", A[i]);
    }

    printf("\n Comparaciones: %llu\n", s.cmp);
    printf("\n Movimientos: %llu\n", s.mov);

    return 0;
}