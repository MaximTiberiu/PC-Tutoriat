#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

typedef struct {
    char nume[30];
    int gps_x;
    int gps_y;
} Magazin;

typedef struct {
    char nume[30];
    float pret;
    Magazin *m;
    int nrMagazine;
} Produs;

struct Nod {
    Produs data;
    struct Nod *next;
};

Produs* citireProduse(int* nrProduse) {
    printf("Introduceti numarul de produse: ");
    scanf("%d", nrProduse);

    Produs *p = (Produs*)malloc(*nrProduse * sizeof(Produs));
    assert(p != NULL);

    for(int i = 0 ; i < *nrProduse ; i++) {
        printf("Produsul %d\n", i + 1);

        printf("Nume produs: ");
        scanf("%s", p[i].nume);

        printf("Pret produs: ");
        scanf("%f", &p[i].pret);

        int nrMagazine;
        printf("Numar magazine: ");
        scanf("%d", &p[i].nrMagazine);

        if(p[i].nrMagazine > 0) {
            p[i].m = (Magazin *) malloc(p[i].nrMagazine * sizeof(Magazin));
            assert(p[i].m != NULL);
            for (int j = 0; j < p[i].nrMagazine; j++) {
                printf("Magazinul %d\n", j + 1);
                int x = getc(stdin);
                printf("Nume magazin: ");
                scanf("%s", p[i].m[j].nume);

                printf("Coordonate magazin (x, y): ");
                scanf("%d %d", &p[i].m[j].gps_x, &p[i].m[j].gps_y);
            }
        }
    }
    return p;
}

void afisare(Produs* p, int nrProduse) {
    for(int i = 0 ; i < nrProduse ; i++) {
        printf("Produsul %d\n", i + 1);

        printf("\tNume produs: %s\n", p[i].nume);

        printf("\tPret produs: %.2f\n", p[i].pret);

        for(int j = 0 ; j < p[i].nrMagazine ; j++) {
            printf("\t Magazinul %d\n", j + 1);

            printf("\t\tNume magazin: %s\n", p[i].m[j].nume);

            printf("\t\tCoordonate magazin (x, y): %d, %d\n", p[i].m[j].gps_x, p[i].m[j].gps_y);
        }
    }
}

float distanta(int gps_x, int gps_y, int gpsC_x, int gpsC_y) {
    return sqrt((gps_x - gpsC_x) * (gps_x - gpsC_x) + (gps_y - gpsC_y) * (gps_y - gpsC_y));
}

void cautareInMagazin(char* produs, int gpsC_x, int gpsC_y, int nrProduse, Produs *p) {
    Produs *tempP = NULL;
    float distMin = -1; // initializare distMin cu o valoare negativa
    int index;
    for(int i = 0 ; i < nrProduse ; i++) { // parcurgem lista de produse
        if (strcmp(produs, p[i].nume) == 0) { // verificam daca este produsul dorit
            tempP = &p[i]; // il stocam intr-o variabila de tip Produs*
            if (tempP->nrMagazine > 0) { // verificam daca exista magazine care au acest produs
                if(distMin == -1) {// daca disatMin este -1, inseamna ca e primul magazin in care gasim acest produs, deci facem initializarea ca sa avem un reper
                    distMin = distanta(tempP->m[0].gps_x, tempP->m[0].gps_y, gpsC_x, gpsC_y);
                    index = 0; // stocam indicele din vectorul de magazine
                }
                for (int j = 0; j < tempP->nrMagazine; j++) { // parcurgem magazinele
                    float dist = distanta(tempP->m[j].gps_x, tempP->m[j].gps_y, gpsC_x, gpsC_y); // calculam distanta pana la magazin
                    if (dist < distMin) { // verificare distanta minima, daca se inteplineste, distanta si indicele magazinului
                        distMin = dist;
                        index = j;
                    }
                }
            }
        }
    }
    if(tempP == NULL)
        printf("Nu am gasit produsul cautat!\n"); // tempP ramane null, rezulta ca nu sunt magazine in care se gaseste produsul cautat
    else
        printf("Cel mai apropiat magazin in care gasiti produsul \"%s\" este: %s, la coordonatele (%d, %d)\n",
               produs, tempP->m[index].nume, tempP->m[index].gps_x, tempP->m[index].gps_y);
}

int compPret(const void* a, const void* b) {
    Produs* a1 = (Produs*)a;
    Produs* b1 = (Produs*)b;

    if(a1->pret == b1->pret)
        return a1->nrMagazine < b1->nrMagazine;
    return a1->pret > b1->pret;
}

void ordoneazaProduse(int nrProduse, Produs *p) {
    qsort(p, nrProduse, sizeof(Produs), compPret);
    afisare(p, nrProduse);
}

struct Nod* inserareInLista(int nrProduse, Produs *p) {
    struct Nod *head, *prev, *temp;
    head = NULL;
    for(int i = 0 ; i < nrProduse ; i++) {
        temp = (struct Nod*)malloc(sizeof(struct Nod));
        assert(temp != NULL);
        temp->data = p[i];
        temp->next = NULL;

        if(head == NULL)
            head = temp;
        else
            prev->next = temp;
        prev = temp;
    }
    return head;
}

int cautaMagazine(int n, Magazin* m, char *nume) {
    for(int i = 0 ; i < n ; i++)
        if(strcmp(m[i].nume, nume) == 0) return 1;
    return 0;
}

void eliminare(struct Nod **L, char *nume) {
    struct Nod *temp = *L, *prev;

    while(temp != NULL && cautaMagazine(temp->data.nrMagazine, temp->data.m, nume) == 1)
    {
        *L = temp->next;
        free(temp);
        temp = *L;
    }

    while(temp != NULL) {
        while(temp != NULL && cautaMagazine(temp->data.nrMagazine, temp->data.m, nume) == 0) {
            prev = temp;
            temp = temp->next;
        }

        if(temp != NULL) return; // nu avem magazine
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

void afisareLista(struct Nod *L) {
    printf("Lista este:\n");
    while(L != NULL) {
        printf("Nume produs: %s; Pret produs: %.2f\n", L->data.nume, L->data.pret);
        L = L->next;
    }
}

int main() {
    int nrProduse;
    Produs *p;
    p = citireProduse(&nrProduse);

    printf("Afisare produse:\n");
    afisare(p, nrProduse);

    printf("--------------------------------\nCautare produs in magazin:\n");
    cautareInMagazin("lapte", 12, 19, nrProduse, p);

    printf("--------------------------------\nOrdonare produse:\n");
    ordoneazaProduse(nrProduse, p);

    printf("--------------------------------\nStergere produse din lista:\n");
    struct Nod *head = inserareInLista(nrProduse, p);
    afisareLista(head);
    eliminare(&head, "lidl");
    afisareLista(head);

    return 0;
}
