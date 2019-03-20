#include <stdio.h>
#include <math.h>
#define MAXLITER 10

void CountingSort(char A[][MAXLITER], int k, int A_rozmiar, int pozycja) {

  int C[k];
  char B[A_rozmiar][MAXLITER];
  
  for (int i = 0; i < k; i++) {
    C[i] = 0;
  }
  for (int j = 0; j < A_rozmiar; j++) {
    C[(int)A[j][pozycja]] = C[(int)A[j][pozycja]] + 1;
  }
  for (int j = 1; j < k; j++) {
    C[j] = C[j] + C[j-1];
  }
  for (int j = A_rozmiar-1; j >= 0; j--) {
    for(int l = MAXLITER-1; l >= 0; l--) {
      B[C[(int)A[j][pozycja]]-1][l] = A[j][l];
    }
    C[A[j][pozycja]] = C[A[j][pozycja]] - 1;
  }

  for (int i = 0; i < A_rozmiar; i++) {
    for (int j = 0; j < MAXLITER; j++) {
      A[i][j] = B[i][j];
    }
  }
}

void RadixSort(char A[][MAXLITER], int k, int rozmiar) {
  
  for (int i = MAXLITER-1; i >= 0; i--) {
    CountingSort(A, k, rozmiar, i);
  }
}

void ZliczanieLiter (char A[][MAXLITER], int B[], int rozmiar) {

  for (int i = 0; i < rozmiar; i++) { //F. zlicza ilosc liter kazdego slowa.
    B[i] = 0;
  }
  
  for (int i = 0; i < rozmiar; i++) {
    for (int j = 0; A[i][j]!='\0'; j++) {
      B[i] += 1;
    }
  }
  
}
  
int main() {

  char tab[][MAXLITER] = {"hamak", "kiri", "ala", "aza", "kajak", "stojak", "afro", "kiwi", "kizi", "zeszyt"};
  int rozmiar = sizeof(tab)/sizeof(tab[0]);
  int tabdlugosci[rozmiar];
  
  RadixSort(tab, 123, rozmiar);   // k = 27 dlatego, ze alfabet ma 26 lit.
                                     // i do tego jeszcze 0 dla konca slowa.
  for (int i = 0; i < rozmiar; i++) {
    printf("%s\n", tab[i]);
  }
}
