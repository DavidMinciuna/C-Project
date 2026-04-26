# C-Project
#  Sistem de Gestionare a Jocurilor pe Consolă Virtuală

##  Descriere

Acest proiect este o aplicație realizată în limbajul **C**, care simulează o **consolă virtuală de jocuri** cu o capacitate maximă de stocare de **1 TB (1024 GB)**.

Programul permite utilizatorului să administreze jocurile instalate printr-un meniu interactiv în consolă, oferind funcționalități de bază precum instalarea, dezinstalarea și vizualizarea jocurilor.

Datele sunt salvate într-un fișier text (`consola.txt`), asigurând persistența informațiilor între rulări.

---

##  Funcționalități

###  Vizualizare jocuri
- Afișează toate jocurile instalate
- Include dimensiunea fiecărui joc (în GB)

###  Instalare joc
- Introducerea numelui jocului
- Introducerea dimensiunii
- Verificare:
  - nume valid
  - joc duplicat
  - spațiu disponibil
- Salvare în fișier

###  Dezinstalare joc
- Eliminarea jocului după nume
- Actualizarea fișierului
- Confirmarea ștergerii

###  Gestionare memorie
- Calcul spațiu utilizat
- Limită maximă: **1024 GB**
- Blocarea instalării dacă memoria este depășită

---
###  Validări implementate
- Nume joc nevid
- Prevenire duplicate
- Dimensiune validă (>0)
- Verificare spațiu disponibil
- Verificare existență joc la ștergere
---
##  Structura datelor

```c
struct Joc {
    float dimensiune;
    char nume[100];
};
