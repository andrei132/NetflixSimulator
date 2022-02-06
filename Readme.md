# Netflix Simulator
## Girnet Andrei
---

## Descriere
---
Implementarea unui sistem de filme, in care utilizatorul va putea interactiona, va putea avea filme si serial preferate vizionate, lista de dorinte si altele.

Exista 4 categorii de seriale:
1. Tendințe
2. Documentare
3. Tutoriale pentru limbajul C
4. Top10 în România

Fiecare serial are un ID al categoriei din care face parte, un nume unic, un rating, și un număr de sezoane. Un serial este o coadă de unul sau mai multe sezoane, iar un sezon este o coadă de unul sau mai multe episoade.
Fiecare sezon are un număr de episoade, iar fiecare episod are o durată în minute.

Cum sunt implementate fiecare tip de serial/film:
* Liste pentru gestionarea categoriilor de seriale
* Coada watch_later
* Stiva currently_watching
* Stiva history

## Structuri de Date folosite
---
+ Serial 

    - Structura informatiie

+  CelulaL

    - Structura unei celule a unei liste generalizate simplu inlantuite

+ TLSI 

    - Pointer la structura celulei listei 

+ Coada 

    - Structura unei cozi cu celule generalizate

+ TCoada

    - Pointer la o structura a cozei

+ Stiva

    - Structura unei stive cu celule generalizate

+ TStiva 

    - Pointer la structura unei stive

## Functii de prelucrare a listelor simple inlantuite
---
+ initCelula

    - Aloca celula cu info primit ca parametru si cimp urm NULL,
    returneaza celula alocata

+ insertStart

    - Insereaza la inceputul unei liste o celula 

+ insertOrdonat

    - Insereaza intr-o lista comform unei reguli

+ first10

    - Parcurge o lista si intoarce a 10-cea celula daca exista sau NULL
    daca lista are mai putin de 10 celule

+ insertPos

    - Insereaza intr-o lista simplu inlantuita intr-o pozitie anumita daca
    aceasta exista, daca sunt mai mult de 10 celule restul se dezaloca

+ findList

    - Gaseste celula cu o informatie anumita si dupa parametrul elim
    il sterge din lista

+ showList

    - Afiseaza o lista simplu inlatuita

+ freeList

    - Dezaloca o lista simplu inlantuita

## Functii de prelucrare a unei cozi
---
+ initCoada

    - Initializeaza o coada 

+ insertCoada
    
    - Insereaza o celula intr-o coada

+ extrageCoada

    - Extrage virful unei cozi

+ findCoada

    - Cauta intr-o coada o informatie anumita eliminindo dupa dorinta,
    coada nu e modificata din punt de vedere al ordinii

+ showCoada

    - Afiseaza o coada fara a o modifica

+ freeCoada

    - Dezaloca o coada

## Functii de prelucrare a unei stive
---
+ initStiva

    - Initializarea unei stive

+ extrageStiva

    - Extrage virful stivei modificindul

+ insertStiva

    - Insereaza o celula intr-o stiva

+ rastoarnaStiva

    - rastoarna o stiva BAZS(stiva)->VRFS(stiva) devine 
    VRFS(stiva)->BAZS(stiva)

+ findStiva

    - Cauta intr-o stiva si elimina celula dupa dorinta o informatie
    nemodificind ordinea stivei

+ showStiva

    - Afiseaza o stiva nemodificind ordinea stivei initiale

+ freeStiva

    - functia de dezalocare a unei stive

## Functii de prelucrare a fisierului si a serialelor/filmelor
---
+ add

    - adauga o informatie intr-o lista din cele 3 posibile

+ add_top

    - adauga o informatie in top10 la o positie anumita

+ addSez

    - adauga minute de vizionat la cimpul nrMin la un serial care exista,
    si adauga sezonul in coada

+ later

    - Muta un serial in wLater

+ watch

    - Gaseste un serial si il muta in stiva cWatch, daca deja e acolo
    este mutat in virful stivei, daca serialul a fost vizionat integral
    e mutat in hystory

+ prelucrareaFisierului
    
    - Recunoaste comanda si executa comform conditiei

## Functii generale cu seriale
---
+ freeInt

    - Functia de dezalocare a *(int **)
    
+ freeFunction

    - Dezaloca un Serial chiar si daca a fost alocat partial

+ initSerial

    - Citeste dintr-un char* toata informatia unui Serial si intoarce adresa

+ afiElement

    - Functia de afisare a unui element

+ cmp

    - functia de comparare a doua Serial, daca un serial are rating -1
    se compara doar numele