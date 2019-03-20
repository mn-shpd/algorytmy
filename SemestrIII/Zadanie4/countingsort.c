#include <stdio.h>
#include <math.h>

void CountingSort(int A[], int k, int A_rozmiar, int dzielnik) {

  int C[k];
  int B[A_rozmiar];
  int dzielnik2 = dzielnik/10;
  
  for (int i = 0; i < k; i++) {
    C[i] = 0;
  }
  for (int j = 0; j < A_rozmiar; j++) {
    C[(A[j]%dzielnik)/dzielnik2] = C[(A[j]%dzielnik)/dzielnik2] + 1;
  }
  for (int j = 1; j < k; j++) {
    C[j] = C[j] + C[j-1];
  }
  for (int j = A_rozmiar-1; j >= 0; j--) {
    B[C[(A[j]%dzielnik)/dzielnik2]-1] = A[j];
    C[(A[j]%dzielnik)/dzielnik2] = C[(A[j]%dzielnik)/dzielnik2] - 1;
  }

  for (int i = 0; i < A_rozmiar; i++) {
    A[i] = B[i];
  }
}

void RadixSort(int A[], int d, int k, int rozmiar) {
  
  int x;
  
  for (int i = 1; i <= d; i++) {     // d - maksymalna ilosc cyfr w liczbach
    x = pow(10, i);                 // k - zakres wartosci cyfr (standardowo 0-9)
    CountingSort(A, k, rozmiar, x);
  }
}
int main() {

  int tab[] = {4, 25, 5, 9, 23, 100, 7, 2, 1, 3, 4, 4, 999};
  int rozmiar = sizeof(tab)/sizeof(tab[0]);

  RadixSort(tab, 3, 10, rozmiar);

  for (int i = 0; i < rozmiar; i++) {
    printf("%d\n", tab[i]);
  }
}
