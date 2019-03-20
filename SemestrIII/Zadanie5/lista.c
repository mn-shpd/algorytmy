#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAKS 10      //maksymalna ilosc liter w slowie

struct wezel {
  char key[MAKS];
  struct wezel *next, *prev;
};

void wstaw(struct wezel **head, char slowo[]) {  //wskaznik na wskaznik na strukture //wstawia na poczatek listy
  
  if (*head==NULL) { //Sprawdzam na co wskazuje wskaznik (Jesli na NULL, to nie ma jeszcze zadnego el.)
    *head = (struct wezel *)malloc(sizeof(struct wezel)); //Przydzielam pamiec, bo wskazuje na NULL;
    strcpy((**head).key, slowo); //Wprowadzam wartosc do pola struktury
    (**head).prev = NULL; //Jest to pierwszy element dlatego nie wskazuje na poprzedni ani nastepny
    (**head).next = NULL; //jw.
  }
  else {
    struct wezel *nowy_element = (struct wezel *)malloc(sizeof(struct wezel)); //Przydzielenie pamieci nowemu el.
    strcpy((*nowy_element).key, slowo); //Wprowadza slowo do nowego el. listy.
    (*nowy_element).prev = NULL; //W nowym elemencie prev ma wskazywac na NULL (bo dodaje na poczatek listy)
    (*nowy_element).next = *head; //W nowym elemencie next ma wskazywac na stary korzen
    (**head).prev = nowy_element; //W starym korzeniu prev ma wskazywac na nowy element.
    *head = nowy_element; //Korzeniem teraz jest nowy element.
  }
}

void drukuj(struct wezel *head) {
  if(head==NULL) {                 //Jesli wskaznik wskazuje na NULL, to lista jest pusta.
    printf("Lista jest pusta\n");  
  }
  else {
    struct wezel *temp = head;     
    do {
      printf("%s", (*temp).key);
      printf("\n");
      temp = (*temp).next;
    } while (temp != NULL);
  }    
  
}

struct wezel *szukaj(char slowo[], struct wezel *head) {
  if(head==NULL) {
    printf("Lista jest pusta.\n");
    return NULL;
  }
  else {
    struct wezel *temp = head;
    do {
      if (strcmp((*temp).key, slowo) == 0) { //funkcja strcmp zwraca 0 gdy stringi sa takie same.
	return temp;
      }
      temp = (*temp).next;
    } while (temp != NULL);
    //printf("Nie ma takiego slowa w liscie.\n");
    return NULL;
  }
}

void usun(char slowo[], struct wezel **head) {

  int flag = 0;    //flaga do warunkow if (jesli wykona sie jeden, to kolejne maja sie nie wykonywac).
  struct wezel *temp2;
  
  if(*head==NULL) {
    printf("Lista jest pusta.\n");
  }
  else {
    struct wezel *temp = *head;  //przekazuje do funkcji adres do wskaznika, wiec trzeba go wyluskac "*head"
    do {
      if (strcmp((*temp).key, slowo) == 0) { //funkcja strcmp zwraca 0 gdy stringi sa takie same.
	if ((*temp).prev == NULL && (*temp).next == NULL) { //gdy jest tylko jeden element w liscie
	  free(temp);
	  *head = NULL;
	  flag = 1;
	}
	if ((*temp).next == NULL && !flag) { //gdy usuwany element jest na koncu
	  temp2 = (*temp).prev;           //ustawia w przedostatnim elemencie nastepnik na NULL (usunieto go)
	  (*temp2).next == NULL;
	  free(temp);
	  flag = 1;
	}
	if ((*temp).prev == NULL && !flag) { //gdy usuwany element jest na poczatku i w liscie jest wiecej elem.
	  *head = (*temp).next;        //ustawia korzen na nastepny element po tym usunietym (na drugi).
	  free(temp);
	  flag = 1;
	}
	if ((*temp).prev != NULL && (*temp).next != NULL && !flag) { //gdyy usuwamy element ze srodka
	  temp2 = (*temp).prev;               //Ustawia wskaznik nastepnego elementu w elemencie wystepujacym przed
	  (*temp2).next = (*temp).next;      // tym usunietym na element wystepujacy po usunietym elemencie
	  free(temp);
	  flag = 1;
	}
      }
      temp = (*temp).next;
    } while (!flag);

    if (!flag)             //Jezeli flaga ani razu sie nie "zapali" to znaczy, ze nic nie usunieto.
      printf("Nie ma takiego slowa w liscie.\n"); 
    else
      printf("Usunieto slowo '%s' z listy.\n", slowo);
  }
}

void kasuj (struct wezel **head) {
  
  struct wezel *temp = (**head).next;  //kopiuje wskaznik na drugi element listy do wskaznika tymczasowego.
  
  do {
    free(*head);           //Zwalnia pamiec 
    *head = temp;         //Przepisuje wskaznik na kolejny element listy do wskaznika head
    temp = (**head).next;  //Do wskaznika tymczasowego przypisuje wskaznik na kolejny element.
  } while (temp != NULL);

  *head = NULL;         //Przypisuje do korzenia NULL, co wskazuje na pusta liste.
}

struct wezel *bezpowtorzen(struct wezel *head) {

  if (head==NULL) return NULL;  //Jesli lista jest pusta, to zwraca NULL
  
  char temp_key[MAKS];
  struct wezel *nowalista = NULL;
  nowalista = (struct wezel *)malloc(sizeof(struct wezel));
  struct wezel *temp;
  struct wezel *temp2;
  struct wezel *nowy_element;

  strcpy((*nowalista).key, (*head).key);    //Kopiuje pierwszy element listy.
  (*nowalista).prev = NULL;
  (*nowalista).next = NULL;
  temp = head;          //iteruje dla klucza.
  temp2 = nowalista;
  
  do {
    temp = (*temp).next;                   //Petla sprawdza kolejny element w liscie i jesli znajduje sie on juz
    strcpy(temp_key, (*temp).key);         //w nowej liscie to go nie dodaje. (wykorzystuje funkcje szukaj).
    if (szukaj(temp_key, nowalista) == NULL) {
      nowy_element = (struct wezel *)malloc(sizeof(struct wezel));
      (*temp2).next = nowy_element;
      strcpy((*nowy_element).key, temp_key);
      (*nowy_element).prev = temp2;
      (*nowy_element).next = NULL;
      temp2 = nowy_element;
    }
  } while ((*temp).next != NULL);

  return nowalista;
}

struct wezel *scal (struct wezel *l1, struct wezel *l2) {

  if (l1 == NULL) return l2;   //Jesli pierwsza lista jest pusta, to zwraca wskaznik na poczatek drugiej listy.
  if (l2 == NULL) return l1;   //jw. tylko na odwrot.
  if (l1 == NULL && l2 == NULL) return NULL; //Jesli obie puste, to zwraca NULL
  
  struct wezel *temp = l1;        //Przypisuje do wskaznika tymczasowego wskaznik na pierwsza liste.

  while ((*temp).next != NULL) {   //Iteruje po elementach pierwszej listy az dojdzie do ostatniego elementu
    temp = (*temp).next;           //tak zeby wskaznik temp wskazywal na ostatni element
  }

  (*temp).next = l2;            //Ustawia wskaznik next w ostatnim el. pierwszej listy na pierwszy el. drugiej.
  (*l2).prev = temp;          //W pierwszym elemencie drugiej listy ustawia prev na ostatni element 1szej listy.
  
  return l1;
  
}

int main() {

  struct wezel *head;  //poczatek listy (wskaznik na pierwszy element)
  struct wezel *nowalista;
  struct wezel *polaczenielist;
  
  //head = (struct wezel *)malloc(sizeof(struct wezel));
  head = NULL;

  drukuj(head);
  wstaw(&head, "aaa");
  wstaw(&head, "aaa"); //Podaje adres wskaznika head. Trzeba przekazac adres wskaznika, bo inaczej
  wstaw(&head, "bbb"); //wszystkie operacje funkcji wstaw dokonalaby sie tylko w obrebie funkcji
  wstaw(&head, "bbb");
  wstaw(&head, "ccc");
  wstaw(&head, "ccc");
  drukuj(head);
  usun("aaa", &head);
  //usun("bbb", &head);
  drukuj(head);
  //kasuj(&head);
  // drukuj(head);

  nowalista = bezpowtorzen(head);
  printf("!!!!!!!!\n");
  drukuj(nowalista);

  usun("bbb", &nowalista);
  drukuj(nowalista);

  polaczenielist = scal(head, nowalista);

  printf("!!!!!!!!\n");
  drukuj(polaczenielist);
  
  //struct wezel *tempek = szukaj("bbb", head);  //Sprawdzenie funkcji szukaj
  //printf("\n\n%s\n", (*tempek).key);

}
  
