#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0
/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////
void utworz_MACIERZ(int n, int ***M){
// alokuj� pami�� na tablic� rozmiaru nxn
// i wpisuje losowe warto�ci 0/1 w macierzy
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=rand()% 2;
            }
    }
}
/////////////////////////////////////////////
void utworz_MACIERZ_x(int n, int ***M, int x){
// alokuj� pami�� na tablic� rozmiaru nxn
// i wpisuje do macierzy wsz�dzie warto�ci x
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=x;
            }
    }
}
/////////////////////////////////////////////
void wypisz_MACIERZ(int n, int **M){
// wypisuje warto�ci macierzy
int i,j;

for(i=0;i<n;i++){
    for(j=0;j<n;j++)
        printf("%d",M[i][j]);
    printf("\n");
    }
}
/////////////////////////////////////////////
void zwolnij_MACIERZ(int n, int **M){
// zwalania pami�� zarezerwowan� dla macierzy
int i;
    for(i=0;i<n;i++)
    {
    free(M[i]);
    }
    free(M);
}
/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M){
int x1,y1,x2,y2,x,y;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=n-1;x2>x1-1;x2--)
            for(y2=n-1;y2>y1-1;y2--){
                local_max=0;
                for(x=x1;x<x2+1;x++)
                    for(y=y1;y<y2+1;y++)
                        local_max+=M[x][y];
                if ((local_max==(x2-x1+1)*(y2-y1+1)) && (local_max>max)) max=local_max;
                }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M,int x1, int y1, int x2, int y2){
if ((x2==x1)&&(y2==y1)) return M[x1][y1];
    else if ((x2-x1)>(y2-y1))
        return REKURENCJA(M,x1,y1,(int)(x1+x2)/2,y2)*REKURENCJA(M,(int)(x1+x2+1)/2,y1,x2,y2);
            else return REKURENCJA(M,x1,y1,x2,(int)(y1+y2)/2)*REKURENCJA(M,x1,(int)(y1+y2+1)/2,x2,y2);
}
/////////////////////////////////////////////
int ALGO_REKURENCYJNY(int n, int **M){
int x1,y1,x2,y2;
int max=0;
int local_max;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=x1;x2<n;x2++)
            for(y2=y1;y2<n;y2++){
                local_max=REKURENCJA(M,x1,y1,x2,y2)*(x2-x1+1)*(y2-y1+1);
                if (local_max>max) max=local_max;
            }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M){
int x1,x2,y;
int max=0;
int iloczyn;
int **MM;

utworz_MACIERZ_x(n,&MM,0);

for(y=0;y<n;y++)
    for(x1=0;x1<n;x1++){
        iloczyn=1;
        for(x2=x1;x2<n;x2++){
            iloczyn*=M[x2][y];
            MM[x1][x2]=iloczyn*(x2-x1+1+MM[x1][x2]);
            if (MM[x1][x2]>max) max=MM[x1][x2];
        }
    }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M){
int x1,y1,x2,y2,ymax;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++){
        local_max=0;
        x2=x1;
        ymax=n-1;
        while ((x2<n)&&(M[x2][y1]==1)){
            y2=y1;
            while((y2<ymax+1)&&(M[x2][y2]==1)){
                y2++;
            }
            ymax=y2-1;
            local_max=(x2-x1+1)*(ymax-y1+1);
            if (local_max>max) max=local_max;
            x2++;
        }
    }
return max;
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
int main() {
  
  int **Macierz;
  int n, wynik;
  srand(time(NULL));
  long double Tn, Fn;
  struct timespec tp0, tp1;

  for(n=5; n<=100; n=n+5) {
    
    utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    //wypisz_MACIERZ(n,Macierz);
   
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
    wynik = ALGO_NAIWNY(n,Macierz);
    //wynik = ALGO_REKURENCYJNY(n,Macierz);
    //wynik = ALGO_DYNAMICZNY(n,Macierz);
    //wynik = ALGO_CZULY(n,Macierz);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

    // zgadywana funkcja czasu
    //Fn=(double)n*n*n*n*n*n; //Algorytm naiwny
    //Fn=(double)n*n*n*n*n*n*log(n); //Algorytm rekurencyjny
    //Fn=(double)n*n*n+n*n; //Algorytm dynamiczny
    Fn=(double)5*n*n; //Algorytm czuly dla 0-1 i 0 macierzy
    //Fn=(double)n*n*n*n; //Algorytm czuly dla 1 macierzy
    
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
 
    printf("W = %d \tn: %d \tCzas: %3.10Lf \tWspolczynnik: %3.5Lf\n", wynik, n, Tn, Fn/Tn);
 
    zwolnij_MACIERZ(n,Macierz);
  }
  return 1;
}
