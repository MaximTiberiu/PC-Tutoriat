#include <stdio.h>
#include <stdlib.h>

void citesteMatrice(int ***a, int *n, int *m) {
    scanf("%d %d", n, m);

    // alocam memorie pentru a[n][m]

    // alocam memorie pentru vectorul de vectori
    *a = (int**)malloc(*n * sizeof(int*));

    // alocam memorie pentru vectorii de int
    for(int i = 0 ; i < *n ; i++)
        (*a)[i] = (int*)malloc(*m * sizeof(int));

    for(int i = 0 ; i < *n ; i++)
        for(int j = 0 ; j < *m ; j++)
            scanf("%d", &(*a)[i][j]);
}

void afisareMatrice(int **a, int n, int m) {
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < m ; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void freeMatrice(int **a, int n) {
    for(int i = 0 ; i < n ; i++)
        free(a[i]);

    free(a);
}

void transpunere(int ***at, int **a, int m, int n) {
    *at = (int**)malloc(m * sizeof(int*));

    for(int i = 0 ; i < m ; i++)
        (*at)[i] = (int*)malloc(n * sizeof(int));

    for(int i = 0 ; i < m ; i++)
        for(int j = 0 ; j < n ; j++)
            (*at)[i][j] = a[j][i];
}

/* a=
  0 1 2
0 1 2 3
1 4 5 6

at=
  0 1
0 1 4
1 2 5
2 3 6
*/
int main() {
    int n, m;
    int **a, **at;

    citesteMatrice(&a, &n, &m);
    transpunere(&at, a, m, n);

    printf("\n");
    afisareMatrice(at, m, n);

    freeMatrice(a, n);
    freeMatrice(at, m);
    return 0;
}