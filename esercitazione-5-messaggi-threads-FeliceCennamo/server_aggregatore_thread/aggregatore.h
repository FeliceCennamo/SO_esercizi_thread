#ifndef _AGGREGATORE_H_
#define _AGGREGATORE_H_

#include <pthread.h>

typedef struct {

    int variabile;

    /* TBD: Completare la struttura dati monitor */
    pthread_mutex_t mutex;
    pthread_cond_t CV_LETT;
    pthread_cond_t CV_SCRITT;

    int cv_lett;
    int cv_scritt;

    int n_lett;
    int n_scritt;

    int busy;

} MonitorLS;

void aggregatore(int id_coda_sensore, int id_code_collettori[3]);
void * thread_lettore(void *);
void * thread_scrittore(void *);
void lettura(MonitorLS *, int * valore);
void scrittura(MonitorLS *, int valore);

#endif