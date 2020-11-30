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
        printf("Clasa de zbor(A/B) a pasagerului %d: ", i + 1);
        char ch = fgetc(stdin);
        scanf("%c", &p[i].clasa_zbor);
        if (p[i].clasa_zbor == 'A' || p[i].clasa_zbor == 'B') cond = 1;
        else {
            printf("Exista doar doua clase, A si B!\n Tastati din nou: ");
            char ch = fgetc(stdin);
            while (!cond) {
                scanf("%c", &p[i].clasa_zbor);
                if (p[i].clasa_zbor == 'A' || p[i].clasa_zbor == 'B') cond = 1;
                else {
                    printf("Exista doar doua clase, A si B!\n Tastati din nou: ");
                    char ch = fgetc(stdin);
                }
            }
        }

        // BAGAJ
        cond = 0;
        printf("Greutatea bagajului pasagerului %d: ", i + 1);
        scanf("%f", &p[i].greutate_bagaj);
        if(p[i].greutate_bagaj <= 500) cond = 1;
        else {
            printf("Limita maxima este 500!\n Tastati din nou: ");
            while(!cond) {
                scanf("%f", &p[i].greutate_bagaj);
                if(p[i].greutate_bagaj <= 500) cond = 1;
                else printf("Limita maxima este 500!\n Tastati din nou: ");
            }
        }
    }
}

void afisare(int nrP, Pasager p[]) {
    for(int i = 0 ; i < nrP ; i++)
        printf("%s %c %.2f %u\n", p[i].nume, p[i].clasa_zbor, p[i].greutate_bagaj, p[i].cod);
}

// recursiva
unsigned int codPasager1(char ch) {
    if(!ch) return 0;
    return (ch & 1 ? 0 : 1) + codPasager1(ch >> 1);
}

void completareDate(int nrP, Pasager p[]) {
    for(int i = 0 ; i < nrP ; i++)
        p[i].cod = codPasager1(p[i].nume[0]);
}

int cmpGreutate(const void* pa, const void* pb) {
    Pasager* p1 = (Pasager*)pa;
    Pasager* p2 = (Pasager*)pb;

    if(p1->greutate_bagaj > p2->greutate_bagaj) return -1;
    if(p1->greutate_bagaj < p2->greutate_bagaj) return 1;
    return 0; // if(p1->greutate_bagaj == p2->greutate_bagaj)
}

void sortareGreutate(int nrP, Pasager p[]){
    qsort(p, nrP, sizeof(Pasager), cmpGreutate);
    afisare(nrP, p);
}

void citirePasageri(FILE* finNume, FILE* finClasa, FILE* finGreutate) {
    // mutam pointerul finClasa pe randul urmator
    fscanf(finClasa, "%*[^\n]\n");

    //  mutam pointerul finGreutate doua randuri
    fscanf(finGreutate, "%*[^\n]\n");
    fscanf(finGreutate, "%*[^\n]\n");

    char nume[31];
    char clasa[2];
    float greutate;

    while(fscanf(finNume, "%s", nume) == 1 && fscanf(finClasa, "%s", clasa) == 1 && fscanf(finGreutate, "%f", &greutate) == 1) {
        //printf("----%s %c %.2f\n", nume, clasa, greutate);
        if(clasa[0] == 'B' && greutate >= 30)
            printf("%s\n", nume);
    }
}

int main() {
    /*int nrP;
    Pasager p[100];

    printf("Numarul pasagerilor: ");
    scanf("%d", &nrP);

    citire(nrP, p);
    completareDate(nrP, p);
    afisare(nrP, p);

    printf("\n\nDUPA SORTARE:\n");
    sortareGreutate(nrP, p);
*/
    printf("\n\nAFISARE DIN FISIER:\n");

    FILE* finNume = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 6\\pasageri.txt", "r");
    assert(finNume != NULL);
    FILE* finClasa = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 6\\pasageri.txt", "r");
    assert(finClasa != NULL);
    FILE* finGreutate = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 6\\pasageri.txt", "r");
    assert(finGreutate != NULL);

    citirePasageri(finNume, finClasa, finGreutate);

    fclose(finNume);
    fclose(finClasa);
    fclose(finGreutate);
    return 0;
}
