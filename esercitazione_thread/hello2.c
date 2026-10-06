#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

typedef struct{

    int valore;
    
}parametri;

void* PrintHello(void * p){

    parametri * x = p;

    printf("\n%d : Hello World!\n",x->valore);
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){

    pthread_t threads[NUM_THREADS];

    int rc;
    for(int i = 0; i< NUM_THREADS; i++){

        parametri * p =(parametri*) malloc(sizeof(parametri));

        p->valore = i;
        
        rc = pthread_create(&threads[i], NULL, PrintHello, p);
        if(rc != 0){
            printf("ERROR");
            exit(-1);

        }

    }

    //metto il padre in attesa della terminazione dei diversi thread
    for(int i = 0; i< NUM_THREADS; i++){

        pthread_join(threads[i], NULL);

    }
    printf("Fine dei thread\n");

    pthread_exit(NULL); //terminazione del processo padre
}