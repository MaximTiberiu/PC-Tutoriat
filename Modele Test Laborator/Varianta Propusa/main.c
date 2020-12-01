#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    char nume[31];
    char prenume[31];
    unsigned short int grupa; // grupa este unsigned short int pentru ca unsigned char are valori doar pana la 255. Putem avea grupa 461, iar in unsigned char nu incape.
    char username[31];
    unsigned int password : 20; // parola are 6 cifre => 20 biti
} Student;

void citireDate(FILE* fin, unsigned  char nrStudenti, Student s[]) {
    unsigned int pass; // nu putem citi un camp care e definit pe camp de biti. Citim intr-o variabila, si dupa facem atribuirea
    // %hu - formatul pentru unsigned short int
    for(unsigned char i = 0 ; i < nrStudenti ; i++) {
        fscanf(fin, "%s %s %hu %s %u", s[i].nume, s[i].prenume, &s[i].grupa, s[i].username, &pass);
        s[i].password = pass;
    }
}

void afisare(unsigned char nrStudenti, Student s[]) {
    for(unsigned char i = 0 ; i < nrStudenti ; i++)
        printf("%s %s %hu %s %u\n", s[i].nume, s[i].prenume, s[i].grupa, s[i].username, s[i].password);
}

void calculareGrupa(unsigned char nrStudenti, Student s[], unsigned char nrStudentiGrupa[]) {
    // initializam elementele vectorului cu 0 - evitam posibile erori din cauza neinitializarii
    for(int i = 0 ; i < 4 ; i++)
        nrStudentiGrupa[i] = 0;

    // presupunem ca grupa 16i corespunde elementului i - 1 din vector
    // ex: 161 -> nrStudentiGrupa[0], iar 164 -> nrStudentiGrupa[3]
    for(unsigned char i = 0 ; i < nrStudenti ; i++) {
        // extragem prima cifra
        unsigned int gr = s[i].grupa % 10;
        // incrementam grupa
        nrStudentiGrupa[gr - 1]++;

        /*
         * putem face si direct:
         * nrStudentiGrupa[s[i].grupa % 10 - 1]++;
         */
    }
}

unsigned int rotireStanga(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int codX = (x << r) | (x >> (8 * sizeof(unsigned int) - r));
    codX = codX ^ key;
    return codX;
}

unsigned int rotireDreapta(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int codX = (x >> r) | (x << (8 * sizeof(unsigned int) - r));
    codX = codX ^ key;
    return codX;
}

unsigned int decodificareStanga(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int decodX = x ^ key;
    decodX = (decodX >> r) | (decodX << (8 * sizeof(unsigned int) - r));
    return decodX;
}

unsigned int decodificareDreapta(unsigned int x, unsigned int r, unsigned int key) {
    unsigned int decodX = x ^ key;
    decodX = (decodX << r) | (decodX >> (8 * sizeof(unsigned int) - r));
    return decodX;
}

void codificareDate(unsigned char nrStudenti, Student s[], Student s_codif[], unsigned int r) {
    for(unsigned char i = 0 ; i < nrStudenti ; i++) {
        // copiem restul campurilor
        strcpy(s_codif[i].nume, s[i].nume);
        strcpy(s_codif[i].prenume, s[i].prenume);
        s_codif[i].grupa = s[i].grupa;

        // codificam username
        // pentru ca inca nu lucram cu pointeri, nu vom face o functie
        strcpy(s_codif[i].username, "\0"); // intialziam username_codif cu NULL

        int len = strlen(s[i].username);
        for(int j = len - 1 ; j >= 0 ; j--)
            s_codif[i].username[len - j - 1] = s[i].username[j];
        s_codif[i].username[len] = '\0';

        // dupa inversare, urmneaza XOR
        for(int j = 0 ; j < len ; j++)
            s_codif[i].username[j] = s_codif[i].username[j] ^ s_codif[i].nume[j % (sizeof(s_codif[i].nume) / sizeof(char))];

        // codificam si parola
        if(s_codif[i].grupa % 2 == 0)
            s_codif[i].password = rotireStanga(s[i].password, r, s_codif[i].grupa);
        else
            s_codif[i].password = rotireDreapta(s[i].password, r, s_codif[i].grupa);
    }
}

void afisareDateCodificate(FILE* fout, unsigned int nrStudenti, Student s_codif[]) {
    for(int i = 0 ; i < nrStudenti ; i++)
        fprintf(fout, "%s %s %hu %s %u\n", s_codif[i].nume, s_codif[i].prenume, s_codif[i].grupa, s_codif[i].username, s_codif[i].password);
}

int cmpGrupa(const void* sa, const void* sb) {
    Student* s1 = (Student*)sa;
    Student* s2 = (Student*)sb;

    // mai intai sortam dupa grupa
    if(s1->grupa < s2->grupa) return -1; // caz favorabil
    if(s1->grupa > s2->grupa) return 1; // caz de swap
    else { // avem egalitate, sortam dupa nume
        if(strcmp(s1->nume, s2->nume) < 0) return -1; // caz favorabil
        if(strcmp(s1->nume, s2->nume) > 0) return 1; // caz de swap
        else {
            // egalitate intre nume, sortam dupa prenume
            if(strcmp(s1->prenume, s2->prenume) < 0) return -1; // caz favorabil
            if(strcmp(s1->prenume, s2->prenume) > 0) return 1; // caz de swap
            return 0; // grupa, nume, prenume la fel pentru cei doi studenti
        }
    }
}

void afisareCredentiale(unsigned char nrStudenti, unsigned short int nrGrupa, unsigned char nrCrtStudent, Student s_codif[], unsigned int r, unsigned char nrStudentiGrupa[]) {
    // avem nevoie de o sortare alfabetica, dar si pe grupe de tipul:
    /*
     * grupa 161:
     *  A
     *  B
     *  C
     *  D
     * grupa 162:
     * A
     * B
     * C
     * D etc
     */
    qsort(s_codif, nrStudenti, sizeof(Student), cmpGrupa);
    // din grupa studentului stabilim pozitia in vectorul de studenti de unde incepe respectiva grupa
    unsigned short int gr = nrGrupa % 10;
    unsigned short int pozStudent = 0; // indicele de unde incepe grupa studentului. Nu parcurgem tot vectorul, pentru a economisi timp si ne folosim de nrStudetiGrupa[]
                       // ca sa aflam cati studenti sunt in fata grupei in care se afla studentul
    for(unsigned short int i = 0 ; i < gr - 1 ; i++)
        pozStudent += nrStudentiGrupa[i];

    // acum ca stim pozitia de la care incepe grupa studentului si vectorul este ordonat si alfabetic, nu ne ramane decat sa printam direct detaliile studentului, decodificate
    pozStudent += (nrCrtStudent - 1);

    // decodifcam username
    char numeDecod[31];
    // XOR
    int len = strlen(s_codif[pozStudent].username);
    for(int j = 0 ; j < len ; j++)
        s_codif[pozStudent].username[j] = s_codif[pozStudent].username[j] ^ s_codif[pozStudent].nume[j % (sizeof(s_codif[pozStudent].nume) / sizeof(char))];
    // inversam caractere
    strcpy(numeDecod, "\0");
    for(int j = len - 1 ; j >= 0 ; j--)
        numeDecod[len - j - 1] = s_codif[pozStudent].username[j];
    numeDecod[len] = '\0';

    // afisam toate datele
    printf("Datele tale sunt: %s %s %hu %s", s_codif[pozStudent].nume, s_codif[pozStudent].prenume, s_codif[pozStudent].grupa, numeDecod);
    printf(" %u\n", (s_codif[pozStudent].grupa % 2 == 0 ? decodificareStanga(s_codif[pozStudent].password, r, s_codif[pozStudent].grupa) : decodificareDreapta(s_codif[pozStudent].password, r, s_codif[pozStudent].grupa)));

}

void afisareUsernameGrupa(unsigned char nrStudenti, unsigned short int nrGrupa, Student s_codif[], unsigned char nrStudentiGrupa[]) {
    // avem nevoie de o sortare alfabetica, dar si pe grupe de tipul:
    /*
     * grupa 161:
     *  A
     *  B
     *  C
     *  D
     * grupa 162:
     * A
     * B
     * C
     * D etc
     */
    qsort(s_codif, nrStudenti, sizeof(Student), cmpGrupa);
    // din grupa studentilor stabilim pozitia in vectorul de studenti de unde incepe respectiva grupa
    unsigned short int gr = nrGrupa % 10;
    unsigned short int pozGrupa = 0; // indicele de unde incepe grupa studentilor. Nu parcurgem tot vectorul, pentru a economisi timp si ne folosim de nrStudetiGrupa[]
    // ca sa aflam cati studenti sunt in fata grupei in care se afla studentii
    for(unsigned short int i = 0 ; i < gr - 1 ; i++)
        pozGrupa += nrStudentiGrupa[i];

    // parcurgem grupa
    for(int i = pozGrupa ; i < pozGrupa + nrStudentiGrupa[gr - 1] ; i++) {
        char numeDecod[31];
        // XOR
        int len = strlen(s_codif[i].username);
        for(int j = 0 ; j < len ; j++)
            s_codif[i].username[j] = s_codif[i].username[j] ^ s_codif[i].nume[j % (sizeof(s_codif[i].nume) / sizeof(char))];
        // inversam caractere
        strcpy(numeDecod, "\0");
        for(int j = len - 1 ; j >= 0 ; j--)
            numeDecod[len - j - 1] = s_codif[i].username[j];
        numeDecod[len] = '\0';

        // afisam toate datele
        printf("%s %s %hu %s\n", s_codif[i].nume, s_codif[i].prenume, s_codif[i].grupa, numeDecod);
    }

}

int main() {
    /* EXERCITIILE 1 & 2 */
    // Am folosit unsigned char pentru eficienta in memorie (valori de la 0 la 255)
    unsigned char nrStudenti;
    Student s[100]; // presupunem ca o grupa are maxim 100 de studenti

    printf("Numarul de studenti al seriei: ");
    scanf("%u", &nrStudenti); // in fisier sunt 100 de studenti

    FILE* fin = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Varianta Propusa\\v1_date.in", "r");
    assert(fin != NULL);
    citireDate(fin, nrStudenti, s);
    fclose(fin);
    afisare(nrStudenti, s); // testare citire

    /* EXERCITUL 3 */
    // decat sa stocam in structura (asta ar insemna sa stocam numarul de studenti din fiecare grupa, la fiecare student), folosim un vector in care vom stoca aceste numere
    unsigned char nrStudentiGrupa[4]; // presupunem ca o grupa are 4 serii
    calculareGrupa(nrStudenti, s, nrStudentiGrupa);

    // afisam numarul de studenti din fiecare grupa, pentru test
    printf("\n\nEXERCITIUL 3:\n");
    for(int i = 0 ; i < 4 ; i++)
        printf("%d ", nrStudentiGrupa[i]); // pentru fisierul de test, trebuie sa afiseze: 25 25 25 25

    /* EXERCITUL 4 */
    // pentru codificare vom folosi tot in vector de studenti in care vom codifica doar username si parola
    Student s_codif[100];
    unsigned int r = 3; // ar merge citit, dar il facem constant
    codificareDate(nrStudenti, s, s_codif, r);
    FILE* fout = fopen("D:\\CTI\\CTI2xx\\CTI21x\\PC-Tutoriat\\Modele Test Laborator\\Varianta Propusa\\v1_date.out", "w");
    assert(fout != NULL);
    afisareDateCodificate(fout, nrStudenti, s_codif); // o sa apara niste caractere urate, dar este normal. Ceea ce am facut este o criptare reala, foarte slaba, evident, dar este criptare
    fclose(fout);

    /* EXERCITIUL 5 */
    printf("\n\nEXERCITIUL 5:\n");
    afisareCredentiale(nrStudenti, 163, 3, s_codif, r, nrStudentiGrupa); // citim datele grupa si nrCrt, aici doar pentru test

    /* EXERCITUL 6 */
    printf("\n\nEXERCITIUL 6:\n");
    afisareUsernameGrupa(nrStudenti, 163, s_codif, nrStudentiGrupa); // citim grupa, aici doar pentru test
    return 0;
}
