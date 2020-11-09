#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} punct;

typedef struct {
    punct p1; // stanga-sus
    punct p2; // dreapta-jos
    int arie;
}dreptunghi;

void citire(dreptunghi **d, int *nr) {
    scanf("%d", nr);
    
    *d = (dreptunghi*)malloc(*nr * sizeof(dreptunghi));

    for(int i = 0 ; i < *nr ; i++) {
        // citim p1
        scanf("%d %d", &(*d)[i].p1.x, &(*d)[i].p1.y);

        // citim p2
        scanf("%d %d", &(*d)[i].p2.x, &(*d)[i].p2.y);
    }
}

void arie(dreptunghi **d, int nr) {
    for(int i = 0 ; i < nr ; i++) {
        int L = (*d)[i].p2.x - (*d)[i].p1.x;
        int l = (*d)[i].p1.y - (*d)[i].p2.y;

        (*d)[i].arie = abs(L * l);
        // printf("%d\n", (*d)[i].arie);
    }
}

int cmpArie(const void* a1, const void* a2) {
    dreptunghi* A1 = (dreptunghi*)a1;
    dreptunghi* A2 = (dreptunghi*)a2;

    return A1->arie - A2->arie;
}

void sorteaza(dreptunghi *d, int nr) {
    qsort(d, nr, sizeof(dreptunghi), cmpArie);

    for(int i = 0 ; i < nr ; i++) 
        printf("%d ", d[i].arie);
}

int main() {
    int nrDreptunghiuri;
    dreptunghi *d;
    citire(&d, &nrDreptunghiuri);
    arie(&d, nrDreptunghiuri);

    sorteaza(d, nrDreptunghiuri);
    return 0;
}