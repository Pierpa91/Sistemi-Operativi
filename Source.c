#include <stdio.h>                                                              //Informazioni:
#include <stdlib.h>                                                             //bisogna adattarlo a linux nel senso sostituire i system pause
//#include <pthread.h>     //Linux Only                                         //ecc con i loro corrispettivi... 
//#define NUM_THREADS 2                                                         //
int main ()                                                                     // _sleep diventa usleep
{                                                                               // system ("cls") ha un corrispettivo ma non so qual'è
    int i=0;
    int vett_nord=1;
    int vett_sud=1;
    int cont=0;
    
   
    
    while(vett_nord != 0 || vett_sud !=0)    //equivale a while true..
    {
        int ponte=0;     //0=vuoto, 1=Nord, 2=Sud
        if (rand() % 10000 % 3 == 0)      //se un numero casuale da 0 a 10000 è divisibile    
        {                                 //per 3 entra nord altrimenti entra sud
            entra_nord();
            esci();
        }else
        {
            entra_sud();
            esci();
        }
    }
    printf ("\nLe vetture da nord e sud sono terminate");
    
    
    entra_nord()         //funzione che  aggiunge macchine in coda alle macchine da nord
    {
        if (vett_nord !=0)
        {
            vett_nord++;
            wait (coda);
        }
    }
    
    entra_sud()         //funzione che aggiunge macchine in coda alle macchine da sud
    {
        if (vett_sud !=0)
        {
            vett_sud++;
            wait (coda);        
        }
    }
    
    esci()  
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

