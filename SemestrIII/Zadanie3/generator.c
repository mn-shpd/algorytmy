#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ZAKRES 150000
int main() {

  srand(time(NULL));
  int n;

  FILE *PLIK;
  PLIK = fopen("wejscie.txt", "w");
  
  for (int i = 0; i < ZAKRES; i++) {
    n = rand()%ZAKRES + 1;
    fprintf(PLIK, "%d\n", n);
  }

  fclose(PLIK);

}
  
