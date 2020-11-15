# Modelul 2 - Test Laborator 1

O selecție secretă din baza de date a studenților FMI se intentionează a fi trimsă către alte facultăți de profil. Deoarece datele sunt private, este necesară codificarea acestora, iar destinatarul, care va cunoaște cheia de codificare, va reuși să decodifice mesajul. Implementați funcții care sprijină comunicarea bazei de date:

1. Funcție de citire a bazei de date a studenților selectați, folosind structura:
    ```
    struct student {
        unsigned int nr_legitimație;
        char nume[30];
    }
    ```
2. Funcție care primește o bază de date și codifică datele studenților. Pentru codificarea numelui se vor inversa caracterele. Pentru codificarea numărului de legitimație se folosește:
    - o rotire cu *r* biți a numărului de legitimație original
    - operația **XOR** între rezultatul rotirii și o cheie de codificare (un întreg pozitiv) primită ca argument
3. Funcție care scrie într-un fișier text datele codificate ale studenților.
4. Funcție care primește datele codificate și afișează datele decodificate (nr_leg: aplică codificarea **XOR** cu aceeași cheie și rotire în sens invers) ale studenților al căror nume începe cu o vocală și au numărul legitimației divizibil cu 3.
