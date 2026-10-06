#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"

/* Il thread padre condivide l'id della coda 
   delle risposte con i figli, tramite una 
   variabile globale "id_coda_risposte".
 */

/* NOTA: la coda delle risposte deve essere utilizzata
		 in modo mutuamente esclusivo dai thread
		 (vedi commento più avanti).
 */

int id_coda_risposte;

typedef struct{
	int v1;
	int v2;
	int id_risposte;
	int pid;
	pthread_mutex_t mutex;
}param;



void server(int id_c, int id_s){

	int k;
	int ret;
	pthread_t threads;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);

	id_coda_risposte = id_s;


	while(1){

		/* TBD: Ricevere un messaggio di richiesta dal client */
		msg_richiesta req;
		ret = msgrcv(id_c, &req, sizeof(msg_richiesta) - sizeof(long), 0, 0);

		if(ret < 0) {
			perror("Errore ricezione richiesta server");
			exit(1);
		}

		if( req.val1 == -1 && req.val2 == -1){			
			exit(0);
		}

		/* TBD: Avviare un thread figlio per l'elaborazione del messaggio,
				passandogli una **copia sullo heap** del messaggio ricevuto.
				(ogni thread figlio deve elaborare un messaggio diverso)
		 */
		param* p = (param*)malloc(sizeof(param));
		p->v1 = req.val1;
		p->v2 = req.val2;
		p->id_risposte = id_coda_risposte;
		p->mutex = mutex;
		p->pid = req.pid;
		pthread_create(&threads, &attr,Prodotto, (void*)p);

	}

}



void* Prodotto(void* v){

	int ret;
	param* data = (param*) v;

	int v3 = data->v1 * data->v2;
	


	/* TBD: Inviare il messaggio di risposta al client.
	        
	   IMPORTANTE: In questo esercizio, si richiede che 
	   			   la coda delle risposte sia utilizzata
				   in modo mutuamente esclusivo dai thread
	   			   (la funzione msgsnd() deve essere chiamata
				   all'interno di una sezione critica).
	 */
	msg_risposta risp;
	risp.res = v3;
	risp.type = data->pid;

	pthread_mutex_lock(&data->mutex);

	printf("\nSono Prodotto di Server. Invio del calcolo: %d\n\n", v3);  

	ret = msgsnd(data->id_risposte, &risp, sizeof(msg_risposta)- sizeof(long), 0);

	if(ret < 0) {
		perror("Errore invio risposta server");
		exit(1);
	}
	pthread_mutex_unlock(&data->mutex);

	pthread_exit(NULL);
}

