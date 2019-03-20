#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 150000
#define STALA 2704
#define MLD 1000000000.0

int Partition(int A[], int p, int r) {
  int temp;
  int x = A[r];
  int i = p-1;

  for(int j = p; j <= r; j++) {
    if (A[j]<=x) {
      i = i+1;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  if (i < r) return i;
  else return i-1;
      
}

void BubbleSort(int A[], int p, int rozmiar) {
  int temp;
  do {
    for(int i = p; i < p+rozmiar-1; i++) { //potrzebna modyfikacja
      if (A[i] > A[i+1]) {               //ze wzgledu na to, ze pods. bubblesort
	temp = A[i];                    //bierze cala tablice pod uwage
	A[i] = A[i+1];
	A[i+1] = temp;
      }
    }
    rozmiar--;
  }while (rozmiar > 1);
}

void Quicksort(int A[], int p, int r) {
  int rozmiar = r-p+1;
  if (rozmiar < STALA) {
    BubbleSort(A, p, rozmiar);       //modyfikacja o podanie poczatku tab.
  }
  else {
    if (p < r) {
      int q=Partition(A, p, r);
      Quicksort(A, p, q);
      Quicksort(A, q+1, r);
    }
  }
}

int main() {
  int tab[MAX];
  int rozmiar = 0;
  FILE *zw;
  char zt[30], *result;
  struct timespec tp0, tp1;
  long double Tn;
  srand(time(NULL));
  
  zw=fopen("wejscie.txt", "r");

  while (1) {
    result = fgets(zt, 30, zw);
    if (result == NULL)
      break;
    else {
      tab[rozmiar] = atoi(zt);
      rozmiar++;
    }
  }
  
  fclose(zw);
  
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
  Quicksort(tab, 0, rozmiar-1);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("Czas: %3.10Lf\n", Tn);

  FILE *PLIK;
  PLIK = fopen("wyjscie.txt", "w");
  
  for (int i = 0; i < rozmiar; i++) {
    fprintf(PLIK, "%d\n", tab[i]);
  }

  fclose(PLIK);
}
      
