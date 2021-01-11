# Varianta 1 - Examen (Test Laborator 2)

O companie de produse electronice dorește gestiunea datelor produselor cu ajutorul limbajului C. Fiecare dintre produsele electronice dispune de un nume, preț ̧(universal)  ̧si un tablou al magazinelor în care el este vândut. Tabloul cu informațiile magazinelor conțin numele și locația acestora. Modelați colecția de produse folosind structurile următoare:

```
struct produs { 
    char nume[30];
    float pret;
    struct magazin* m; 
}

struct magazin { 
    char nume[30]; 
    int gps_x;
    int gps_y; 
}
```

1. Implementați o funcție care citește datele produselor de la tastatură  ̧si alocă dinamic tablourile unidimensionale corespunzătoare magazinelor.
*Indicațe: numărul inițial de magazine în care apare fiecare produs este aleator (la alegere).*
2. Scrieți o funcție care primește argumentele: numele unui produs si locația unui client (în coordonate planare întregi (x, y)),  ̧si stabilește care este cel mai apropiat magazin, care conțne produsul, de locația clientului.
*Indicațe: distanțele se măsoară în norma euclidiană d(a, b) = sqrt((a.x − b.x)<sup>2</sup>+(a.y − b.y)<sup>2</sup>)*
3. Scrieți o funcție care ordonează produsele, utilizând funcția qsort, după preț, iar produsele cu prețuri egale vor fi ordonate după numărul de magazine în care se găsesc.
4. Creați o listă simplu înlănțuită în care fiecare nod reprezintă un produs. Scrieți o funcție cu antet-ul
```
void eliminare (struct nod **L, char *nume)
```
care parcurge această listă  ̧si elimină produsele care se află în magazinul cu numele *nume*.