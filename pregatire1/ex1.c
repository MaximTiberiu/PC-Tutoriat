#include "ex1.h"
#include <string.h>

void citire(char* fileName, int dim, Meteo m[]) {
    FILE* fin = fopen(fileName, "r");

    for(int i = 0 ; i < dim ; i++) {
        fscanf(fin, "%d", &m[i].nrLuni);
        for(int j = 0 ; j < m[i].nrLuni ; j++) 
            fscanf(fin, "%f", &m[i].temp[j]);
        
        fscanf(fin, "%s", m[i].nume);
    }

    fclose(fin);
}

void calculeazaMedie(int dim, Meteo m[]) {
    for(int i = 0 ; i < dim ; i++)
    {
        float suma = 0;
        for(int j = 0 ; j < m[i].nrLuni ; j++)
            suma += m[i].temp[j];
        //printf("%.2f", suma);
        
        m[i].tempMed = suma / m[i].nrLuni;
        //printf("%f\n", m[i].tempMed);
    }
}

int cmpTemp(const void* t1, const void* t2) {
    Meteo* t11 = (Meteo*)t1;
    Meteo* t22 = (Meteo*)t2;
    //33 13.2 43 -> 43 33 13.2
    if(t11->tempMed > t22->tempMed) return -1;
    if(t11->tempMed < t22->tempMed) return 1;

    // cazul t11->tempMed == t22->tempMed
    if(strcmp(t11->nume, t22->nume) < 0) return -1;
    else if(strcmp(t11->nume, t22->nume) > 0) return 1;
    return 0;
}

void printeaza(char* fileName, int dim, Meteo m[]) {
    FILE* fout = fopen(fileName, "w");

    for(int i = 0 ; i < dim ; i++) {
        fprintf(fout, "%s %.2f\n", m[i].nume, m[i].tempMed);
    }

    fclose(fout);
}

void sorteaza(int dim, Meteo m[]) {
    // qsort(obiect, nrElemente, dimElement, fnComp)
    qsort(m, dim, sizeof(Meteo), cmpTemp);
    printeaza("ex1-out.txt", dim, m);
}