## Tololoi Ilinca-Roxana, 311CB ## 
In primul rand, am atribuit nume numerelor care apar constant in calculele noastre:
- #define SECINHOUR 360 -> numarul de secunde intr-o ora
- #define MININHOUR 60 -> numarul de minute intr-o ora/numarul de secunde intr-un minut
- #define HOURINDAY 24 -> numarul de ore intr-o zi
- #define STARTYEAR 1970 -> anul de la care incepe numaratoarea
- #define JANUARY 1 -> numarul lunii ianuarie
- #define FEBRUARY 2 -> numarul lunii februarie
- #define MONTHINYEAR 12 -> numarul de luni in an
- #define DAYSINNORMALYEAR 365 -> numarul de zile intr-un an nebisect
- #define DAYSINBISECTYEAR 366 -> numarul de zile intr-un an bisect
- #define BISECTNONDIV 100 -> numarul la care nu se divide un an bisect(daca nu se divide nici la 400)
- #define BISECTDIV 400 -> numarul la care se divide un an bisect(daca se divide la 100)
- #define BISECTFEB 29 -> numarul de zile din februarie daca e an bisect
- #define ENDDAY 31 -> numarul de zile din decembrie(si celelalte luni cu 31 - am luat ca reper 31 decembrie, d-aia si endday)
- #define PSTDIF 8 -> diferenta de ore dintre pst si gmt
- #define LUNICU30 30 -> numarul de zile pt luni cu 30 de zile
- #define NONBISECTFEB 28 -> numarul de zile din februarie daca nu e an bisect

## Explicatii taskuri: ##
## TASK 1 ##
In cadrul taskului 1, trebuie convertit timestamp-ul in ora, minutul si secunda in care a fost creat. Luam numarul "timestamp", ce reprezinta numarul de secunde care au
trecut de la 1 ianuarie 1970, 00:00:00, pana in momentul crearii timestampului. Astfel, pentru a afla numarul de secunde, atribuim lui result.sec restul impartirii timestampului la 60, numarul de secunde dintr-un minut(vedem cate minute sunt in timestamp, iar restul e numarul cautat).
Pentru result.min, impartim timestampul la numarul de secunde dintr-un minut, deci obtinem numarul de minute, iar dupa luam restul impartirii acestui numar la numarul de minute dintr-o ora, adica minutele care nu "fac parte" dintr-o ora.
Pentru result.hour, impartim timestampul la numarul de secunde dintr-o ora, si astfel obtinem numarul de ore din timestamp. In continuare, facem restul impartirii la numarul de ore dintr-o zi, si obtinem numarul de ore care "nu fac parte" dintr-o zi. 

## TASK 2 ##
La taskul 2, trebuie sa obtinem ziua, luna si anul in care a fost creat timestampul. Pentru asta, am creat o functie ce determina numarul de zile al fiecarei luni in functie de luna(evident) si de anul dat.
Mai intai, am luat un vector cu numarul de zile din fiecare luna a anului(nonbisect sau nebisect, nu stiu cum se zice). Astfel, dupa o structura de decizie ce determina daca anul e bisect sau nu(daca se imparte la 400 sau daca se imparte la 4 si nu la 100),
returnam ori 29(in caz in care luna e februarie si anul e bisect), sau numarul aferent din vectorul mai sus mentionat.
Dupa, am declarat 2 variabile, una care reprezinta numarul de secunde dintr-o zi, si alta, numarul de secunde dintr-un an nebisect. Am atribuit si lui result.year numarul anului de la care incepe numaratoarea pentru timestamp.
Iau un while sa scad repetat din timestamp numarul de secunde dintr-un an nebisect, pana ajungem la numarul de secunde ce nu "fac parte" dintr-un an. In acelasi timp, pentru fiecare scadere, adaugam 1 la an, initializat la 1970.
Obtinem astfel anul timestampului. Dupa, initializam luna cu "1", ianuarie. Am luat inca un while, pentru care am folosit si functia "zilele_lunii", ce stabileste zilele unei luni in functie de luna si an. Anul fiind deja aflat, o folosim pentru a putea determina cat scadem de fiecare data cand vrem sa adaugam la numarul lunii.
Pentru fiecare scadere, numarul lunii creste. Dupa, am adaugat o structura de decizie pentru a ne asigura ca daca result.month ajunge sa aiba peste 12, sa treaca inapoi la 1. Timestampul ramas reprezinta numarul de secunde pentru zilele ce nu au putut fi incadrate intr-o luna. 
Impartim acest numar la numarul de secunde dintr-o zi si obtinem rezultatul.


## TASK 3 ##
La taskul 3, am memorat la inceput valorile pentru numarul de secunde dintr-o zi si numarul de secunde dintr-un an. Am setat result.year la 1970, anul de la care se incepe calcularea timestampului.
Dupa, in functie de an(daca e bisect sau nu), luam un while in care scadem din timestamp numarul de secunde al anului luat in considerare, iar anul creste cu fiecare parcurgere. Se ajunge astfel la numarul de secunde ce nu apartin unui an. 
In principiu, este acelasi lucru ca la taskul 2, doar ca se iau in calcul si anii bisecti, motiv pentru care am introdus structura de decizie ce decide tipul de an in cauza.


## TASK 4 ##
La taskul 4, functia convertUnixTimestampToDateTimeTZ primeste un stampila Unix (timestamp) si indicele unui fus orar intr-un vector de structuri TTimezone. 
Aceasta ajusteaza timestamp-ul pentru diferenta de ora UTC asociata fusului orar, apoi converteste timestamp-ul in date si ora, impachetand rezultatul intr-o structura TDateTimeTZ. In exemplul furnizat, vectorul de fusuri orare contine UTC, EET (Eastern European Time) cu o diferenta de 2 ore fata de UTC si PST (Pacific Standard Time) cu o diferenta orara negativa specificata de macro-ul PSTDIF.



## TASK 5 ##
La taskul 5, functia convertDateTimeTZToUnixTimestamp primeste o structura TDateTimeTZ care reprezinta o anumita data si ora intr-un anumit fus orar. 
Functia converteste aceasta informatie intr-un timestamp Unix, luand in considerare anii bisecti, zilele din luna si ajustand pentru diferenta de ora asociata fusului orar. Rezultatul este un timestamp reprezentand momentul specificat in secunde de la 1 ianuarie 1970, ora 00:00:00 UTC.



## TASK 6 ##
La taskul 6, functia printDateTimeTZ primeste o structura TDateTimeTZ si afiseaza data si ora asociate, impreuna cu numele lunii si numele fusului orar. 
Afisarea include si informatii despre diferenta de ora fata de UTC, indicand daca aceasta este pozitiva sau negativa. Afisarea se realizeaza intr-un format usor de citit, cu zilele lunii, numele lunii, anul si ora, minutele si secundele.


## TASK 7 si 8 ##
Codul contine doua parti principale. In primul caz (Task 7), programul sorteaza un numar N de date reprezentate sub forma unor biti, extrage componentele de zi, luna si an pentru fiecare data si afiseaza rezultatul in ordine cronologica. 
In al doilea caz (Task 8), programul verifica validitatea unui sir de biti (bitzi) in functie de un alt sir de control. Se extrag si proceseaza datele valide, apoi se sorteaza si se afiseaza rezultatul in ordine cronologica. 
Codul utilizeaza operatii pe biti, pointeri si functii predefinite pentru manipularea datelor si afisarea rezultatelor.


## TASK 9 ##
Codul implementeaza un program in limbajul C pentru gestionarea si planificarea evenimentelor intre persoane cu diferite fusuri orare. Se defineste o structura pentru reprezentarea unei persoane cu nume, fus orar si intervale orare disponibile. 
Programul primeste informatii despre fusurile orare si persoanele implicate, verifica disponibilitatea acestora pentru un eveniment cu durata specifica, si afiseaza un mesaj in cazul in care nu se gasesc participanti suficienti pentru eveniment.