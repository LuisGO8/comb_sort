/*
CODIGO EXTRAIDO DE: https://fvcalderan.github.io/myworks/articles/comb_sort.pdf

cmp = comparaciones
mov = movimientos/intercambios 
gap = distancia entre los elementos comparados
n = tamaño del arreglo (cantidad de elementos a ordenar)
sm = indice del elemento lejano
aux = variable temporal para intercambiar 

EXPLICACION DEL ALGORITMO: https://www.youtube.com/watch?v=DX-dXwtIGa0



PARA REALIZAR LAS PRUEBAS
int n = 1000000;
int A[n];

for(int i = 0; i<n; i++){
    A[i] = rand() % 1000000
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

typedef struct {
    uint64_t cmp;
    uint64_t mov;
} sort;

sort comb_sort(int *A, int n) {
    
    const double factor = 1.3;
    int gap = n;
    int swapped = 1;
    sort s = {0, 0};

    while (gap > 1 || swapped) {
         gap = (int)(gap / factor);
        if (gap < 1) gap = 1;
        
        swapped = 0;

         for (int i = 0; i < n - gap; i++) {
            s.cmp++;
            if (*(A + i) > *(A + i + gap)) {
                int aux = *(A + i);
                *(A + i) = *(A + i + gap);
                *(A + i + gap) = aux;
                
                s.mov += 3;
                swapped = 1;
            }
        }
    }
    return s;
}

int *nuevoArr(int orden) {
    int *ptr = (int *)malloc(orden * sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }
    for (int i = 0; i < orden; i++)
        *(ptr + i) = (rand() % 200000) + 1;
    return ptr;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <tamaño_de_lista>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    int orden = atoi(argv[1]);

        int *ptr = nuevoArr(orden);
        
        printf("Valores generados...\n");
        for (int i = 0; i < orden; i++)
            printf("%6d ", *(ptr+i));
        

        clock_t inicio = clock();
        sort s = comb_sort(ptr, orden);
        clock_t fin = clock();

        
        printf("\nValores ordenados...\n");
        for (int i = 0; i < orden; i++)
            printf("%6d ", *(ptr+i));
        
        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("\n\nResultados para %d elementos:", orden);
        printf("\nTiempo: %.6f s", tiempo);
        printf("\nComparaciones: %llu", (unsigned long long)s.cmp);
        printf("\nMovimientos: %llu\n", (unsigned long long)s.mov);

        free(ptr);
    return 0;
}