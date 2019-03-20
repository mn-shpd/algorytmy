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
    C[(int)A[j][pozycja]%96] = C[(int)A[j][pozycja]%96] + 1;
  }
  for (int j = 1; j < k; j++) {
    C[j] = C[j] + C[j-1];
  }
  for (int j = A_rozmiar-1; j >= 0; j--) {
    for(int l = MAXLITER-1; l >= 0; l--) {
      B[C[(int)A[j][pozycja]%96]-1][l] = A[j][l];
    }
    C[A[j][pozycja]%96] = C[A[j][pozycja]%96] - 1;
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
  
int main() {

  char tab[][MAXLITER] = {"hamak", "akustyk", "ala", "aza", "kajak", "stojak", "afro", "kiwi", "kizi", "zeszyt"};
  int rozmiar = sizeof(tab)/sizeof(tab[0]);
  
  RadixSort(tab, 27, rozmiar);   // k = 27 dlatego, ze alfabet ma 26 lit.
                                     // i do tego jeszcze 0 dla konca slowa.
  for (int i = 0; i < rozmiar; i++) {
    printf("%s\n", tab[i]);
  }
}
