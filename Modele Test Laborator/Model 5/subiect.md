# Modelul 5 - Test Laborator 1

O companie bancară deține o bază de date a clienților în care sunt stocate următoarele informații: nume, debit_cont, codificat, stare_îndatorare. Presupunem că:
- numele unui client (numele de familie, fără spații) nu depășește 40 de caractere;
- câmpul debit cont reprezintă o valoare numerică în format virgulă mobilă cu limita superioară 100000;
- stare_îndatorare este dată doar de valori corespunzătoare lui îndatorat sau neîndatorat.
Implementați următoarele funcții pentru a ajuta banca să realizeze operațiunile corespunzătoare:
1. Funcție care citește întreaga bază de date cu informațiile corespunzătoare (de la tastatură), impunând limitele specificate în enunț. Dimensiunea câmpului care specifică starea de îndatorare a clientului este de 1 bit. Folosiți structura cu dimensiune minimă.
2. Banca dorește să transfere baza de date în condiții sigure, de aceea se codifică debitul de cont după cum urmează: se calculează adunarea dintre numarul de zero-uri din primul octet si cel din ultimul octet din reprezentarea in baza 2 a valorii debitului și se memoreaza în câmpul cu numele codificat. Scrieți o funcție care completează câmpurile codificat din toată baza de date.
3. Funcție care reordonează baza de date după cum urmează: clienții îndatorați cu un debit pe cont mai mare de 1000, clienții îndatorați cu un debit pe cont mai mic sau egal cu 1000, clienții neîndatorați.
4. . Funcție de scriere în fișier. Funcția va executa scrierea în fișier a câmpurilor asociate unui client (primit ca argument) în format: nume debit_cont stare_indatorare evitând scrierea zecimalelor din valoarea debit cont-urilor. Dacă un câmp nu exista, se va scrie caracterul ’-’. Extrageți din fișier numele clienților neîndatorați cu debite peste 200.
