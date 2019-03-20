#include <stdio.h>
#include <string.h>
#define MAXLITER 30
#define IL_KLUCZY 3744
#define STALA 11
#define M 1870      //Musi byc mniejsze od 1872

int main() {

  FILE *plik;
  int indeks = 0;
  char napis[MAXLITER];
  char tabnap[IL_KLUCZY][MAXLITER];
  char *result;
  long int klucze[IL_KLUCZY];
  long int klucz;
  int indeks2 = 0;
  int T[M];
  long int hasz;
  int licznik_zer = 0, max_wart, srednia_wart;
  float suma_niezer = 0;
  
  plik = fopen("3700.txt", "r");

  while(1) {
    result = fgets(napis, 30, plik);
    if (result == NULL)
      break;
    else {
      strcpy(tabnap[indeks], napis);
      indeks++;
    }
  }
  fclose(plik);
  
  for (int i = 0; i < indeks; i++) {
    klucz = STALA*tabnap[i][0] + tabnap[i][1];
    for (int j = 2; tabnap[i][j] != '\n'; j++) {
      klucz = (klucz*STALA) + tabnap[i][j];
    }
    if (klucz < 0) {
      printf("ERROR\n");
      return 0;
    }
    klucze[indeks2] = klucz;
    indeks2++;
  }

  /*  for  (int i = 0; i < indeks; i++) {
    printf("%li\n", klucze[i]);
    }
  */

  /////////////////////////////
  
  for (int i = 0; i < M; i++) {        //Wyzerowanie tablicy z iloscia kluczy.
    T[i] = 0;
  }

  for (int i = 0; i < 2*M; i++) {
    hasz = klucze[i] % M;
    T[hasz] += 1;
  }

  /////////////////////////////
  
  max_wart = T[0];
  
  for (int i = 0; i < M; i++) {
    if (T[i] == 0) licznik_zer++;
    if (T[i] > max_wart) max_wart = T[i];
    if (T[i] != 0) suma_niezer += T[i];
  }
  printf("Wartosc M: %d \t Ilosc kluczy: %d\n\n", M, 2*M);
  printf("Ilosc zerowych pozycji w tablicy T: %d\n", licznik_zer);
  printf("Maksymalna wartosc w T: %d\n", max_wart);
  printf("Srednia wartosc pozycji niezerowych: %f\n\n", suma_niezer/(M-licznik_zer));
}
