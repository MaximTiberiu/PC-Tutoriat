#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    float debit; // 32 de biti
    unsigned char biti[4];
} octet;

typedef struct {
    char nume[40]; // 1 byte
    octet debit_cont; // 4 bytes
    unsigned int codificat; // 4 bytes
    unsigned int stare_indatorare : 1; // 4 bytes
} Clienti;

void citire(int nrClienti, Clienti c[], FILE* fin) {
    for(int i = 0 ; i < nrClienti ; i++) {
        fscanf(fin, "%s %f", c[i].nume, &c[i].debit_cont.debit);

        unsigned int stare;
        fscanf(fin, "%u", &stare);
        c[i].stare_indatorare = stare;
    }
}

void codifica(int nrClienti, Clienti c[]) {
    /*for(int i = 0 ; i < 4 ; i++)
        printf("bitul %d este: %03x\n", i, c[0].debit_cont.biti[i]);*/
    for(int i = 0 ; i < nrClienti ; i++) {
        c[i].codificat = 0;
        unsigned char oct = c[i].debit_cont.biti[0];
        // oct: 00010110 &
        //      00000001
        //--------------
        //      00000000
        while(oct) {
            if((oct & 1) == 0) c[i].codificat++;
            oct >>= 1; // oct = oct >> 1;
        }

        oct = c[i].debit_cont.biti[3];
        while(oct) {
            if((oct & 1) == 0) c[i].codificat++;
            oct >>= 1; // oct = oct >> 1;
        }
        // printf("%u\n", c[i].codificat);
    }

}

// Ordine afisare: 1. clienti indatorati, debit > 1000; 2. clienti indatorati, debit <= 1000; 3. clienti neindatorati
int cmp(const void* ca, const void* cb) {
    Clienti* c1 = (Clienti*)ca;
    Clienti* c2 = (Clienti*)cb;

    /*
     * cmp(a, b) < 0 => ordinea dorita - nu facem schimbari
     * cmp(a, b) = 0 => elementele sunt egale - nu facem schimbari
     * cmp(a, b) > 0 => ordinea nu este cea dorita - facem schimbare
     */

    if(c1->stare_indatorare == 0 && c2->stare_indatorare == 0) return 0;
    if(c1->stare_indatorare == 1 && c2->stare_indatorare == 0) return -1;
    if(c1->stare_indatorare == 0 && c2->stare_indatorare == 1) return 1;

    if(c1->stare_indatorare == 1 && c2->stare_indatorare == 1)
    {
        if(c1->debit_cont.debit > 1000 && c2->debit_cont.debit <= 1000) return -1;
        if(c1->debit_cont.debit > 1000 && c2->debit_cont.debit > 1000) return 0;
        if(c1->debit_cont.debit <= 1000 && c2->debit_cont.debit <= 1000) return 0;
        return 1; // if(c1->debit_cont.debit <= 1000 && c2->debit_cont.debit > 1000)
    }
}

void afisare(int nrClienti, Clienti c[]) {
    for(int i = 0 ; i < nrClienti ; i++)
        printf("%s %.2f %u\n", c[i].nume, c[i].debit_cont.debit, c[i].stare_indatorare);
}

void sortare(int nrClienti, Clienti c[]) {
    // qsort(obj, nrElem, sizeof(Elem), cmp)
    qsort(c, nrClienti, sizeof(Clienti), cmp);
    afisare(nrClienti, c);
}

void citireClienti(FILE* fin) {
    char nume[40];
    char debit[6];
    char stare = 'a';
    char linie[100];

    // fgets(obj, dim, stdin/fin);

    while(fscanf(fin,"%s %s %c", nume, debit, &stare) == 3) {
        int cond = 1;

        if(strcmp(nume, "-") == 0)
        {
            cond = 0;
            printf("Lipseste numele! ");
        }
        if(strcmp(debit, "-") == 0) {
            cond = 0;
            printf("Lipseste debitul! ");
        }
        if(stare == '-') {
            cond = 0;
            printf("Nu stim daca este dator!");
        }

        if(cond) {
            if(stare == '1'){
                int deb = atoi(debit);
                if(deb > 200)
                    printf("%s\n", nume);
            }
        }
        else printf("\n");
    }

}

int main() {
    int nrClienti;
    Clienti c[100];

    // exercitul 1 - citire
    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 4\\clienti.txt", "r");
    assert(fin != NULL); // exceptie citire esuata din fisier

    fscanf(fin, "%d", &nrClienti);
    citire(nrClienti, c, fin);
    fclose(fin);
    codifica(nrClienti, c);
    //sortare(nrClienti, c);

    FILE* fin1 = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Model 4\\clienti1.txt", "r");
    assert(fin1 != NULL);
    citireClienti(fin1);
    fclose(fin1);
    return 0;
}
