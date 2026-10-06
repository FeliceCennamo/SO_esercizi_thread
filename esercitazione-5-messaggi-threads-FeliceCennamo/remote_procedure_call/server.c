#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "prodcons_msg.h"
#include "prodcons_server.h"

#define TOTALE_WORKER 3
#define RICHIESTE_PER_WORKER 2

void * worker(void *);

struct param {

    int id_coda_richieste;
    int id_coda_risposte;
};

int main() {

    key_t chiave_coda_richieste = ftok(".", 'a');
    int id_coda_richieste = msgget(chiave_coda_richieste, IPC_CREAT | 0644);

    key_t chiave_coda_risposte = ftok(".", 'b');
    int id_coda_risposte = msgget(chiave_coda_risposte, IPC_CREAT | 0644);

    pthread_t threads[TOTALE_WORKER];


    init_monitor();

    struct param* p = (struct param*)malloc(sizeof(struct param));
    p->id_coda_richieste = id_coda_richieste;
    p->id_coda_risposte = id_coda_risposte;

    for(int i=0; i<TOTALE_WORKER; i++) {

        pthread_create(&threads[i], NULL, worker, (void*) p);
        
        
    }


    for(int i=0; i<TOTALE_WORKER; i++) {

        pthread_join(threads[i], NULL);
    }

    remove_monitor();

    return 0;
}


void * worker(void * x) {

    struct param* p = (struct param*) x;

    int id_coda_richieste = p->id_coda_richieste;
    int id_coda_risposte = p->id_coda_risposte;

    int ret;
    int risultato;
    int errore;

    printf("[Worker] In attesa di richieste...\n");


    for(int i=0; i<RICHIESTE_PER_WORKER; i++) {

       
        richiesta_rpc req;
        ret = msgrcv(id_coda_richieste, &req, sizeof(richiesta_rpc)- sizeof(long), 0, 0);

        if(ret < 0){
            perror("errore receive server");
            exit(1);
        }

        
        if(req.type == PRODUCI_CON_SOMMA) {

            int val1 = req.val1;
            int val2 = req.val2;
            int val3 = req.val3;

            printf("[Worker] Ricevuta richiesta di tipo PRODUCI CON SOMMA(%d, %d, %d)\n", val1, val2, val3);

            produci_con_somma(val1, val2, val3);

            risultato = 0;
            errore = 0;

        }
        else if(req.type == PRODUCI) {

            int val1 = req.val1;

            printf("[Worker] Ricevuta richiesta di tipo PRODUCI(%d)\n", val1);

            produci(val1);

            risultato = 0;
            errore = 0;
        }
        else if(req.type == CONSUMA) {

            printf("[Worker] Ricevuta richiesta di tipo CONSUMA(nessun parametro)\n");

            risultato = consuma();
            errore = 0;
        }
        else {

            printf("[Worker] Errore, tipo di richiesta sconosciuta");

            risultato = -1;
            errore = 1;
        }

        risposta_rpc risp;
        risp.type = req.pid;
        risp.error = errore;
        risp.res = risultato;

        ret = msgsnd(id_coda_risposte, &risp, sizeof(risposta_rpc)- sizeof(long), 0);

        if(ret <0){
            perror("errore send server");
            exit(1);
        }


        printf("[Worker] Inviato risposta: risultato=%d, errore=%d\n", risultato, errore);

    }




    printf("[Worker] Terminazione\n");

    return NULL;
}
