#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    char nume[16];
    float pret;
    char **cod;
} Produs;

struct nod {
    char**cod;
    struct nod *urm;
};

Produs* citireProduse(int *numarProduse) {
    printf("Numarul de produse: ");
    scanf("%d", numarProduse);

    Produs *p = (Produs*)malloc(*numarProduse * sizeof(Produs));
    assert(p != NULL);

    for(int i = 0 ; i < *numarProduse ; i++) {
        printf("Produsul %d\n", i + 1);
        printf("Nume produs: ");
        scanf("%s", p[i].nume);

        printf("Pret produs: ");
        scanf("%f", &p[i].pret);

        // alocare matrice char**
        p[i].cod = (char**)malloc(4 * sizeof(char*));
        assert(p[i].cod != NULL);
        for(int j = 0 ; j < 4 ; j++) {
            p[i].cod[j] = (char*)calloc(4 , sizeof(char));
            assert(p[i].cod[j] != NULL);
        }
    }
    return p;
}

void afisareProduse(int numarProduse, Produs *p) {
    for(int i = 0 ; i < numarProduse ; i++) {
        printf("Produsul %d\n", i + 1);
        printf("\tNume produs: %s\n", p[i].nume);
        printf("\tPret produs: %.2f\n", p[i].pret);

        printf("\tCod produs: \n");
        for(int j = 0 ; j < 4 ; j++) {
            printf("\t");
            for(int k = 0 ; k < 4 ; k++)
                printf("%c ", p[i].cod[j][k]);
            printf("\n");
        }
    }
}

void transpunereMatrice(char **a) {
    char aux;
    for(int i = 0 ; i < 4 ; i++)
        for(int j = i ; j < 4 ; j++)
        {
            aux = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = aux;
        }
}

void inversareElementeColoane(char **a) {
    char aux;
    for(int j = 0 ; j < 4 ; j++)
        for(int i = 0 ; i < 2 ; i++) {
            aux = a[i][j];
            a[i][j] = a[4 - i - 1][j];
            a[4 - i - 1][j] = aux;
        }
}

void completareCoduri(int numarProduse, Produs *p) {
    // pasul 1
    for(int i = 0 ; i < numarProduse ; i++) {
        int pos = 0;
        for(int j = 0 ; j < 4 ; j++)
            for(int k = 0 ; k < 4 ; k++)
                if(p[i].nume[pos])
                    p[i].cod[j][k] = p[i].nume[pos++];
                else
                    p[i].cod[j][k] = '0';
    }

    // pasul 2
    for(int i = 0 ; i < numarProduse ; i++) {
        // transpunere
        transpunereMatrice(p[i].cod);
        // inverare elemente coloane
        inversareElementeColoane(p[i].cod);
    }
}

int numaraZerouri(char **a) {
    int cnt = 0;
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < 4 ; j++)
            if(a[i][j] == '0') cnt++;
    return cnt;
}

int cmpProduse(const void* a, const void* b) {
    Produs* aa = (Produs*)a;
    Produs* bb = (Produs*)b;

    if(aa->pret == bb->pret)
        return numaraZerouri(aa->cod) < numaraZerouri(bb->cod);
    return aa->pret > bb->pret; // aa->pret - bb->pret

}

void ordonareProduse(int numarProduse, Produs *p) {
    // qsort(vector_de_sortat, numar_elemente_vector, dimensiune_element_vector_comparator)
    qsort(p, numarProduse, sizeof(Produs), cmpProduse);
    afisareProduse(numarProduse, p);
}

struct nod* inserareDataLista(Produs *p, int numarProduse) {
    struct nod *head, *prev, *temp;
    head = NULL;
    // produse = {lapte, oua, carne, biscuiti, lapte, haine...}
    for(int i = 0 ; i < numarProduse ; i++) {
        temp = (struct nod*)malloc(sizeof(struct nod));
        assert(temp != NULL);

        temp->urm = NULL;
        temp->cod = p[i].cod;

        if(head == NULL) {
            head = temp;
        }
        else {
            prev->urm = temp;
        }
        prev = temp;
    }
    return head;
}

void afisareLista(struct nod *head) {
    if(head == NULL) return;
    while(head != NULL) {
        for(int i = 0 ; i < 4 ; i++) {
            for (int j = 0; j < 4; j++)
                printf("%c ", head->cod[i][j]);
            printf("\n");
        }
        printf("----------------------\n");
        head = head->urm;
    }
}

char* decodifcare(char **a) {
    int n = 16 - numaraZerouri(a);
    char *c = (char*)malloc(n * sizeof(char));
    assert(c != NULL);
    inversareElementeColoane(a);
    transpunereMatrice(a);

    int pos = 0;
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < 4 ; j++) {
            if(a[i][j] != '0')
                c[pos++] = a[i][j];
        }
    return c;
}

void eliminare(struct nod **L, char *produs) {
    struct nod *temp, *prev;
    temp = *L;

    // imi verifica daca exista noduri la inceputul listei pe care trebuie sa le eliminam
    // L = { biscuiti, haine...}
    while(temp != NULL && strcmp(produs, decodifcare(temp->cod)) == 0) {
        *L = temp->urm;
        free(temp);
        temp = *L;
    }

    while(temp != NULL) {
        while(temp != NULL && strcmp(produs, decodifcare(temp->cod)) != 0) {
            prev = temp;
            temp = temp->urm;
        }

        if(temp == NULL) return; // nu mai sunt elemente de eliminat
        prev->urm = temp->urm;
        free(temp);
        temp = prev->urm;
    }
}

void freeMatrice(char **a) {
    for(int i = 0 ; i < 4 ; i++)
        free(a[i]);
    free(a);
}

void freeVector(Produs *p, int numarProduse) {
    for(int i = 0 ; i < numarProduse ; i++)
        free(p[i].cod);
    free(p);
}

void freeLista(struct nod *L) {
    struct nod *temp;
    while(L != NULL){
        temp = L;
        L = L->urm;
        free(temp);
    }
}

int main() {
    // ex1
    int numarProduse;
    Produs *produse = citireProduse(&numarProduse);

    // ex2
    completareCoduri(numarProduse, produse);
    afisareProduse(numarProduse, produse);

    // ex3
    printf("Afisare vector sortat: \n");
    ordonareProduse(numarProduse, produse);

    // ex4
    // produse = {lapte, oua, carne, biscuiti, lapte, haine...}
    // eliminare(&L, "lapte")
    struct nod *L = inserareDataLista(produse, numarProduse);
    afisareLista(L);
    eliminare(&L, "lapte");
    printf("\n\n\nDupa eliminare:\n");
    afisareLista(L);
    freeVector(produse, numarProduse);
    freeLista(L);
    return 0;
}

/*
 * parcurgem vectorul de produse
 * daca dam de un produs identic, intram in lista de magazine (ex...  produsul corect este p[i])
 * Magazin temp = p[i].m[0];
 *  float distMin = calculeazaDistanta(x, y, p[i].m[0].gps_x, p[i].m[0].gps_y)
 * for  pentru lista de magazine j = 1 pana la p[i].nrMagazine;
 * afisare magazin ... nume, coordonate
 */

/*
 * ex.4
 * Parcurgem lista de produse.
 * Pentru fiecare produs, la verificarile din while-uri, apelam cautaMagazine(Magazin *vectorul_magazine, int nrMag, char *numeMag)
 *
 * cautaMagazine(Magazin *m, int nrMag, char *numeMag) {
 *      for(int i = 0 ; i < nrMag ; i++)
 *          if(strcmp(numeMag, m[i].nume)==0)
 *              return 1;
 *      return 0;
 * }
 *
 * cum facem apelul?
 * while(temp != NULL && cautareMagazine(temp->data.m, temp->data.nrMag, numeMag) == 1) primul while
 * while(temp != NULL && cautareMagazine(temp->data.m, temp->data.nrMag, numeMag) == 0) al doilea while
 */
