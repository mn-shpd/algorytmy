#include <stdio.h>

#define SIZE_X 4  //dlugosc pierwszego ciagu 
#define SIZE_Y 3  //dlugosc drugiego ciagu

//Zmienne globalne zdefiniowane dla potrzeb uzycia tablicy dwuwymiarowej w funkcji.

void LCS_length(char *x, char *y, int c[SIZE_X+1][SIZE_Y+1], char b[SIZE_X][SIZE_Y]) {

  //SIZE+1 , SIZE+1 rozmiar tablicy dwuwymiarowej wiekszy o 1, bo trzeba pomiescic zerowa kolumne i wiersz.
  
  printf("\n");
  
  int i,j;
  
  for (i = 0; i < SIZE_X+1; i++) {          //Wyzerowanie pierwszej kolumny i wiersza.
    c[i][0] = 0;
  }
  for (i = 0; i < SIZE_Y+1; i++) {
    c[0][i] = 0;
  }

  for (i = 1; i < SIZE_X+1; i++) {
    for (j = 1; j < SIZE_Y+1; j++) {
      if(*(x+i-1) == *(y+j-1)) {           //Warunek, gdy znaki sa takie same.
	c[i][j] = c[i-1][j-1] + 1;
	b[i-1][j-1] = '\\';
      }
      else if (c[i-1][j] >= c[i][j-1]) {   //Znaki rozne, wartosc wyzej wieksza.
	c[i][j] = c[i-1][j];
	b[i-1][j-1] = '|';
      }
      else {
	c[i][j] = c[i][j-1];              //Znaki rozne, wartosc po lewej wieksza.
	b[i-1][j-1] = '-';
      }
    }
  }

  for (i = 0; i < SIZE_X+1; i++) {
    for (j = 0; j < SIZE_Y+1; j++) {
      printf("%d ", c[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      printf("%c ", b[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void LCS_print(char *x, char *y, int i, int j, char b[SIZE_X][SIZE_Y]) { 

  printf("%d %d - ", i, j);
  
  if (i < 0 || j < 0) {
    printf("koniec\n\nNWP = ");
    return;
  }
  if (b[i][j] == '\\') {
    printf("poprzek\n");
    LCS_print(x, y, i-1, j-1, b);
    printf("%c", x[i]);
  }
  else if (b[i][j] == '|') {
    printf("gora\n");
    LCS_print(x, y, i-1, j, b);
  }
  else {
    printf("lewo\n");
    LCS_print(x, y, i, j-1, b);
  }
}

int main() {

  char tab1[] = {'x', 'y', 'c', 'a'};
  char tab2[] = {'x', 'c', 'a'};
  int c[SIZE_X+1][SIZE_Y+1];
  char b[SIZE_X][SIZE_Y];
  
  LCS_length(tab1, tab2, c, b);
  LCS_print(tab1, tab2, SIZE_X-1, SIZE_Y-1, b); //Pomniejszone rozmiary, poniewaz nastapi iteracja po el. tab.

  printf("\n");
}

