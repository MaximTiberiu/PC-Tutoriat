#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
    int nr_legitimatie;
    char nume[30];
} Student;

void citire(int nrStud, Student s[], FILE* fin) {
    for(int i = 0 ; i < nrStud ; i++)
        fscanf(fin, "%d %s", &s[i].nr_legitimatie, s[i].nume);
}

/* (x << r) | (x >> (8 * sizeof(int) - r)) ;r = 3
x = 247                     11110111
x << r                      10111000 (111 - pierdut)
x >> (8 * sizeof(int) - r)  00000111
                            10111111 => 191
*/

int codifica(int x, int r, int key) {
    int codX = (x << r) | (x >> (8 * sizeof(int) - r));
    codX = codX ^ key;

    return codX;
}

int decodifica(int x, int r, int key) {
    int decodX = x ^ key;
    decodX = (decodX >> r) | (decodX << (8 * sizeof(int) - r));

    return decodX;
}

void codificaLegitimatii(int nrStud, Student s[], int legCodif[], int r, int key) {
    for(int i = 0 ; i < nrStud ; i++)
        legCodif[i] = codifica(s[i].nr_legitimatie, r, key);
}

/* x - nr de transformat
 for i= 31 -> 0
    int k = x >> i 000000000000....10
    if(k & 1) =>
*/

void decToBin(int x, FILE* fout) {
    if(x) {
        decToBin(x / 2, fout);
        fprintf(fout, "%d", x % 2);
    }
}

void afiseazaLegitimatiiBinare(int nrStud, int legCodif[], FILE* fout) {
    for(int i = 0 ; i < nrStud ; i++) {
        decToBin(legCodif[i], fout);
        fprintf(fout, "\n");
    }
}

int binToDec(int x) {
    int decX = 0, e = 1;
    while(x) {
        decX += ((x % 10) * e);
        e *= 2;
        x /= 10;
    }

    return decX;
}

int citireDecodificata(int nrLinie, int nrStud, FILE* fin, int r, int key) {   
    assert(nrLinie <= nrStud);

    char buffer[32];

    for(int i = 0 ; i < nrLinie - 1 ; i++)
    {
        //fgets(buffer, 32, fin); 
        fscanf(fin, "%s", buffer);
        int ch = fgetc(fin);
    }
    
    fscanf(fin, "%s", buffer); // aici se afla legitimatia de la nrLinie

    int nrLeg = atoi(buffer); // itoa, atol, ltoa
    nrLeg = binToDec(nrLeg);
    nrLeg = decodifica(nrLeg, r, key);

    return nrLeg;
} 

int main() {
    Student s[100];
    int legitimatii[100];

    int nrStud = 5;
    int r = 3;
    int key = 43;

    FILE* fin = fopen("studenti.txt", "r");
    assert(fin != NULL);

    FILE* fout = fopen("legitimatiiBinar.txt", "w");
    assert(fout != NULL);

    citire(nrStud, s, fin);
    fclose(fin);

    codificaLegitimatii(nrStud, s, legitimatii, r, key);
    afiseazaLegitimatiiBinare(nrStud, legitimatii, fout);
    fclose(fout);

    FILE* bfin = fopen("legitimatiiBinar.txt", "r");
    assert(bfin != NULL);

    //printf("%d\n", citireDecodificata(3, nrStud, bfin, r, key)); // nu da bine

    fclose(bfin);

    return 0;
}