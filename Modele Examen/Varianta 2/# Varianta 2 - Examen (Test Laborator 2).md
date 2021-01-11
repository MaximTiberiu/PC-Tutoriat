# Varianta 2 - Examen (Test Laborator 2)

O fabrică de produse electronice dorește gestiunea datelor produselor cu ajutorul limbajului C. Fiecare dintre produsele electronice dispune de un nume, preț și cod. Modelați colecția de produce folosind structura:

```
struct produs { 
    char nume[16];
    float pret;
    char **cod; 
}
```

1. Implementați o funcție alocă dinamic memorie pentru un tablou (unidimensional) de produse și care citește datele produselor (nume și preț) de la tastatură.
*Indicațe: De asememena, se va aloca dinamic memorie (necompact) pentru matricea cod[][].*
2. Scrieți o funcție care completează funcția cod (de dimensiune 4x4) a fiecărui produs după următorii pași:
    1. valoare elementelor de pe linia i este data de codurile ASCII ale celui de-al i-lea set de 4 caractere din nume;
    2. se rotește matricea rezultată cu 90 de grade în sens trigonometric (contrar acelor de ceasornic.)
    Exemplu:
    ```
        Pas 1) TELEVIZOR => T e l e
                            v i z o
                            r
        Pas 2) T e l e
               v i z o   => e o
               r            l z
                            e i
                            T v r
    ```
3. Scrieți o funcție care ordonează produsele, utilizând funcția qsort, după preț, iar produsele cu prețuri egale vor fi ordonate după numărul de 0-uridin matricea cod.
4. Creați o listă simplu înlănțuită în care fiecare nod reprezintă un cod de produs, în care fiecare nod are structura: 
```
struct nod {
    char **cod;
    struct nod *urm;
}
``` 
și memoreză în câmpul *cod* matricea cod a produsului afernet. Screiți o funcție cu antetul
```
void eliminare (struct nod **L, char *produs)
```
care parcurge această listă  ̧si elimină nodurile pentru care șirul rezultat după decodificare coincide cu șirul produs.