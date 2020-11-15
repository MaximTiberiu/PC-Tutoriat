# Modelul 3 - Test Laborator 1

O companie bancară deține o bază de date a clienților în care sunt stocate următoarele informații: nume, IBAN, stare_civilă, bit_paritate. Presupunem că:
- numele unui client (numele de familie, fără spații) nu depășește 30 de caractere;
- câmpul IBAN reprezintă o valoare numerică cu maxim 5 cifre;
- stare_civilă este dată doar de valori corespunzătoare lui căsătorit sau necăsătorit.
Implementați următoarele funcții pentru a ajuta banca să realizeze operațiunile corespunzătoare:

1. Funcție care citește (de la tastatură) întreaga bază de date cu informațiile corespunzătoare. Folosiți o structură care ocupă un spațiu de memorie ***MINIM***.
2. Banca dorește să tramsfere baza de date în condiții sigure, de aceea pentru verificarea oricărui transfer se completează bit_paritate după cum urmează:
    - dacă numărul de biți din reprezentarea câmpului IBAN este par, bit_paritate = 0;
    - altfel, bit_paritate = 1.
  Scrieți o funcție care primește baza de date a clienților, iar pentru fiecare client numără în mod eficient biții de 1 din reprezentarea câmpului IBAN și completează câmpul bitului de paritate.
3. Funcție care reordonează baza de date după câmpul de stare civilă: toți clienții necăsătoriți vor apărea înaintea celor căsătoriți.
4. Funcție care primește un fișier text în care se află informațiile clienților în formatul *nume IBAN stare_civilă* cu spațiere arbitrară. Afișați IBAN și bit_paritate pentru fiecare client într-un nou fișier.
