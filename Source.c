#include <stdio.h>                                                              //Informazioni:
#include <stdlib.h>                                                             //bisogna adattarlo a linux nel senso sostituire i system pause
//#include <pthread.h>     //Linux Only                                         //ecc con i loro corrispettivi... 
//#define NUM_THREADS 2                                                         //
int main ()                                                                     // _sleep diventa usleep
{                                                                               // system ("cls") ha un corrispettivo ma non so qual'è
    char dir;               //Direzione assume valori n=nord, s=sud
    char scelta;            //variabile char per aggiungere una vettura
    int i=0;
    int vett_nord=0;
    int vett_sud=0;
    int cont=0;
    
    //************Funzione aggiungi macchine********************************/   /*Creare al suo posto un qualcosa che random aggiunga*/
    while(cont!=2)                                                              /*Macchine da nord o sud a discrezione del computer*/
    {
        printf ("\n\nVuoi aggiungere una macchina? [s/n]  ");
        scanf ("%s", &scelta);        
        if (scelta== 's' || scelta== 'S')
        {
            printf ("\nAggiungeremo una nuova vettura\n");
            printf ("La nuova vettura arrivera' da nord o sud? [s/n]  \n");
            scanf("%s", &scelta);
            if (scelta== 's' || scelta== 'S')
            {
                printf("Aggiungeremo una vettura da sud\n");
                vett_sud++;
                printf("Le vetture da sud ora sono: %d",vett_sud);
                system("pause");
                system("cls");
            }else
            {
                printf("Aggiungeremo una vettura da nord\n");
                vett_nord++;
                printf("Le vetture da nord ora sono: %d",vett_nord);
                system("pause");
                system("cls");
            }
                
        }else
        {
             system("cls");
             printf("Le vetture da nord totali sono: %d\n",vett_nord);
             printf("Le vetture da sud totali sono: %d\n",vett_sud);
             system("pause");
             system("cls");
             printf("\n\nVerra' chiusa la procedura di inserimento\n");
             printf("E acceso il monitor\n\n");
             cont=2;
        }  
    }
    
    /*****Richiamo Le macchine****************/
    int ponte=0;     //0=vuoto, 1=Nord, 2=Sud
    entra();
    esci();
    
    
    
    
    entra()
    {
        while (vett_nord != 0 || vett_sud !=0)
        {
              if (ponte == 0)
              {
                  if (vett_nord > 0)          //prima iterazione
                  {
                      ponte=1;
                      printf("\nvetture da nord sul ponte\n");
                      pthread_mutex_lock(&mutex); //parte il mutex
                      vett_nord--;
                  }
              }
              if (ponte == 1)                //tutte le altre iterazioni
              {
                  if (vett_nord > 0)
                  {
                      ponte=1;
                      printf("\nvetture da nord sul ponte\n");
                      pthread_mutex_lock(&mutex); //parte il mutex
                      vett_nord--;
                      if (vett_nord == 1)    //gestisco l'ultima vettura da nord sul ponte
                      {
                          ponte=0;           //setto il ponte come libero
                          printf("\nUltima vettura da nord sul ponte\n");
                          pthread_mutex_lock(&mutex); //parte il mutex
                          vett_nord--;
                          pthread_cond_wait(&empty, &mutex); //terminato il passaggio le macchine da nord sono in wait
                          pthread_cond_signal(&empty);
                          pthread_mutex_unlock(&mutex); //rilascio la mutua esclusione
                      }
                  }
              }else
              {
                   if (vett_sud > 0)
                   {
                       ponte = 2;
                       printf("\nVetture da sud sul ponte\n");
                       pthread_mutex_lock(&mutex);     //parte il mutex
                       vett_sud--;
                       if (vett_sud == 1)    //gestisco l'ultima vettura da sud sul ponte
                       {
                           ponte = 0     //imposto il ponte come libero
                           printf("\nUltima vettura da sud sul ponte\n");
                           pthread_mutex_lock(&mutex); //parte il mutex
                           vett_sud--;
                           pthread_cond_wait(&empty, &mutex); //terminato il passaggio le macchine da sud sono in wait
                           pthread_cond_signal(&full);   //sveglio le macchine da nord
                           pthread_mutex_unlock(&mutex); //rilascio il mutex
                       }
                   }
              }                       
        }
        printf ("\nLe vetture da nord e sud sono terminate");
    }
    
}
