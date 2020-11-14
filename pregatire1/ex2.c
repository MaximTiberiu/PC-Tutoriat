#include "ex2.h"
#include <string.h>

void citire1(char* fileName, int n, Elev e[]){
    FILE* fin = fopen(fileName, "r");

    for(int i = 0 ; i < n ; i++) {
        fscanf(fin, "%s %s", e[i].nume, e[i].prenume);
        for(int j = 0 ; j < 3 ; j++) 
            fscanf(fin, "%f", &e[i].note[j]);
    }

    fclose(fin);
}

void medie(int n, Elev e[]) {
    for(int i = 0 ; i < n ; i++) 
    {
        float suma = 0;
        for(int j = 0 ; j < 3 ; j++)
            suma += e[i].note[j];
        
        e[i].medie = suma / (3 * 1.0);
    }
}

int noteValide(float note[]) {
    for(int i = 0 ; i < 3 ; i++) 
        if(note[i] < 5) return 0;
    return 1;
}

void promovat(int n, Elev e[]) { 
    for(int i = 0 ; i < n ; i++) {
        if(e[i].medie >= 6 && noteValide(e[i].note))
             e[i].promovat = 'Y';
        else
        {
            e[i].promovat = 'N';
            e[i].medie = 0;
        }
    }
}

int cmpElev(const void* e1, const void* e2) {
    Elev* a = (Elev*)e1;
    Elev* b = (Elev*)e2;

    if(a->medie > b->medie) return -1;
    else if(a->medie < b->medie) return 1;

    // a->medie == b->medie
    if(strcmp(a->nume, b->nume) < 0) return -1;
    else if(strcmp(a->nume, b->nume) > 0) return 1;

    // a->nume == b->nume
    if(strcmp(a->prenume, b->prenume) < 0) return -1;
    else if(strcmp(a->prenume, b->prenume) > 0) return 1;

    return 0;
}

void sortare(int n, Elev e[]) {
    qsort(e, n, sizeof(Elev), cmpElev);
    printeaza1("ex2.out", n, e);
}

void printeaza1(char* fileName, int n, Elev e[]) {
    FILE* fout = fopen(fileName, "w");

    for(int i = 0 ; i < n ; i++)
        fprintf(fout, "%s %s %.2f %c\n", e[i].nume, e[i].prenume, e[i].medie, e[i].promovat);

    fclose(fout);
}


