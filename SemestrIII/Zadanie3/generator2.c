#include <stdio.h>
#define ZAKRES 150000
int main() {

  FILE *PLIK;
  PLIK = fopen("wejscie.txt", "w");
  
  for (int i = ZAKRES; i > 0; i--) {
    fprintf(PLIK, "%d\n", i);
  }

  fclose(PLIK);

}
