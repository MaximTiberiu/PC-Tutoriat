## Exerciții

1. Definiți o structură, Meteo, care să permită memorarea temperaturilor medii lunare dintr-o țară în primele m luni ale unui anumit an (1 ≤ m ≤ 12). 
Scrieți o funcție care să calculeze temperatura medie anuală înregistrată într-o anumită țară. Informațiile referitoare la temperaturile lunare înregistrate în mai multe țări 
de-a lungul mai multor ani vor fi transmise funcției prin intermediul unui tablou unidimensional t cu n elemente de tip Meteo.
Folosind funcția qsort din biblioteca stdlib.h, sortați elementele unui tablou unidimensional t format din n elemente de tip Meteo în ordinea descrescătoare a temperaturilor 
medii anuale, iar în cazul unor temperaturi medii anuale egale țările se vor ordona alfabetic. Implementați funcția comparator corespunzătoare și scrieți apelul funcției
qsort.

2. Definiți o structură Elev care să permită memorarea numelui și prenumelui unui elev, precum și a notelor, mediei și rezultatului pe care acesta le-a obținut la Bacalaureat.
Scrieți o funcție care să calculeze rezultatele obținute de n elevi ale căror date sunt memorate
într-un tablou unidimensional t cu elemente de tip Elev. Un elev promovează examenul de
Bacalaureat dacă toate notele obținute sunt mai mari sau egale decât 5 și media este mai mare
sau egală decât 6.
Folosind funcția qsort, sortați elementele unui tablou unidimensional t format din n
elemente de tip Elev în ordinea descrescătoare a rezultatelor obținute (se consideră că
nepromovat ≼ promovat), iar în cazul unor rezultate egale elevii se vor ordona descrescător
în funcție de medii, iar la medii egale în funcție de nume și apoi de prenume. Implementați
funcția comparator corespunzătoare și scrieți apelul funcției qsort.

3. Sunteți rugat să scrieți un program în limbajul C pentru a ajuta secretariatul Facultății de
Matematică și Informatică în calcularea situațiilor școlare dupa primul an. Un student
promovează primul an dacă suma creditelor examenelor promovate este ≥ jumătate din suma
tututor creditelor. În primul an fiecare student are de susținut 12 examene obligatorii. În
catalog, pentru fiecare student, în dreptul fiecărei discipline, este trecută o notă (între 1 și 10)
sau ‚a’ (absent). O disciplină este considerată promovată dacă nota la acea disiplina este cel
puțin 5. La sfârșit de an se calculează mediile numai pentru studenții integraliști, acei studenți
care promovează toate disciplinele din an. Pentru fiecare student se calculează punctajul de
clasificare ca suma ponderată dintre notele la disciplinele promovate și creditele aferente
disciplinei.
Definiți o structură Student care să permită memorarea numelui, prenumelui, grupei
corespunzătoare unui student, notelor, mediei, punctajului de clasificare și statutului la
sfârșitul primului an universitar (promovat sau nu).
Scrieți o funcție care să calculeze media, punctajul de clasificare, statutul pentru n studenți ale
căror date sunt memorate într-un tablou unidimensional t cu elemente de tip Student.

4. a. Să se construiască o structură ce conține următoarele date despre candidații la admitere:
nr_legitimatie, nume, nota_mate, nota_info, nota_bac, medie, admis (Y/N), buget (Y/N).
   b. Sa se defineasca o instrucțiune ce calculează media de admitere dupa regula: 80% media la
examen, 20% media de bac. Promovabilitatea se calculeaza utilizand pragul de 5.
   c. Sa se scrie o funcție care citește datele unui candidat, in afara de medie, admis si buget, si le
adauga unui vector al tuturor candidatilor, pastrand ordinea alfabetica. Media si promovabilitatea
vor fi calculate folosind definitiile de la punctele b). Numarul de candidati este citit de la tastatura.
  d. Să se scrie o funcție care completeaza campul „buget” cu Y sau N dupa regula: primii 75%
(rotunjit in jos) dintre candidatii admisi, in ordinea mediilor, sunt la buget (Y), restul la taxa (N) sau
nu au promovat examenul de admitere (lasati campul gol).
  e. Sa se scrie o functie care afiseaza datele candidatilor in functie de optiunea aleasa: toti candidatii
(alfabetic), cei admisi la buget, cei admisi la taxa, cei respinsi (ordonati descrescator dupa medie).
(meniu cu switch)
