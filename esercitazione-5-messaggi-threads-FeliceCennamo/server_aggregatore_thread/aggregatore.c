#include "sensore.h"
#include "aggregatore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct{
    MonitorLS* m;
    int coda;
}param;

void aggregatore(int id_coda_sensore, int id_code_collettori[3]) {

    printf("Avvio processo aggregatore...\n");

    pthread_t threads[4];

    /* TBD: Completare questa funzione, avviando un thread scrittore e 3 thread lettori *
     *
     * IMPORTANTE: Occorre passare ai thread sia il puntatore ad un oggetto-monitor,
     *             sia l'identificativo della coda di messaggi su cui ricevere/inviare.
     *             Si definisca una struct per il passaggio dei parametri.
     */
    MonitorLS* m = (MonitorLS*) malloc(sizeof(MonitorLS));
    pthread_mutex_init(&m->mutex,NULL);
    pthread_cond_init(&m->CV_LETT,NULL);
    pthread_cond_init(&m->CV_SCRITT,NULL);

    m->busy = 0;
    m->n_lett = 0;
    m->n_scritt = 0;

    param * p = (param*)malloc(sizeof(param));
    p->coda = id_coda_sensore;
    p->m = m;

    pthread_create(&threads[3], NULL, thread_scrittore,(void*)p);

    for(int i = 0; i<3; i++){
        param* q = malloc(sizeof(param));
        q->coda = id_code_collettori[i];
        q->m = m;
        pthread_create(&threads[i], NULL, thread_lettore, (void*)q);

    }    

    for(int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    free(m);
    return;

}


void * thread_lettore(void * x) {

    param * p = (param*) x;
    int ret;

    for(int i=0; i<10; i++) {

        int valore;

        sleep(1);

        /* TBD: Chiamare il metodo "lettura()" del monitor */
        lettura(p->m,&valore);

        printf("Aggregatore: Invio valore=%d\n", valore);

        /* TBD: Inviare il messaggio */
        messaggio msg;
        msg.valore = valore;
        msg.tipo = 1;

        ret = msgsnd(p->coda, &msg, sizeof(messaggio) - sizeof(long), 0);

        if(ret <0){
            perror("errore send lettore");
            exit(1);
        }
    }


    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    param* p = (param*) x;
    int ret;

    for(int i=0; i<10; i++) {

        printf("Aggregatore: In attesa di messaggi...\n");

        /* TBD: Ricevere il messaggio */
        messaggio msg;
        ret = msgrcv(p->coda, &msg, sizeof(messaggio) - sizeof(long), 0 ,0);

        if(ret < 0){
            perror("errore receive scrittore");
            exit(1);
        }

        int valore = msg.valore;

        printf("Aggregatore: Ricevuto valore=%d\n", valore);

        /* TBD: Chiamare il metodo "scrittura()" del monitor */
        scrittura(p->m, valore);
    }

    pthread_exit(NULL);
}

void lettura(MonitorLS * m, int * valore) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
    while(m->busy == 0){      
        pthread_cond_wait(&m->CV_LETT, &m->mutex);       
    }
    m->n_lett++;

    *valore = m->variabile;

    if(m->n_lett == 3){
        m->busy = 0;
        m->n_lett =0;
        pthread_cond_signal(&m->CV_SCRITT);
    }
    pthread_mutex_unlock(&m->mutex);

    printf("Aggregatore: Lettura valore=%d\n", *valore);

}

void scrittura(MonitorLS * m, int valore) {
    
    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
    while(m->busy == 1 ||m->n_lett != 0){
    
        pthread_cond_wait(&m->CV_SCRITT, &m->mutex);
      
    }
    

    printf("Aggregatore: Scrittura valore=%d\n", valore);

    m->busy = 1;
    m->variabile = valore;

    pthread_cond_broadcast(&m->CV_LETT);

    pthread_mutex_unlock(&m->mutex);
}