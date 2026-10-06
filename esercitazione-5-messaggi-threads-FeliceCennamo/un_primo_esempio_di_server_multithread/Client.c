#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"

void client(int id_c, int id_s){

	int k;
	int ret;

	srand(getpid());



	for(k=0;k<RICHIESTE;k++){

		/* TBD: Inviare un messaggio di richiesta */
		msg_richiesta msg;

		int v1 = rand()%101;
		int v2 = rand()%101;
		msg.type = 1;
		msg.val1 = v1;
		msg.val2 = v2;
		msg.pid = getpid();

		printf("Richiesta %d Inviata (%d, %d) [PID=%ld]\n\n", k, v1, v2, getpid());

		ret = msgsnd(id_c, &msg, sizeof(msg_richiesta) - sizeof(long), 0);
	
		if(ret < 0) {
			perror("Errore invio richiesta client");
			exit(1);
		}

		msg_risposta risp;
		ret = msgrcv(id_s, &risp, sizeof(msg_risposta) - sizeof(long), getpid(), 0);

		if(ret < 0) {
			perror("Errore ricezione risposta client");
			exit(1);
		}

		int v3 = risp.res;
		/* TBD */

		printf("Risposta %d Ricevuta (%d) [PID=%ld]\n\n", k, v3, getpid());
	}

}

