#pragma once

#include <stdio.h>

typedef struct Elev {
    char nume[30];
    char prenume[30];
    float note[3];
    float medie;
    char promovat;
}Elev;

void citire1(char* fileName, int n, Elev e[]);
void medie(int n, Elev e[]);
void promovat(int n, Elev e[]);
void printeaza1(char* fileName, int n, Elev e[]);
void sortare(int n, Elev e[]);