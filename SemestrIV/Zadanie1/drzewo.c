#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED 1
#define BLACK 0
#define SZER_EKR 80
#define IL_POZ 5

typedef struct drzewo *Wskwezla;
typedef struct drzewo {
  int klucz;
  int ilosc;
  int kolor;
  Wskwezla left, right, p;
} Twezla;

/*------------------------wklejony kod-------------------------------------*/


void drukuj(Wskwezla w);
/* funkcja drukujaca drzewo binarne na ekranie (tutaj tylko deklaracja) */
/* funkcja drukuje drzewo o korzeniu "w"                                */

void drukujDot(Wskwezla r);
  // generuje w plikach drzewo0.gv,  drzewo1.gv ...
  // opis drzew o korzeniu r do wydrukowania przez program dot
  // zlecenie "dot -Tpdf -O drzewo1.gv" utworzy plik "drzewo1.gv.pdf" 

/* ------------  implementacja ------------------------------------- */
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       if (w==NULL)   return; 
       wydruk[poziom][srodek]='*';
}

void drukujwew(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       int i,dl;
       char s[19];
       if (w==NULL)    return;
       if (w->kolor==BLACK)
         dl=sprintf(s,"%d",w->klucz);
       else
	 //	        dl=sprintf(s,"\e[31m%+d\e[0m",w->klucz);
       dl=sprintf(s,"%+d",w->klucz);
       for (i=0;i<dl;i++)
         wydruk[poziom][srodek-dl/2+i]=s[i];
       if (++poziom<IL_POZ){
         drukujwew(w->left,l,srodek,poziom) ;
         drukujwew(w->right,srodek+1,p,poziom) ;
       }
       else {
         drukujost(w->left,l,srodek,poziom) ;
         drukujost(w->right,srodek+1,p,poziom) ;
       }
}

void drukuj(Wskwezla w){
  int j,i;
  for (i=0;i<=IL_POZ;i++)
    for (j=0;j<SZER_EKR;j++)
      wydruk[i][j] = ' ';
  drukujwew(w,0,SZER_EKR,0);
  for (i=0;i<=IL_POZ;i++){
      for (j=0;j<SZER_EKR;j++)
        putchar(wydruk[i][j]);
      printf("\n");
  }
}

void drukujKrawedz(FILE *plikwy, Wskwezla r, int z, Wskwezla syn, int zs){
// wezel r o numerze z jest juz wydrukowany
// teraz drukujemy jego syna "syn" o numerze zs oraz krawedz miedzy nimi
  if (syn == NULL){
    fprintf(plikwy,"%d [shape=circle, style=invisible, label=\"",zs);
    fprintf(plikwy,"%d ",0);
    fprintf(plikwy,"\"]\n");
    fprintf(plikwy,"%d -- %d [style=invis];\n ",z,zs);
  } else{
    if (syn->kolor == RED)
      fprintf(plikwy,"%d [shape=circle, color=red, label=\"",zs);
    else
      fprintf(plikwy,"%d [shape=circle, color=black, label=\"",zs);
    fprintf(plikwy,"%d ",syn->klucz);
    fprintf(plikwy,"\"]\n");
    fprintf(plikwy,"%d -- %d ;\n",z,zs);
  }  
}

int rekDrukujDot(Wskwezla r, int z, FILE *plikwy){
  // drukuje drzewo o korzeniu r 
  // z  - numer wezla r
  // zwraca najwiekszy numer wezla w poddrzewie, ktorego jest korzeniem
  // zakladamy, ze korzen r jest juz wydrukowany
  int nz,i;
  if (r == NULL) return z;
  else{
    drukujKrawedz(plikwy,r,z,r->left,z+1);
    nz=rekDrukujDot(r->left,z+1,plikwy);
    drukujKrawedz(plikwy,r,z,r->right,nz+1);
    nz=rekDrukujDot(r->right,nz+1,plikwy);
    return nz;
  }
}

void drukujDot(Wskwezla r){
  // generuje w plikach drzewo0.gv, dzrewo1.gv, ... 
  // opisy drzew o korzeniu r pzeznaczone do wydrukowania przez program dot
  // zlecenie "dot -Tpdf -O drzewo1.gv" utworzy plik "drzewo1.gv.pdf" 
  static int gdzie=0;
  char numer[10];
  char nazwap[20]="drzewo";
  FILE *plikwy;
  snprintf(numer,9,"%d",gdzie);
  strcat(nazwap,numer);
  strcat(nazwap,".gv");
  plikwy=fopen(nazwap,"w");
  gdzie++;
  fprintf(plikwy, "graph drzewo{\n");
  fprintf(plikwy, "size = \"2,20\"");
  if (r!=NULL){
    if (r->kolor == RED)
      fprintf(plikwy,"%d [shape=circle, color=red, label=\"",0);
    else
      fprintf(plikwy,"%d [shape=circle, color=black, label=\"",0);
    fprintf(plikwy,"%d ",r->klucz);
    fprintf(plikwy,"\"]\n");
    rekDrukujDot(r,0,plikwy);
  }
  fprintf(plikwy, "}\n");
  fclose(plikwy);
  printf("wydrukowane %s\n",nazwap);
}

/*-------------------------wklejony kod----------------------------------*/

void wlasnosci(Wskwezla *T, int klucz);

void tree_insert(Wskwezla *T, int z) {

  int flaga;
  
  if(*T==NULL) {  //Sprawdzam na co wskazuje wskaznik (Jesli na NULL, to nie ma jeszcze zadnego el.)
    *T = (Wskwezla)malloc(sizeof(Twezla)); //Przydzielam pamiec, bo wskazuje na NULL
    (**T).p = NULL;  //Jest to pierwszy wezel, wiec nie ma rodzica
    (**T).klucz = z;    //Wprowazdam klucz
    (**T).ilosc = 1;    //Ilosc jeden, bo to pierwszy element
    (**T).left = NULL; //Jest to pierwszy element, wiec nie ma zadnych synow.
    (**T).right = NULL;
    (**T).kolor = BLACK;
  }
  else {
    Wskwezla x = *T;            
    Wskwezla y = NULL;
    while(x != NULL) {
      y = x;
      flaga = 0;
      if (z == (*x).klucz) {    //Sprawdza kazdy wezel czy juz jest taki klucz, jesli tak to zwieksza pole ilosc
	(*x).ilosc += 1;     //i wychodzi z funkcji, a jak nie to ustawia wartosc flagi
	return;             //0 jesli ma zapisac nowy wezel po lewej stronie; 1 jesli po prawej
      }
      if (z < (*x).klucz) {
	x = (*x).left;
	flaga = 0;
      }
      else {
	x = (*x).right;
	flaga = 1;
      }
    }
    Wskwezla nowy_element = (Wskwezla)malloc(sizeof(Twezla));
    (*nowy_element).p = y;
    (*nowy_element).klucz = z;
    (*nowy_element).ilosc = 1;
    (*nowy_element).left = NULL;
    (*nowy_element).right = NULL;
    (*nowy_element).kolor = RED;
    if (flaga == 0) (*y).left = nowy_element;   //y jest tutaj ostatnim sprawdzanym wezlem. 
    else (*y).right = nowy_element;            //nowy klucz byl porownywany ostatni raz z kluczem wezla y.

    wlasnosci(T, (*nowy_element).klucz);
  }
}

Wskwezla tree_search(Wskwezla T, int x) { //szuka klucza po wezlach i zwraca wskaznik na wezel

  if (T == NULL) {
    printf("Nie zapisano jeszcze zadnego klucza.");
    return NULL;
  }
  else {
    Wskwezla temp = T;
    while(temp != NULL && x != (*temp).klucz) {
      if (x < (*temp).klucz)
	temp = (*temp).left;
      else
	temp = (*temp).right;
    }
    return temp;
  }
}

Wskwezla tree_min(Wskwezla T) {
  
  Wskwezla temp = T;
  while((*temp).left != NULL)
    temp = (*temp).left;
  return temp;
}
void drukuj_inorder(Wskwezla T) {

  if(T == NULL) {
    printf("Drzewo jest puste!\n");
    return;
  }
  
  Wskwezla temp = T;
  
  if((*temp).left != NULL) {       //Sprawdza kolejno lewych synow i jesli lewy syn wystepuje, to znowu wywoluje dla
    printf("\n");                 //niego funkcje drukuj_inorder
    drukuj_inorder((*temp).left);
  }
  
  printf("%d(%d) ", (*temp).klucz, (*temp).ilosc);   //Wyswietla wartosc z rodzica.
  
  if((*temp).right != NULL) {         //jw. tylko ze prawy syn
    printf("\n");
    drukuj_inorder((*temp).right);
  }
}

void tree_delete(Wskwezla *T, int z) {

  int temp_key;
  
  if(*T == NULL) {
    printf("Drzewo jest puste.\n");
    return;
  }
  Wskwezla temp = tree_search(*T, z);        //najpierw wyszukuje wezel, w ktorym wystepuje dany klucz.
  Wskwezla y;
  Wskwezla y2;
  
  if(temp == NULL) {
    printf("Nie ma takiego klucza w drzewie.\n");
    return;
  }
  
  if((*temp).ilosc > 1) {                  //jesli w znalezionym wezle ilosc jest wieksza od 1, to zmniejsza te ilosc
    (*temp).ilosc -= 1;                    //o 1 i wychodzi z funkcji (niefizyczne usuniecie).
    return;
  }
  
  if((*temp).left == NULL && (*temp).right == NULL){   //warunek dla wezla nie posiadajacego synow.

    if((*temp).p == NULL) {            //jesli wezel ten jest dodatkowo pierwszym wezlem, to sie wykonuje ten kod.
      free(temp);
      *T = NULL;
      return;
    }
    
    if(temp == (*(*temp).p).left) {    //a jesli nie, to sprawdza czy dany wezel jest lewym/prawym synem swojego
      (*(*temp).p).left = NULL;          //rodzica, zeby w rodzicu zlikwidowac odpowiedniego syna.
      free(temp);
    }
    else {
      (*(*temp).p).right = NULL;
      free(temp);
    }
    return;
  }
  
  if((*temp).left != NULL && (*temp).right != NULL) { //warunek dla wezla, ktory posiada dwoch synow.
    y2 = tree_min((*temp).right);                   //przypisuje do zmiennej wskaznikowej y2 wezel najbardziej w lewo
    temp_key = (*y2).klucz;                          //od prawego syna wezla, ktory chcemy usunac.
    tree_delete(T, (*y2).klucz);          //zapisuje w zmiennej tymczasowej wartosc klucza z y2.
    (*temp).klucz = temp_key;          //wywoluje funkcje usun dla wezla y2.
    //(*temp).parent = NULL;          //przypisuje do pierwotnie usuwanego klucza klucz z y2 i wychodzi z funkcji.
    return;
  }
  if((*temp).left != NULL) {                 //warunek dla wezla, ktory posiada tylko lewego syna.
    (*(*temp).left).p = (*temp).p;  //Ustawia w synie rodzica na rodzica wezla ktorego usuwamy.
    y = (*temp).left;                     //Zapisuje lewego syna do zmiennej tymczasowej.
    if ((*temp).p == NULL) {       //Sprawdzamy czy wezel, ktory usuwamy znajduje sie na szczycie drzewa.
      *T = (*temp).left;             //Jesli tak, to swojego jedynego lewego syna czyni poczatkiem drzewa(szczytem)
      return;
    }
    if (temp == (*(*temp).p).left) {  //Sprawdza, ktorym synem jest usuwany wezel u swojego rodzica (czy lewym?)
      (*(*temp).p).left = y;         //Jesli tak, to w rodzicu usuwanego wezla lewego syna ustawia sie na jedynego
      free(temp);                        //lewego syna wezla usuwanego.
      return;
    }
    else {
      (*(*temp).p).right = y;       //Podobnie jw. tylko ze prawy syn.
      free(temp);
      return;
    }
  }
  if((*temp).right != NULL) {           //warunek dla wezla, ktory posiada tylko prawego syna (analogicznie jw.)
    (*(*temp).right).p = (*temp).p;
    y = (*temp).right;
    if ((*temp).p == NULL) {
      *T = (*temp).right;
      return;
    }
    if (temp == (*(*temp).p).right) {
      (*(*temp).p).right = y;
      free(temp);
      return;
    }
    else {
      (*(*temp).p).left = y;
      free(temp);
      return;
    }
  }
}

void rotate_right(Wskwezla *T, int x) {
  
  if(*T == NULL) {
    printf("Drzewo jest puste.\n");
    return;
  }

  Wskwezla b;                               //B lewym synem wezla C.
  Wskwezla rodzicC;
  Wskwezla c = tree_search(*T, x);           //C jest wezlem wokol ktorego f. dokonuje rotacji.

  if((*c).left == NULL) return;         //Jesli lewy syn C nie istnieje, to nie wykonuje rotacji.
  b = (*c).left;
  if ((*c).p != NULL) {               //Sprawdza czy C jest korzeniem. Jesli nie jest to
    rodzicC = (*c).p;                 //przypisuje do rodzicaC rodzica C.
    (*b).p = rodzicC;
    if ((*rodzicC).left == c)
      (*rodzicC).left = b;
    else
      (*rodzicC).right = b;
  }
  else {                            //Jesli C jest korzeniem, to rodzica w lewym synie (B) ustawia na
    (*b).p = NULL;                  //NULL i oznacza ten wezel korzeniem. (rotacja w prawo).
    *T = b;
  }
  (*c).p = b;                      //Rodzica C ustawia na jego wczesniejszego lewego syna (B).
  (*c).left = (*b).right;          //W C ustawia lewego syna na prawego syna B.
  (*b).right = c;                  //W B ustawia prawego syna na C (nastapila rotacja).
}

void rotate_left(Wskwezla *T, int x) {

  if(*T == NULL) {
    printf("Drzewo jest puste.\n");
    return;
  }

  Wskwezla c;
  Wskwezla rodzicB;
  Wskwezla b = tree_search(*T, x);
  
  if((*b).right == NULL) return;
  c = (*b).right;
  rodzicB = (*b).p;
  if (rodzicB != NULL) {
    (*c).p = rodzicB;
    if((*rodzicB).left == b)
      (*rodzicB).left = c;
    else
      (*rodzicB).right = c;
  }
  else {
    (*c).p = NULL;
    *T = c;
  }
  (*b).p = c;
  (*b).right = (*c).left;
  (*c).left = b;
}

void wlasnosci(Wskwezla *T, int klucz) {

  Wskwezla x, o, oo;   //o - ojciec, oo - ojciec ojca
  x = tree_search(*T, klucz);
  if((*x).p == NULL || (*(*x).p).kolor == BLACK) return;   //Najpierw sprawdza czy ojciec x istnieje badz jest czarny
  else {
    o = (*x).p;
    oo = (*o).p;
    if((*oo).left == o) {    //ojciec jest lewym synem swojego ojca.
      if((*oo).right != NULL && (*(*oo).right).kolor == RED) { //1-szy warunek (brat ojca czerwony)
	(*(*oo).right).kolor = BLACK;
	if((*oo).p != NULL) (*oo).kolor = RED;  //Jesli oo nie jest korzeniem, to maluje na czerwono.
	(*o).kolor = BLACK;                    //Ojca x maluje na czarno.
	wlasnosci(T, (*oo).klucz);
	return;
      }
      if((*oo).right == NULL || (*(*oo).right).kolor == BLACK) { //2-gi i 3-ci przypadek
	if((*o).right == x) {            //Rozwiazuje drugi przypadek (przejscie do 3.)
	  rotate_left(T, (*o).klucz);
	  x = o;
	}
	rotate_right(T, (*(*(*x).p).p).klucz);  //Rozwiazuje trzeci przypadek
	(*(*x).p).kolor = BLACK;
	(*(*(*x).p).right).kolor = RED;
      }
    }
    else {                    //ojciec jest prawym synem swojego ojca
      if((*oo).left != NULL && (*(*oo).left).kolor == RED) {
	(*(*oo).left).kolor = BLACK;
	if((*oo).p != NULL) (*oo).kolor = RED;
	(*o).kolor = BLACK;
	wlasnosci(T, (*oo).klucz);
	return;
      }
      if ((*oo).left == NULL || (*(*oo).left).kolor == BLACK) {
	if((*o).left == x) {
	  rotate_right(T, (*o).klucz);
	  x = o;
	}
	rotate_left(T, (*(*(*x).p).p).klucz);
	(*(*x).p).kolor = BLACK;
	(*(*(*x).p).left).kolor = RED;
      }
    }
  }
}

int main() {
  Wskwezla korzen;
  korzen = NULL;

  tree_insert(&korzen, 15);
  tree_insert(&korzen, 8);
  tree_insert(&korzen, 19);
  drukuj(korzen);
  tree_insert(&korzen, 7);        //1-szy przypadek
  drukuj(korzen);
  tree_insert(&korzen, 5);        //3-ci przypadek
  drukuj(korzen);
  tree_insert(&korzen, 17);       
  drukuj(korzen);
  tree_insert(&korzen, 18);       //2-gi przypadek
  drukuj(korzen);
 
}
