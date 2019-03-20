#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLITER 40        //Maksymalna dlugosc nazwiska
#define IL_NAZWISK 20000   //Maksymalna ilosc nazwisk mozliwych do wczytania
#define STALA 5           //Stala do zamiany stringow na liczby
#define A 3              //Stala nr 1 do haszowania kwadratowego
#define B 4             //Stala nr 2 do haszowania kwadratowego
#define M 30           //Wielkosc tablicy haszowan (wartosc modulo)

struct klucz {
  int ilosc;
  char nazwisko[MAXLITER];
};

struct klucz tabstruktur[IL_NAZWISK];

long int H(long int key, int i) {     //Funkcja haszujaca (kwadratowe)

  long int result;
  result = ((key % M) + A*i + B*i*i) % M;
  return result;
}

int HashInsert(struct klucz *T[], struct klucz * x) {

  int i = 0;
  int j;
  long int klucz_x;              //Najpierw wylicza liczbe dla klucza (stringa) II sposob
 
  klucz_x = STALA*(*x).nazwisko[0] + (*x).nazwisko[1]; 
  
  for (int j = 2; (*x).nazwisko[j] != '\n'; j++) {
    klucz_x = (klucz_x*STALA) + (*x).nazwisko[j];
  }
  if (klucz_x < 0) {
    printf("Blad przy wyliczaniu klucza.\n");  // Gdy liczbowy klucz wyjdzie ujemny, to konczy dzial.
    return 0;
  }

  printf("Klucz: %li", klucz_x);
  
  do {                      //Proby wpisania klucza do tablicy haszowan.
    j = H(klucz_x, i);
    printf("\nProbuje wstawic klucz na pozycje %d... (i = %d)", j, i);
    if (T[j] == NULL) {
      printf(" Powodzenie!");
      T[j] = x;
      return j;
    }
    printf(" Niepowodzenie!");
    i += 1;
  } while (i < M);
  
  printf("\nBlad: brak miejsca!\n");
  
}

int HashSearch(struct klucz *T[], struct klucz x) {   //Tez zamienia strina na liczbe. II sposob.

  int i = 0;
  int j;
  long int klucz_x;
 
  klucz_x = STALA*x.nazwisko[0] + x.nazwisko[1];
  
  for (int j = 2; x.nazwisko[j] != '\n'; j++) {
    klucz_x = (klucz_x*STALA) + x.nazwisko[j];
  }
  if (klucz_x < 0) {
    printf("Blad przy wyliczaniu klucza.\n");
    return 0;
  }

  printf("Klucz: %li", klucz_x);
  
  do {
    j = H(klucz_x, i);
    printf("\nProbuje znalezc klucz na pozycji %d...(i = %d)", j, i);
    if (strcmp((*T[j]).nazwisko, x.nazwisko) == 0) {   //strcmp() - zwraca 0, gdy stringi sa takie same
      printf(" Powodzenie!");
      return j;
    }
    printf(" Niepowodzenie!");
    i += 1;
  } while ((T[j] != NULL) && (i < M));
  printf("\nNie znaleziono szukanego klucza.");
}

int main() {

  FILE *plik;
  int indeks = 0;
  char napis[MAXLITER];
  char *result;
  int licznik;
  struct klucz * T[M];
 
  plik = fopen("nazwiskaASCII", "r");

  while(1) {
    result = fgets(napis, MAXLITER, plik);
    if (result == NULL)
      break;
    else {
      tabstruktur[indeks].ilosc = atoi(napis);
      licznik = 0;
      for (int i = 0; napis[i] != ' '; i++) {
	licznik++;
      }
      strcpy(tabstruktur[indeks].nazwisko, napis+licznik+1);
      indeks++;
      licznik = 0;
    }
  }
  fclose(plik);

  ////////////////////////////////

  for (int i = 0; i < M; i++) {        //Wyzerowanie tablicy z iloscia kluczy.
    T[i] = NULL;
  }

  int licznik2 = 0;
  int k;
  
  for (int i = 0; i < 20000; i++) {
    if (licznik2 >= M*0.8) {
      k = i;
      break;
    }
    licznik2 = 0;
    printf("\n\n%d. %s", i, (tabstruktur[i]).nazwisko);
    HashInsert(T, &tabstruktur[i]);
    for (int i = 0; i < M; i++) {
      if (T[i] != NULL) licznik2++;
    }
  }

  printf("\n\n////////////SZUKANIE/////////\n");
  
  for (int i = k-1; i >= k-21; i--) {
    printf("\n\nSzukam: %d. %s", i, tabstruktur[i].nazwisko);
    HashSearch(T, tabstruktur[i]);
  }

  printf("\n");
}
