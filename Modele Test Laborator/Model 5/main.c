#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char nume[31];
    char clasa_zbor;
    float greutate_bagaj;
    unsigned int cod : 3; // A = 65 -> z = 122 ( 122 - 7 biti) => codul nu poate fi mai mare de 7 (111 - in binar) => 3 biti
} Pasager;

void citire(int nrP, Pasager p[]) {
    for (int i = 0; i < nrP; i++) {
        int cond = 0;

        // NUME
        printf("Numele pasagerului %d: ", i + 1);
        scanf("%s", p[i].nume);

        // CLASA_ZBOR
        printf("Clasa de zbor(A/B/C/D) a pasagerului %d: ", i + 1);
        char ch = fgetc(stdin);
        scanf("%c", &p[i].clasa_zbor);
        if (p[i].clasa_zbor == 'A' || p[i].clasa_zbor == 'B' || p[i].clasa_zbor == 'C' || p[i].clasa_zbor == 'D') cond = 1;
        else {
            printf("Exista doar patru clase, A, B, C si D!\n Tastati din nou: ");
            char ch = fgetc(stdin);
            while (!cond) {
                scanf("%c", &p[i].clasa_zbor);
                if (p[i].clasa_zbor == 'A' || p[i].clasa_zbor == 'B' || p[i].clasa_zbor == 'C' || p[i].clasa_zbor == 'D') cond = 1;
                else {
                    printf("Exista doar patru clase, A, B, C si D!\n Tastati din nou: ");
                    char ch = fgetc(stdin);
                }
            }
        }

        // BAGAJ
        cond = 0;
        printf("Greutatea bagajului pasagerului %d: ", i + 1);
        scanf("%f", &p[i].greutate_bagaj);
        if(p[i].greutate_bagaj <= 100) cond = 1;
        else {
            printf("Limita maxima este 500!\n Tastati din nou: ");
            while(!cond) {
                scanf("%f", &p[i].greutate_bagaj);
                if(p[i].greutate_bagaj <= 100) cond = 1;
                else printf("Limita maxima este 500!\n Tastati din nou: ");
            }
        }
    }
}

void afisare(int nrP, Pasager p[]) {
    for(int i = 0 ; i < nrP ; i++)
        printf("%s %c %.2f %u\n", p[i].nume, p[i].clasa_zbor, p[i].greutate_bagaj, p[i].cod);
}

unsigned int codPasager(char ch) {
    if(!ch) return 0;
    return (ch & 1 ? 0 : 1) + codPasager(ch >> 1);
}

void completareDate(int nrP, Pasager p[]) {
    for(int i = 0 ; i < nrP ; i++)
        p[i].cod = codPasager(p[i].nume[0]);
}

int cmpClasa(const void* pa, const void* pb) {
    Pasager* p1 = (Pasager*)pa;
    Pasager* p2 = (Pasager*)pb;

    if(p1->clasa_zbor < p2->clasa_zbor) return -1;
    if(p1->clasa_zbor > p2->clasa_zbor) return 1;
    return 0; // if(p1->clasa_zbor == p2->clasa_zbor)
}

void sortareClasa(int nrP, Pasager p[]) {
    qsort(p, nrP, sizeof(Pasager), cmpClasa);
    afisare(nrP, p);
}

void citirePasageri(FILE* fin) {
    char nume[31];
    char clasa;
    float greutate;

    while(fscanf(fin, "%s %c %f", nume, &clasa, &greutate) == 3) {
        if(greutate >= 30) printf("%s\n", nume);
    }
}

int main() {
    int nrP;
    Pasager p[100];

    printf("Numarul pasagerilor: ");
    scanf("%d", &nrP);

    citire(nrP, p);
    completareDate(nrP, p);
    afisare(nrP, p);

    printf("\n\n DUPA SORTARE:\n");
    sortareClasa(nrP, p);

    printf("\n\n FISIER:\n");
    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 5\\pasageri.txt", "r");
    assert(fin != NULL);

    citirePasageri(fin);

    fclose(fin);

    return 0;
}
