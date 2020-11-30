#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
    unsigned int nrLeg;
    char nume[31];
} student;

void citire(int nrS, student s[]) {
    for(int i = 0 ; i < nrS ; i++) {
        printf("Legitimatia studentul %d: ", i + 1);
        scanf("%u", &s[i].nrLeg);

        printf("Numele studentului %d: ", i + 1);
        char ch = getc(stdin);
        scanf("%s", s[i].nume);
    }
}

void afisare(int nrS, student s[]) {
    for(int i = 0 ; i < nrS ; i++)
        printf("%u %s\n", s[i].nrLeg, s[i].nume);
}

unsigned int codifica(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int codX = (x << r) | (x >> (8 * sizeof(unsigned int) - r));
    codX = codX ^ key;
    return codX;
}

unsigned int decodifica(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int decodX = x ^ key;
    decodX = (decodX >> r) | (decodX << (8 * sizeof(unsigned int) - r));
    return decodX;
}

void codificareDate(int nrS, student s[], student sC[], unsigned int r, unsigned int key) {
    for(int i = 0 ; i < nrS ; i++) {
        sC[i].nrLeg = codifica(s[i].nrLeg, r, key);
        strcpy(sC[i].nume, "\0");

        /**
         * s[i].nume = abcd => len = 4; i = 3
         * sC[i].nume= dcba
         */

        int len = strlen(s[i].nume); // ch nume[30] = a b c d \0
        for(int j = len - 1; j >= 0 ; j--)
            sC[i].nume[len - j - 1] = s[i].nume[j];
        sC[i].nume[len] = '\0';
    }
}

void afisareFisier(int nrS, student s[], FILE* fout) {
    for(int i = 0 ; i < nrS ; i++) {
        fprintf(fout, "%u %s\n", s[i].nrLeg, s[i].nume);
    }
}

void citireFisierCodificat(int nrS, FILE* fin, unsigned int r, unsigned int key) {
    unsigned int nrLeg;
    char nume[31];
    for(int i = 0 ; i < nrS ; i++) {
        fscanf(fin, "%u %s", &nrLeg, nume);

        char ch = nume[strlen(nume) - 1];
        char vocale[11] = "aeiouAEIOU";
        if(strchr(vocale, ch) != NULL) {
            unsigned int legDecod = decodifica(nrLeg, r, key);
            if(legDecod % 3 == 0) {
                printf("%u ", legDecod);

                int len = strlen(nume);
                char numeDecod[31];
                for(int j = len - 1; j >= 0 ; j--)
                    numeDecod[len - j - 1] = nume[j];
                numeDecod[len] = '\0';
                printf("%s\n", numeDecod);
            }
        }
    }
}

int main() {
    int nrS;
    unsigned int r, key;
    student s[100];
    student sC[100];

    printf("Numarul de studenti este: ");
    scanf("%d", &nrS);
    printf("Numarul de biti r este: ");
    scanf("%u", &r);
    printf("Cheia este: " );
    scanf("%u", &key);

    citire(nrS, s);
    codificareDate(nrS, s, sC, r, key);
    //afisare(nrS, sC);

    FILE* fout = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 4\\studenti.txt", "w");
    assert(fout != NULL);
    afisareFisier(nrS, sC, fout);
    fclose(fout);

    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 4\\studenti.txt", "r");
    assert(fin != NULL);
    citireFisierCodificat(nrS, fin, r, key);
    fclose(fin);

    /* Conditie float <= 100000
    float debit;
    int cond = 0;
    scanf("%f", &debit);
    if(debit <= 100000) cond = 1;
    else {
        printf("Debitul nu trebuie sa depaseasca 100000!\n");
        printf("Scrie din nou debitul: ");
    }
    while(cond == 0) {
        scanf("%f", &debit);
        if(debit <= 100000) cond = 1;
        else {
            printf("Debitul nu trebuie sa depaseasca 100000!\n");
            printf("Scrie din nou debitul: ");
        }
    }*/


    return 0;
}
