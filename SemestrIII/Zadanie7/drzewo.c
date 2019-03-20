#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct drzewo {
  struct drzewo *parent;
  int key;
  int ilosc;
  struct drzewo *left, *right;
};

void tree_insert(struct drzewo **T, int z) {

  int flaga;
  
  if(*T==NULL) {  //Sprawdzam na co wskazuje wskaznik (Jesli na NULL, to nie ma jeszcze zadnego el.)
    *T = (struct drzewo *)malloc(sizeof(struct drzewo)); //Przydzielam pamiec, bo wskazuje na NULL
    (**T).parent = NULL;  //Jest to pierwszy wezel, wiec nie ma rodzica
    (**T).key = z;    //Wprowazdam klucz
    (**T).ilosc = 1;    //Ilosc jeden, bo to pierwszy element
    (**T).left = NULL; //Jest to pierwszy element, wiec nie ma zadnych synow.
    (**T).right = NULL;
  }
  else {
    struct drzewo * x = *T;            
    struct drzewo * y = NULL;
    while(x != NULL) {
      y = x;
      flaga = 0;
      if (z == (*x).key) {    //Sprawdza kazdy wezel czy juz jest taki klucz, jesli tak to zwieksza pole ilosc
	(*x).ilosc += 1;     //i wychodzi z funkcji, a jak nie to ustawia wartosc flagi
	return;             //0 jesli ma zapisac nowy wezel po lewej stronie; 1 jesli po prawej
      }
      if (z < (*x).key) {
	x = (*x).left;
	flaga = 0;
      }
      else {
	x = (*x).right;
	flaga = 1;
      }
    }
    struct drzewo *nowy_element = (struct drzewo*)malloc(sizeof(struct drzewo));
    (*nowy_element).parent = y;
    (*nowy_element).key = z;
    (*nowy_element).ilosc = 1;
    (*nowy_element).left = NULL;
    (*nowy_element).right = NULL;
    if (flaga == 0) (*y).left = nowy_element;   //y jest tutaj ostatnim sprawdzanym wezlem. 
    else (*y).right = nowy_element;            //nowy klucz byl porownywany ostatni raz z kluczem wezla y.
  }
}

struct drzewo * tree_search(struct drzewo *T, int x) { //szuka klucza po wezlach i zwraca wskaznik na wezel

  if (T == NULL) {
    printf("Nie zapisano jeszcze zadnego klucza.");
    return NULL;
  }
  else {
    struct drzewo *temp = T;
    while(temp != NULL && x != (*temp).key) {
      if (x < (*temp).key)
	temp = (*temp).left;
      else
	temp = (*temp).right;
    }
    return temp;
  }
}

struct drzewo * tree_min(struct drzewo *T) {
  
  struct drzewo *temp = T;
  while((*temp).left != NULL)
    temp = (*temp).left;
  return temp;
}
void drukuj_inorder(struct drzewo *T) {

  if(T == NULL) {
    printf("Drzewo jest puste!\n");
    return;
  }
  
  struct drzewo *temp = T;
  
  if((*temp).left != NULL) {       //Sprawdza kolejno lewych synow i jesli lewy syn wystepuje, to znowu wywoluje dla
    printf("\n");                 //niego funkcje drukuj_inorder
    drukuj_inorder((*temp).left);
  }
  
  printf("%d(%d) ", (*temp).key, (*temp).ilosc);   //Wyswietla wartosc z rodzica.
  
  if((*temp).right != NULL) {         //jw. tylko ze prawy syn
    printf("\n");
    drukuj_inorder((*temp).right);
  }
}

void tree_delete(struct drzewo **T, int z) {

  int temp_key;
  
  if(*T == NULL) {
    printf("Drzewo jest puste.\n");
    return;
  }
  struct drzewo *temp = tree_search(*T, z);        //najpierw wyszukuje wezel, w ktorym wystepuje dany klucz.
  struct drzewo *y;
  struct drzewo *y2;
  
  if(temp == NULL) {
    printf("Nie ma takiego klucza w drzewie.\n");
    return;
  }
  
  if((*temp).ilosc > 1) {                  //jesli w znalezionym wezle ilosc jest wieksza od 1, to zmniejsza te ilosc
    (*temp).ilosc -= 1;                    //o 1 i wychodzi z funkcji (niefizyczne usuniecie).
    return;
  }
  
  if((*temp).left == NULL && (*temp).right == NULL){   //warunek dla wezla nie posiadajacego synow.

    if((*temp).parent == NULL) {            //jesli wezel ten jest dodatkowo pierwszym wezlem, to sie wykonuje ten kod.
      free(temp);
      *T = NULL;
      return;
    }
    
    if(temp == (*(*temp).parent).left) {    //a jesli nie, to sprawdza czy dany wezel jest lewym/prawym synem swojego
      (*(*temp).parent).left = NULL;          //rodzica, zeby w rodzicu zlikwidowac odpowiedniego syna.
      free(temp);
    }
    else {
      (*(*temp).parent).right = NULL;
      free(temp);
    }
    return;
  }
  
  if((*temp).left != NULL && (*temp).right != NULL) { //warunek dla wezla, ktory posiada dwoch synow.
    y2 = tree_min((*temp).right);                   //przypisuje do zmiennej wskaznikowej y2 wezel najbardziej w lewo
    temp_key = (*y2).key;                          //od prawego syna wezla, ktory chcemy usunac.
    tree_delete(T, (*y2).key);          //zapisuje w zmiennej tymczasowej wartosc klucza z y2.
    (*temp).key = temp_key;          //wywoluje funkcje usun dla wezla y2.
    //(*temp).parent = NULL;          //przypisuje do pierwotnie usuwanego klucza klucz z y2 i wychodzi z funkcji.
    return;
  }
  if((*temp).left != NULL) {                 //warunek dla wezla, ktory posiada tylko lewego syna.
    (*(*temp).left).parent = (*temp).parent;  //Ustawia w synie rodzica na rodzica wezla ktorego usuwamy.
    y = (*temp).left;                     //Zapisuje lewego syna do zmiennej tymczasowej.
    if ((*temp).parent == NULL) {       //Sprawdzamy czy wezel, ktory usuwamy znajduje sie na szczycie drzewa.
      *T = (*temp).left;             //Jesli tak, to swojego jedynego lewego syna czyni poczatkiem drzewa(szczytem)
      return;
    }
    if (temp == (*(*temp).parent).left) {  //Sprawdza, ktorym synem jest usuwany wezel u swojego rodzica (czy lewym?)
      (*(*temp).parent).left = y;         //Jesli tak, to w rodzicu usuwanego wezla lewego syna ustawia sie na jedynego
      free(temp);                        //lewego syna wezla usuwanego.
      return;
    }
    else {
      (*(*temp).parent).right = y;       //Podobnie jw. tylko ze prawy syn.
      free(temp);
      return;
    }
  }
  if((*temp).right != NULL) {           //warunek dla wezla, ktory posiada tylko prawego syna (analogicznie jw.)
    (*(*temp).right).parent = (*temp).parent;
    y = (*temp).right;
    if ((*temp).parent == NULL) {
      *T = (*temp).right;
      return;
    }
    if (temp == (*(*temp).parent).right) {
      (*(*temp).parent).right = y;
      free(temp);
      return;
    }
    else {
      (*(*temp).parent).left = y;
      free(temp);
      return;
    }
  }
}

int main() {
  struct drzewo *korzen;
  korzen = NULL;
  int r;
  srand(time(NULL));
  
  tree_insert(&korzen, 2);
  tree_insert(&korzen, 3);
  tree_insert(&korzen, 1);
  tree_insert(&korzen, 5);
  tree_insert(&korzen, 4);
  drukuj_inorder(korzen);

  /*
    for (int i = 0; i < 10; i++) {
    r = rand()%20;
    tree_insert(&korzen, r);
  }
  */
  // struct drzewo * doszukania;
  //doszukania = tree_search(korzen, 9);
  //if(doszukania != NULL)
  //printf("%d\n", (*doszukania).key);
  //else
  //printf("Nie ma takiego klucza w drzewie!\n");

  
  // tree_delete(&korzen, 2);
  //tree_delete(&korzen, 3);
  //tree_delete(&korzen, 1);
  //tree_delete(&korzen, 4);
  tree_delete(&korzen, 5);
  printf("\n");
  drukuj_inorder(korzen);
  /*
  tree_insert(&korzen, 2);
  tree_insert(&korzen, 2);
  tree_insert(&korzen, 1);
  tree_insert(&korzen, 5);
  tree_insert(&korzen, 4);
  drukuj_inorder(korzen);
  tree_delete(&korzen, 2);
  drukuj_inorder(korzen);
  */
}
