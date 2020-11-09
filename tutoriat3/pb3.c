#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void alocMatrice(int ***a, int *n) {
    scanf("%d", n);
    *a = (int**)malloc(*n * sizeof(int*));
    assert(*a != NULL);

    for(int i = 0 ; i < *n ; i++) {
        (*a)[i] = (int*)malloc(*n * sizeof(int));
        assert((*a)[i] != NULL);
    }
}

void spirala(int **a, int n) {
   int nrRame = (n % 2 == 0 ? n / 2 : n / 2 + 1);

   for(int i = 0 ; i < nrRame ; i++) {
       
        // latura de sus
        for(int j = i ; j < n - i ; j++) 
            printf("%d ", a[i][j]);

        // latura din dreapta
        for(int j = i + 1 ; j < n - i ; j++)
            printf("%d ", a[j][n - i - 1]);

        // latura de jos
        for(int j = n - i - 2 ; j >= i ; j--) 
            printf("%d ", a[n - i - 1][j]);

        // latura din stanga
        for(int j = n - i - 2 ; j >= i + 1 ; j--)
            printf("%d ", a[j][i]);
   }

}

void citesteMatrice(int ***a, int n) {
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            scanf("%d", &(*a)[i][j]);
}

int main() {
    int **a, n;
    alocMatrice(&a, &n);
    citesteMatrice(&a, n);
    spirala(a, n);

    for(int i = 0 ; i < n ; i++) 
        free(a[i]);
    free(a);
    return 0;
}