#include "ex2.h"

int main()
{
    // ex1
    /*Meteo m[100];
    int dim;
    scanf("%d", &dim);
    citire("ex1.txt", dim, m);
    calculeazaMedie(dim, m);
    sorteaza(dim, m);*/

    // ex2
    Elev e[100];
    int n;
    scanf("%d", &n);
    citire1("ex2.in", n, e);
    medie(n, e);
    promovat(n, e);
    sortare(n, e);
    return 0;
}