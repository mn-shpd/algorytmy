#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 1000

//ITERACJA

void Heapify(int A[], int i, int rozmiar) {
  int l, r, largest, temp;

  while(i >= 0 && i < rozmiar) {
    l = 2*i+1;
    r = 2*i+2;
    if (l<rozmiar && A[l]>A[i])
      largest = l;
    else
      largest = i;
    if (r<rozmiar && A[r]>A[largest])
      largest = r;
    if (largest != i) {
      temp = A[i];
      A[i] = A[largest];
      A[largest] = temp;
      i = largest;
    }
    else
      break;
  }
}
  
void BuildHeap(int A[], int rozmiar) {
  for (int i = floor(rozmiar/2)-1; i>=0; i--)
    Heapify(A, i, rozmiar);
}

void HeapSort(int A[], int rozmiar) {
  int temp;
  BuildHeap(A, rozmiar);
  for (int i = rozmiar-1; i >= 0; i--) {
    temp = A[i];
    A[i] = A[0];
    A[0] = temp;
    Heapify(A, 0, i);
  }
}

int main() {
  int tab[MAX];
  int rozmiar = 0;
  FILE *zw;
  char zt[30], *result;
  
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
  
  HeapSort(tab, rozmiar);

  FILE *PLIK;
  PLIK = fopen("wyjscie.txt", "w");
  
  for (int i = 0; i < rozmiar; i++) {
    fprintf(PLIK, "%d\n", tab[i]);
  }

  fclose(PLIK);
		 
}
