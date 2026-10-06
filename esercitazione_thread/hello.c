#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5


void* PrintHello(void * p){

    //qua devo necessariamente fare un cast ad intero per p, perchè
    //C non sa come trattare il tipo void *
    printf("\n%d : Hello World!\n", (int)p);
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){

    pthread_t threads[NUM_THREADS];

    int rc;
    for(int i = 0; i< NUM_THREADS; i++){

    //sto creando un thread per ogni volta che voglio eseguire la funzione PrintHello 
    //printHello deve essere passata senza le () !!! 
    //il cast a void* viene effettuato per generalizzare il tipo di dati che si vogliono 
    //passare in modo da garantire estrema versatilità alla funzione create
        rc = pthread_create(&threads[i], NULL, PrintHello, (void * )i);
        if(rc != 0){
            printf("ERROR");
            exit(-1);

        }

    }
    pthread_exit(NULL);
}