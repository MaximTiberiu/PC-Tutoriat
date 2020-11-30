#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    char nume[31];
    unsigned int IBAN : 17;
    unsigned int stare_civila : 1;
    unsigned int bit_paritate : 1;
} Client;

void citire(int nrC, Client c[]) {
    for(int i = 0 ; i < nrC ; i++) {
        int cond = 0; // conditie pentru citrea IBAN corect / stare_civila corecta
        // NUME
        printf("Numele clientului %d: ", i + 1);
        scanf("%s", c[i].nume);

        // IBAN
        int iban;
        printf("IBAN-ul clientului %d: ", i + 1);
        scanf("%u", &iban);
        if(iban < 100000)
            cond = 1;
        else {
            printf("IBAN-ul este o valoare numerica de maxim 5 cifre!\n Tastati din nou: ");
            while(!cond) {
                scanf("%u", &iban);
                if(iban < 100000)
                    cond = 1;
                else
                    printf("IBAN-ul este o valoare numerica de maxim 5 cifre!\n Tastati din nou: ");
            }
        }
        c[i].IBAN = iban;

        // STARE_CIVILA
        unsigned int stareC;
        printf("Starea civila (0-necasatorit; 1-casatorit) a clientului %d: ", i + 1);
        scanf("%u", &stareC);
        cond = 0;
        if(stareC <= 1)
            cond = 1;
        else {
            printf("Starea civila (0-necasatorit; 1-casatorit) gresita!\n Tastati din nou: ");
            while(!cond) {
                scanf("%u", &stareC);
                if(stareC <= 1)
                    cond = 1;
                else
                    printf("Starea civila (0-necasatorit; 1-casatorit) gresita!\n Tastati din nou: ");
            }
        }
        c[i].stare_civila = stareC;
    }
}

void afisare(int nrC, Client c[]) {
    for(int i = 0 ; i < nrC ; i++)
        printf("%s %u %u %u\n", c[i].nume, c[i].IBAN, c[i].stare_civila, c[i].bit_paritate);
}

unsigned int bitParitate(unsigned int x) {
    unsigned int cnt = 0;
    while(x) {
        if(x & 1) cnt++;
        x >>= 1;
    }
    if(cnt % 2 == 0) return 0;
    return 1;
}

void completareDate(int nrC, Client c[]) {
    for(int i = 0 ; i < nrC ; i++)
        c[i].bit_paritate = bitParitate(c[i].IBAN);
}

int cmpStareCivila(const void* c1, const void* c2) {
    Client* ca = (Client*)c1;
    Client* cb = (Client*)c2;

    if(ca->stare_civila == 0 && cb->stare_civila == 1) return -1;
    if(ca->stare_civila == 1 && cb->stare_civila == 0) return 1;
    return 0; // if(ca->stare_civila == cb->stare_civila)
}

void sortareStareCivila(int nrC, Client c[]) {
    qsort(c, nrC, sizeof(Client), cmpStareCivila);
    afisare(nrC, c);
}

unsigned int verificareNume(char nume[]){
    int len = strlen(nume);
    char vocale[11] = "aeiouAEIOU\0";

    int cons = 0, voc = 0;
    for(int i = 0 ; i < len ; i++) {
        if(strchr(vocale, nume[i]) != NULL)
            voc++;
        else
            cons++;
    }

    if(cons > voc) return 1;
    return 0;
}

void citireClienti(FILE* fin) {
    char nume[31];
    int IBAN;
    char stare_civila;

    while(fscanf(fin, "%s %u %c", nume, &IBAN, &stare_civila) == 3) {
        if(stare_civila == '0' && verificareNume(nume))
            printf("%s %d %u\n", nume, IBAN, bitParitate(IBAN));
    }

}

int main() {
    int nrC;
    Client c[100];

    printf("Numarul de clienti este: ");
    scanf("%d", &nrC);
    citire(nrC, c);
    completareDate(nrC, c);
    afisare(nrC, c);

    printf("\n\n\n ------- Dupa sortare ------\n");
    sortareStareCivila(nrC, c);


    printf("\n\n\n ------- Afisare din fisier ------\n");
    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 3\\clienti.txt", "r");
    assert(fin != NULL);
    citireClienti(fin);
    fclose(fin);
    return 0;
}
