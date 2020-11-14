#pragma once

#include <stdio.h>
typedef struct {
    int nrLuni;
    float temp[11];
    float tempMed;
    char nume[30];
} Meteo;

void citire(char* fileName, int dim, Meteo m[]);
void calculeazaMedie(int dim, Meteo m[]);
void sorteaza(int dim, Meteo m[]);
void printeaza(char* fileName, int dim, Meteo m[]);

