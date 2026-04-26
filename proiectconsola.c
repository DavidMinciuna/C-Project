#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>
struct Joc {
    float dimensiune;
    char nume[100]; // e string 
};
float limita=1024;
float sum=0;
void meniu(){
  printf("\033[0;32m===Meniul Principal===\033[0m\n");
  printf("\033[0;32m1. Vizualizare Jocuri\033[0m\n");
  printf("\033[0;32m2. Instalare Jocuri\033[0m\n");
  printf("\033[0;32m3. Dezinstalare Jocuri\033[0m\n");
  printf("\033[0;32m0. Exit\033[0m\n");
  printf("\033[0;32mAlege o optiune: \033[0m");
}
bool joc_existent(char nume_cautat[]) {
    FILE *fisier = fopen("consola.txt", "r");
    if (fisier==NULL){
        return false;
    }
    char linie[256];
    struct Joc joc1;
    while (fgets(linie, sizeof(linie), fisier)) {
        sscanf(linie, "%[^|]| %f", joc1.nume, &joc1.dimensiune);
        if (stricmp(joc1.nume, nume_cautat)==0){
            fclose(fisier);
            return true;
        }
    }
    fclose(fisier);
    return false;
}
void citirefisier(){
  FILE *fisier;
    fisier=fopen("consola.txt","r");
    if(fisier==NULL){
      printf("Nu s-a putut deschide consola.\n");
}
char numelinie[256];
    struct Joc joc1;
    while (fgets(numelinie, sizeof(numelinie), fisier)) 
    {
      sscanf(numelinie, "%[^|]| %f", joc1.nume, &joc1.dimensiune);
      printf("Nume: \033[0;35m%s\033[0m, Dimensiune: \033[0;33m%.2f\033[0m GB\n", joc1.nume , joc1.dimensiune);
    }
    fclose(fisier);
}
void vizualizare_joc(){
  printf("\e[1;1H\e[2J");
    printf("\033[0;32m===Vizualizare Jocuri===\033[0m\n\n");
    citirefisier();
    printf("\033[0;36mApasa ENTER pentru a te intoarce la meniul principal...\033[0m\n");
    getchar();
    printf("\e[1;1H\e[2J");   
}
void limitaconsola(){
  FILE *fisier;
    fisier=fopen("consola.txt","r");
     if(fisier==NULL){
      printf("Nu s-a putut deschide consola.\n");
      printf("\033[0;36m\nApasa ENTER pentru a reveni la meniul principal...\033[0m");
      return;
     }
      char numelinie[256];
    struct Joc joc1;
    sum=0;
    while (fgets(numelinie, sizeof(numelinie), fisier)) 
    {
      sscanf(numelinie, "%[^|]| %f", joc1.nume, &joc1.dimensiune);
      sum+=joc1.dimensiune;
    }
    printf("Ati folosit \033[0;33m%.2f\033[0m GB din limita de \033[0;33m%.2f\033[0m GB\n",sum,limita);
    fclose(fisier);

}
void instalare_joc(){
  printf("\e[1;1H\e[2J");
  FILE *fisier;
    fisier=fopen("consola.txt", "a");    
    struct Joc joc1;
    printf("\n");
    
    printf("\033[0;32m===Instalare Joc===\033[0m\n");
    printf("Introduceti Numele jocului dorit: \n");
    scanf("%[^\n]", joc1.nume);
    getchar();
    if (strlen(joc1.nume)==0) {
      printf("Numele jocului nu poate fi gol!\n");
      printf("\033[0;36m\nApasa ENTER pentru a reveni...\033[0m");
      getchar();
      fclose(fisier);
      return;
}
    if (joc_existent(joc1.nume))
      {
        printf("Jocul este deja instalat.\n");
        printf("\033[0;36m\nApasa ENTER pentru a reveni...\033[0m");
      getchar();
      fclose(fisier);
      printf("\e[1;1H\e[2J");
      return;
      }
    
    printf("Introduceti Dimensiunea jocului: \n");
    if (scanf("%f", &joc1.dimensiune) !=1 || joc1.dimensiune <=0) {
      printf("Dimensiune invalida!\n");
      getchar();
      fclose(fisier);
        printf("\033[0;36m\nApasa ENTER pentru a reveni...\033[0m");
        getchar();
        return;
}
    getchar();
    limitaconsola();
    if (fisier==NULL)
    {
        printf("Nu s-a putut deschide consola.\n");
    }
    else
    {
        if (limita<=sum+joc1.dimensiune){
          printf("Nu ai destula memorie pentru instalarea jocului!\n");
        }
        else {
        fprintf(fisier, "%s| %.2f GB\n", joc1.nume, joc1.dimensiune);
        printf("Jocul: \033[0;35m%s\033[0m cu Dimensiunea \033[0;33m%.2f\033[0m a fost adaugat\n",joc1.nume,joc1.dimensiune);  
      }
    }
  printf("\033[0;36m\nApasa ENTER pentru a reveni la meniul principal...\033[0m");
  getchar();
  fclose(fisier);
  printf("\e[1;1H\e[2J");
}
void dezinstalare_joc(){
  printf("\e[1;1H\e[2J");
  printf("\033[0;32m===Dezinstalare Joc===\033[0m\n");
  printf("Introduceti numele jocului dorit: \n");
  char nume_joc[100];
  scanf("%[^\n]", nume_joc);
    getchar();
  if (!joc_existent(nume_joc)) {
        printf("Jocul nu este instalat.\n", nume_joc);
        printf("\033[0;36mApasa ENTER pentru a reveni la meniul principal...\033[0m\n");
        getchar();
        printf("\e[1;1H\e[2J");
        return;
  }
  FILE *fisier;
  fisier=fopen("consola.txt","r");
  FILE *fisiertemp;
  fisiertemp=fopen("temp.txt","a");
  if (fisier == NULL){
    printf("Nu s-a putut deschide consola.\n");
    fclose(fisier);
    fclose(fisiertemp);
    return;
  }
  char linie[256];
  struct Joc joc1;
    while (fgets (linie,256,fisier)){
        sscanf(linie,"%[^|]| %f",joc1.nume,&joc1.dimensiune);
        if(stricmp(joc1.nume,nume_joc) !=0){
          fprintf(fisiertemp,"%s",linie);
        }
      }
      fclose(fisiertemp);
       fclose(fisier);
        remove("consola.txt");
        rename("temp.txt", "consola.txt");
        printf("Jocul '\033[0;35m%s\033[0m' a fost \033[0;31mdezinstalat\033[0m cu succes.\n", nume_joc);
  printf("\033[0;36mApasa ENTER pentru a reveni la meniul principal...\033[0m\n");
  getchar();
  printf("\e[1;1H\e[2J");
}
int main(){
    
    int optiune;
    bool afisare_meniu = true;

    while (afisare_meniu) 

    {
      meniu();
      scanf("%d",&optiune);
      getchar();
      switch (optiune){

        case 0: {
          printf("\e[1;1H\e[2J");
          printf("\033[0;31mAti iesit din program!\033[0m\n");
          afisare_meniu = false;
          break;
        }
        
        case 1: {
         printf("\e[1;1H\e[2J");
          vizualizare_joc();
              break;
      } 
        case 2: {
          printf("\e[1;1H\e[2J");
          instalare_joc();
          break;
        }
        case 3: {
          printf("\e[1;1H\e[2J");
          dezinstalare_joc();
          break;
        }
        default: {
          printf("\e[1;1H\e[2J");
          printf("Optiune invalida!\n");
          sleep(2);
          printf("\e[1;1H\e[2J");
    }
}
}
 return 0;
}