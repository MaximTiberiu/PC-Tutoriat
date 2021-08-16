#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*void citireValoare(int* x) {
    scanf("%d", x);
}

int citireValoare1() {
    int x;
    scanf("%d", &x);
    return x;
}

void afisareValoare(int x) {
    printf("%d", x);
}

void citireVector(int** a, int* n) {
    scanf("%d", n);

    *a = (int*)malloc(*n * sizeof(int));
    assert(*a != NULL);

    for(int i = 0 ; i < *n ; i++) {
        scanf("%d", &(*a)[i]);
    }
}

int* citireVector1(int* n) {
    scanf("%d", n);

    int* a = (int*)malloc(*n * sizeof(int));
    assert(a != NULL);

    for(int i = 0 ; i < *n ; i++)
        scanf("%d", &a[i]);
    return a;
}

void afisareVector(int* a, int n) {
    for(int i = 0 ; i < n ; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void citireMatrice(int*** a, int* n, int* m) {
    scanf("%d %d", n, m);

    *a = (int**)malloc(*n * sizeof(int*));
    assert(*a != NULL);

    for(int i = 0 ; i < *n ; i++) {
        (*a)[i] = (int*)malloc(*m * sizeof(int));
        assert((*a)[i] != NULL);
    }

    for(int i = 0 ; i < *n ; i++)
        for(int j = 0 ; j < *m ; j++)
            scanf("%d", &(*a)[i][j]);
}

int** citireMatrice1(int* n, int* m) {
    scanf("%d %d", n, m);

    int** a;
    a = (int**)malloc(*n * sizeof(int*));
    assert(a != NULL);

    for(int i = 0 ; i < *n ; i++) {
        a[i] = (int*)malloc(*m * sizeof(int));
        assert(a[i] != NULL);
    }

    for(int i = 0 ; i < *n  ;i++)
        for(int j = 0 ; j < *m ; j++)
            scanf("%d", &a[i][j]);
    return a;
}

void afisareMatrice(int** a, int n, int m) {
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void freeMatrice(int** a, int n) {
    for(int i = 0 ; i < n ; i++)
        free(a[i]);
    free(a);
}*/

typedef struct {
    int nrObiecte;
    char numeObiect[30]
} grupObiecte;

// getline(buffer, max_char, stdin/fin)
// fgets(buffer, max_char, stdin/fin)

int verificareNumar(char* nr) {
    char n[] = "0123456789";
    for(int i = 0 ; i < strlen(nr) ; i++)
        if(strchr(n, nr[i]) == NULL) return 0;
    return 1;
}

grupObiecte** citireMatrice(int* n, char*** init) {
    grupObiecte** a;

    scanf("%d", n);
    a = (grupObiecte**)malloc(*n * sizeof(grupObiecte*));
    assert(a != NULL);

    *init = (char**)malloc(*n * sizeof(char*));
    assert(*init != NULL);
    for(int i = 0 ; i < *n ; i++) {
        *init[i] = (char*)malloc(2 * sizeof(char));
        assert(*init[i] != NULL);
    }

    char sep[] = " .,_-/";
    char* buffer;
    int maxSize = 1024;
    buffer = (char*)malloc(maxSize * sizeof(char));
    assert(buffer != NULL);

    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\tutoriat8\\date.in", "r");
    assert(fin != NULL);

    int nrCol = 0;
    for(int i = 0 ; i < *n ; i++) {
        nrCol = 0;
        fgets(buffer, maxSize, fin);
        char* ch = strtok(buffer, sep);
        while(ch != NULL) {
            if(verificareNumar(ch) == 1)
            {
                nrCol++;
                if(nrCol - 1 == 0)
                {
                    printf("%s", ch);
                    a[i] = (grupObiecte*)malloc(nrCol * sizeof(grupObiecte));
                    assert(a[i] != NULL);
                    a[i][nrCol - 1].nrObiecte = atoi(ch);
                    ch = strtok(NULL, sep);
                    printf("%s", ch);
                    strcpy(a[i][nrCol - 1].numeObiect, ch);
                }
                else
                {
                    printf("%s", ch);
                    a[i] = (grupObiecte*)realloc(a[i], nrCol * sizeof(grupObiecte));
                    assert(a[i] != NULL);
                    a[i][nrCol - 1].nrObiecte = atoi(ch);
                    ch = strtok(NULL, sep);
                    printf("%s", ch);
                    strcpy(a[i][nrCol - 1].numeObiect, ch);
                }
            }
            else {
                printf("%s", ch);
                *init[i][0] = ch[0];
                ch = strtok(NULL, sep);
                printf("%s", ch);
                *init[i][1] = ch[0];
            }
            ch = strtok(NULL, sep);
            printf("%s", ch);
        }
        printf("\n");
    }

    fclose(fin);
    return a;
}

int main() {
    int nrStud;
    grupObiecte **lista;
    char** initiale;

    lista = citireMatrice(&nrStud, &initiale);

    printf("%d %s\n", lista[1][1].nrObiecte, lista[1][1].numeObiect);
    printf("%c%c", initiale[1][0], initiale[1][1]);

    /* lucru cu pointer
    int a = 5;
    int* pa = &a;
    printf("%x %x %d", &a, &pa, *pa);

    vector alocat dinamic
    int* a;
    a = (int*)malloc(3 * sizeof(int)); // a = (int*)calloc(3, sizeof(int))
     assert(a != NULL);

    for(int i = 0 ; i < 3 ; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0 ; i < 3 ; i++) {
        printf("%d ", *(a + i));
    }
    printf("\n");
    free(a)*/

    /* matrice alocata dinamic
    int** b;
    int n = 2;
    b = (int**)malloc(n * sizeof(int*));
    assert(b != NULL); // acelasi lucru cu: if(b == NULL) return;
    for(int i = 0 ; i < n ; i++) {
        b[i] = (int*)malloc(n * sizeof(int));
        assert(b[i] != NULL);
    }

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            scanf("%d", &b[i][j]);

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++)
            printf("%d ", b[i][j]); // echivalent cu printf("%d ", *(*(b+i)+j));
        printf("\n");
    }
    for(int i = 0 ; i < n ; i++)
        free(b[i]);
    free(b);

     //citire valoare prin functie
    /*int x, y;
    citireValoare(&x);
    afisareValoare(x);
    y = citireValoare1();
    afisareValoare(y);*/

    /*citire vectori prin functie
    int *a, n;
    int *b = citireVector1(&n);
    //citireVector(&a, &n);
    afisareVector(b, n);
    free(b);//*/


    /* citire matrice prin functie
    int** b, **a;
    int n, m;
    //citireMatrice(&b, &n, &m);
    a = citireMatrice1(&n, &m);
    afisareMatrice(a, n, m);
    freeMatrice(a, n);*/

    // REALLOC - VECTORI
    // int* ptr = (int*)realloc(ptr, new_size);

    /*int n;
    int* b = citireVector1(&n);
    afisareVector(b, n);
    int m = n + 2;
    // int* a = (int*)realloc(a, m * sizeof(int));
    b = (int*)realloc(b, m * sizeof(int));
    b[3] = 25;
    b[4] = 35;
    afisareVector(b, m);

    int x = m - 3;
    b = (int*)realloc(b, x * sizeof(int));
    b[0] = -1;
    b[1] = 0;
    afisareVector(b, x);

    free(b);*/

    // REALLOC - MATRICE
    // n = 3, m = 2 -> n = 4, m = 3
    /*int** a;
    int n, m;
    a = citireMatrice1(&n, &m);
    afisareMatrice(a, n, m);
    printf("\n\n");
    n++;
    m++;
    a = (int**)realloc(a, n * sizeof(int*));
    for(int i = 0 ; i < n ; i++)
        a[i] = (int*)realloc(a[i], m * sizeof(int));
    for(int i = 0 ; i < m ; i++)
        a[3][i] = 4;
    for(int i = 0 ; i < n ; i++)
        a[i][2] = 4;
    afisareMatrice(a, n, m);
    printf("\n\n");

    int nn = n + 2;
    a = (int**)realloc(a, nn * sizeof(int*));
    for(int i = n ; i < nn ; i++)
        a[i] = (int*)malloc(m * sizeof(int));
    for(int i = 0 ; i < m ; i++) {
        a[n][i] = 2;
        a[n + 1][i] = 3;
    }
    afisareMatrice(a, nn, m);
    printf("\n\n");
    m--;
    for(int i = 0 ; i < nn ; i++)
        a[i] = (int *) realloc(a[i], m * sizeof(int));

    afisareMatrice(a, nn, m);
    printf("\n\n");

    n = 3;
    for(int i = n ; i < nn ; i++)
        free(a[i]);
    a = (int**)realloc(a, n * sizeof(int));
    afisareMatrice(a, n, m);
    freeMatrice(a, n);*/
    return 0;
}