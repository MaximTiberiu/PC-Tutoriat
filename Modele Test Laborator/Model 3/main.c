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

int main() {
    int nrC;
    Client c[100];

    printf("Numarul de clienti este: ");
    scanf("%d", &nrC);
    citire(nrC, c);
    afisare(nrC, c);

    return 0;
}
