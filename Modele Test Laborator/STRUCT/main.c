#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define prag 5
#define medieAdmitere(mate, info, bac) (4 * (mate + info) + 2 * bac) / 10.0

typedef struct {
    int nr_legitimatie;
    char nume[30];
    float nota_mate, nota_info, nota_bac, medie;
    bool admis, buget;
} Candidat;

void citire(int nrC, Candidat c[]) {
    for(int i = 0 ; i < nrC ; i++)
        scanf("%d %s %f %f %f", &c[i].nr_legitimatie, c[i].nume, &c[i].nota_mate, &c[i].nota_info, &c[i].nota_bac);
}


int cmpNume(const void* a, const void* b) {
    Candidat* A = (Candidat*)a;
    Candidat* B = (Candidat*)b;

    if(strcmp(A->nume, B->nume) < 0) return 1;
    return -1;

    /*
    cmp(a, b) < 0 => a < b
    cmp(a, b) = 0 => a == b
    cmp(a, b) > 0 => a > b (swap) 
    */
}

void afisare(int nrC, Candidat c[]) {
    for(int i = 0 ; i < nrC ; i++)
        printf("%d %s\n", c[i].nr_legitimatie, c[i].nume);
}

void sortareAlfa(int nrC, Candidat c[]){
    // qsort(obiect, nrElemente, sizeof(Element), cmp)
    qsort(c, nrC, sizeof(Candidat), cmpNume);
    afisare(nrC, c);
}

int main() {
    Candidat c[100];
    citire(5, c);
    sortareAlfa(5, c);
    return 0;
}