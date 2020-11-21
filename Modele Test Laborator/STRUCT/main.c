#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define prag 5
#define medieAdmitere(mate, info, bac) (4 * (mate + info) + 2 * bac) / 10.0

typedef struct {
    int nr_legitimatie;
    char nume[30];
    float nota_mate, nota_info, nota_bac, medie;
    char admis, buget;
} Candidat;

void citire(int nrC, Candidat c[], FILE* fin) {
    for(int i = 0 ; i < nrC ; i++)
        fscanf(fin, "%d %s %f %f %f", &c[i].nr_legitimatie, c[i].nume, &c[i].nota_mate, &c[i].nota_info, &c[i].nota_bac);
}


int cmpNume(const void* a, const void* b) {
    Candidat* A = (Candidat*)a;
    Candidat* B = (Candidat*)b;

    if(strcmp(A->nume, B->nume) > 0) return 1;
    return -1;

    /*
    cmp(a, b) < 0 => a < b
    cmp(a, b) = 0 => a == b
    cmp(a, b) > 0 => a > b (swap) 
    */
}

void afisare(int nrC, Candidat c[]) {
    for(int i = 0 ; i < nrC ; i++)
        printf("%d %s %.2f %c %c\n", c[i].nr_legitimatie, c[i].nume, c[i].medie, c[i].admis, c[i].buget);
}

void sortareAlfa(int nrC, Candidat c[]){
    // qsort(obiect, nrElemente, sizeof(Element), cmp)
    qsort(c, nrC, sizeof(Candidat), cmpNume);
    afisare(nrC, c);
}

void completeazaDate(int nrC, Candidat c[]) {
    for(int i = 0 ; i < nrC ; i++) {
        c[i].medie = medieAdmitere(c[i].nota_mate, c[i].nota_info, c[i].nota_bac);
        if(c[i].medie >= prag) 
            c[i].admis = 'Y';
        else
            c[i].admis = 'N';
    }
}

int cmpAdmis(const void* c1, const void* c2) {
    Candidat* ca = (Candidat*)c1;
    Candidat* cb = (Candidat*)c2;

    if(ca->medie > cb->medie) return -1;
    return 1;
}

int candAdmisi(int nrC, Candidat c[]) {
    int cAdmisi = nrC;
    nrC--;

    while(c[nrC].admis == 'N') {
        cAdmisi--;
        nrC--;
    }

    return cAdmisi; // return (nrC + 1);
}

void bugetSauTaxa(int nrC, Candidat c[]) {
    qsort(c, nrC, sizeof(Candidat), cmpAdmis);

    int cAdmisi = candAdmisi(nrC, c);

    int cBuget = (75 * cAdmisi) / 100;

    for(int i = 0 ; i < cBuget ; i++)
        c[i].buget = 'Y';
    for(int i = cBuget; i < cAdmisi ; i++)
        c[i].buget = 'N';
    for(int i = cAdmisi ; i < nrC ; i++) 
        c[i].buget = '-';
}

void afisareOptiuni() {
    printf("1. Ordonare candidati alfabaetica\n");
    printf("2. Candidat admisi la buget\n");
    printf("3. Candidati admisi la taxa\n");
    printf("4. Candidati respinsi\n");
    printf("5. Candidati dupa medie\n");
    printf("6. Iesire\n");
}

void afisari(int nrCand, Candidat c[]) {
    afisareOptiuni();
    printf("Tastati optiunea dorita: ");
    int opt;
    scanf("%d", &opt);

    while(opt != 6) {
        switch (opt)
        {
            case 1: { 
                sortareAlfa(nrCand, c);
                break;
            }
            case 2: {
                qsort(c, nrCand, sizeof(Candidat), cmpAdmis);
                int i = 0;
                while(c[i].buget == 'Y') {
                    printf("%d %s %.2f\n", c[i].nr_legitimatie, c[i].nume, c[i].medie);
                    i++;
                }
                break;
            }
            case 3: {
                for(int i = 0 ; i < nrCand ; i++) 
                    if(c[i].buget == 'N') 
                        printf("%d %s %.2f\n", c[i].nr_legitimatie, c[i].nume, c[i].medie);
                break;
            }
            case 4: {
                for(int i = 0 ; i < nrCand ; i++) 
                    if(c[i].buget == '-') 
                        printf("%d %s %.2f\n", c[i].nr_legitimatie, c[i].nume, c[i].medie);
                break;
            }
            case 5: {
                qsort(c, nrCand, sizeof(Candidat), cmpAdmis);
                afisare(nrCand, c);
                break;
            }
        }
        printf("\n\n\n");
        afisareOptiuni();
        printf("Tastati optiunea dorita: ");
        scanf("%d", &opt);
    }
}

int main() {
    Candidat c[100];
    int nrCand;

    FILE* fin = fopen("candidati.txt", "r");
    assert(fin != NULL);

    fscanf(fin, "%d", &nrCand);
    citire(nrCand, c, fin);
    fclose(fin);
    
    completeazaDate(nrCand, c);
    bugetSauTaxa(nrCand, c);
    afisari(nrCand, c);
    return 0;
}