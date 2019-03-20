#include <stdio.h>

int main() {
  char **tab = {"slowo1", "slowo2"};
  int x = sizeof(tab)/sizeof(tab[0]);
  printf("%s - %d", tab[0], x);
}
