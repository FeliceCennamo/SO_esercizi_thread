#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


struct monitor {

	int stazione;
	int id_treno;

	pthread_mutex_t mutex;
	pthread_cond_t CV_LETT;
	pthread_cond_t CV_SCRITT;

	int n_lett;
	int n_scritt;

	int n_cv_lett;
	int n_cv_scritt;

	/* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
	
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_stazione(struct monitor * m, int stazione);
int leggi_stazione(struct monitor * m);



#endif
