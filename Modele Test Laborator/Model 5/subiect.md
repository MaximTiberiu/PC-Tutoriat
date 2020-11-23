# Modelul 5 - Test Laborator 1

Compania aeriană TAROM stochează la fiecare zbor baza de date a pasagerilor cu următoarele
informații: nume, clasa zbor, greutate bagaj, cod. Presupunem că: numele unui client
nu depășește 50 de caractere, câmpul clasa zbor poate stoca doar 4 valori posibile corespunzătoare claselor de zbor A,B,C sau D. Câmpul greutate bagaj reprezintă o valoare numerică în format virgulă mobilă cu limita superioară 100. Implementați următoarele funcții
pentru a ajuta compania să realizeze operațiunile corespunzătoare:
1. Funcție care citeșteîntreaga bază de date a pasagerilor, cu informațiile corespunzătoare, din stream-ul stdin, impunând limitele specificate în enunț. Dimensiunile câmpurilor vor fi alocate în modul cel mai economic. Indicație: Folosiți câmpuri de biți pentru a limita dimensiunea câmpurilor. Citiți valori
ale câmpurilor care respectă limitele specificate în enunț.
2. La aterizare se dorește reverificarea pasagerilor prin codul asociat fiecărui pasager. De aceea se calculează codul fiecărui pasager pe baza primului caracter din numele său, după cum urmează: codul este dat de numărul de biți 0 din reprezentarea binară a codului ASCII a primului caracter. Scrieți o funcție care completează câmpurile cod din toată baza de date.
3. Funcție care reordonează baza de date după clasa de zbor pe baza importanței: clasa A fiind cea mai importantă, iar D cea mai puțin importantă.
4. Funcție care primește un fișier text în care se află informațiile pasagerilor in format: nume clasa_zbor greutate_bagaj cu spațiere arbitrară. Funcția va executa următoarea interogare de selecție: afișează la ecran numele pasagerilor cu bagaje mai grele de 30 (kg). Indicații: pentru punctaj maxim tratați cât mai multe excepții: inexistența fișierului, inexistența unui câmp de pe o linie, valoare invalidă a câmpului de (caracter diferit de A, B, C sau D) etc.