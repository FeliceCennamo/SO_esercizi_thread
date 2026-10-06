#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "prodcons_msg.h"
#include "prodcons_client.h"

static int id_coda_richieste;
static int id_coda_risposte;

void init_client(int id_coda_richieste_parametro, int id_coda_risposte_parametro) {

    id_coda_richieste = id_coda_richieste_parametro;
    id_coda_risposte = id_coda_risposte_parametro;
}

void produci_con_somma(int val1, int val2, int val3) {

    /* TBD: Inviare un messaggio di tipo "PRODUCI CON SOMMA" */
    richiesta_rpc req1;
    req1.type = PRODUCI_CON_SOMMA;
    req1.val1 = val1;
    req1.val2 = val2;
    req1.val3 = val3;
    req1.pid = getpid();

    printf("[Client] Invio richiesta PRODUCI_CON_SOMMA(%d, %d, %d)\n", val1, val2, val3);
    
    int ret = msgsnd(id_coda_richieste, &req1, sizeof(richiesta_rpc)- sizeof(long), 0);

    if(ret < 0 ){
        perror("errore send client");
        exit(1);
    }

    risposta_rpc risp1;

    ret = msgrcv(id_coda_risposte, &risp1, sizeof(risposta_rpc) - sizeof(long), getpid(), 0);

    if(ret < 0){
        perror("errore receive client");
        exit(1);
    }


    int risultato = risp1.res;
    int errore = risp1.error;

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);
}

void produci(int val) {

    richiesta_rpc req1;
    req1.type = PRODUCI;
    req1.val1 = val;
    req1.pid = getpid();

    printf("[Client] Invio richiesta PRODUCI(%d)\n", val);

    int ret = msgsnd(id_coda_richieste, &req1, sizeof(richiesta_rpc) - sizeof(long), 0);

    if(ret < 0){
        perror("errore send client");
        exit(1);
    }

    risposta_rpc risp1;

    ret = msgrcv(id_coda_risposte, &risp1, sizeof(risposta_rpc) - sizeof(long), getpid(), 0);


    int risultato = risp1.res;
    int errore = risp1.error;

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);
}

int consuma() {

    richiesta_rpc req1;
    req1.type = CONSUMA;
    req1.pid = getpid();

    printf("[Client] Invio richiesta CONSUMA(nessun parametro)\n");

    int ret = msgsnd(id_coda_richieste, &req1, sizeof(richiesta_rpc)-sizeof(long), 0);
    
    if(ret < 0){
        perror("errore send client");
        exit(1);
    }

    risposta_rpc risp1;

    ret = msgrcv(id_coda_risposte, &risp1, sizeof(risposta_rpc) - sizeof(long), getpid(), 0 );

    int risultato = risp1.res;
    int errore = risp1.error;

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);

    return risultato;
}