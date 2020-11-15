# Modelul 4 - Test Laborator 1

O companie bancară deține o bază de date a clienților în care sunt stocate următoarele informații: nume, debit_cont, codificat, stare_îndatorare. Presupunem că:
- numele unui client (numele de familie, fără spații) nu depășește 40 de caractere;
- câmpul debit cont reprezintă o valoare numerică în format virgulă mobilă cu limita superioară 100000;
- stare_îndatorare este dată doar de valori corespunzătoare lui îndatorat sau neîndatorat.
Implementați următoarele funcții pentru a ajuta banca să realizeze operațiunile corespunzătoare:

1. Funcție care citește (de la tastatură) întreaga bază de date cu informațiile corespunzătoare. Folosiți o structură care ocupă un spațiu de memorie ***MINIM***.
2. Banca dorește să tramsfere baza de date în condiții sigure, de aceea se codifică debitul de cont după cum urmează:
    - se calculează adunarea dintre numărul de zero-uri din primul octet și din ultimul octet din reprezentarea în baza 2 a debitului;
    - se memorează în câmpul codificat.
  Scrieți o funcție care primește baza de date a clienților, iar pentru fiecare client completează câmpul codificat.
  *Indicație: folosiți o uniune pentru a accesa pe octeți valoarea în virgulă mobilă*
3. Funcție care reordonează baza de date după cum urmează:
    - clienții îndatorați cu un debit mai mare de 1000;
    - clienții îndatorați cu un debit mai mic sau egal cu 1000;
    - clienți neîndatorați
4. Funcție care primește un fișier text în care se află informațiile clienților în formatul *nume debit_cont stare_îndatorare* evitând scrierea zecimalelor din debit. Dacă un câmp nu există, se va scrie caracterul '-'. Extrageți din fișier numele clienților neîndatorați cu debit peste 200.
*Indicație: pentru punctaj maxim, tratați cât mai multe excepții: inexistența unui câmp, citire eșuată etc.*
