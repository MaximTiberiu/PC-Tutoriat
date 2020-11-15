# Modelul 1 - Test Laborator 1

O selecție secretă din baza de date a studenților FMI se intentionează a fi trimsă către alte facultăți de profil. Deoarece datele sunt private, este necesară codificarea acestora, iar destinatarul, care va cunoaște cheia de codificare, va reuși să decodifice mesajul. Implementați funcții care sprijină comunicarea bazei de date:

1. Funcție de citire a bazei de date a studenților selectați, folosind structura:
    ```
    struct student {
        int nr_legitimație;
        char nume[30];
    }
    ```
2. Funcție care primește o bază de date și returnează un tablou al numerelor de legitimație codificate. Pentru codificare se folosește:
    - o rotire cu *r* biți a numărului de legitimație original
    - operația **XOR** între rezultatul rotirii și o cheie de codificare (un întreg pozitiv) primită ca argument
3. Funcție care scrie într-un fișier text numerele de legitimație codificate, transformate în binar. Pe o linie a fișierului va sta un număr de legitimație.
4. Funcție care citește o linie din fișier, primind fișierul și indexul liniei ca argument și decodifică conținutul liniei - aplică codificarea **XOR** cu aceeași cheie și rotire în sens invers. Rezultatul îl returnează la ieșire.
