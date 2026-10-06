#include "header.h"


void inizializza(struct monitor* m){

	m->stazione=0;
	m->id_treno=0;

	/* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
	pthread_mutex_init(&m->mutex,NULL);
	pthread_cond_init(&m->CV_LETT, NULL);
	pthread_cond_init(&m->CV_SCRITT,NULL);

	m->n_lett = 0;
	m->n_scritt = 0;

	m->n_cv_lett = 0;
	m->n_cv_scritt = 0;
}

void rimuovi (struct monitor* m){

	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->CV_LETT);
	pthread_cond_destroy(&m->CV_SCRITT);

}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_stazione(struct monitor* m, int stazione){

	
	pthread_mutex_lock(&m->mutex);


	while(m->n_lett > 0 || m->n_scritt > 0){ //se ci sono altri lettori o altri scrittori devo sospendere
		m->n_cv_scritt++;
		pthread_cond_wait(&m->CV_SCRITT, &m->mutex);
		m->n_cv_scritt--;
	}
	m->n_scritt++;

	// SCRITTURA
	m->stazione=stazione;
	printf("Scrittura: stazione=%d\n", stazione);

	m->n_scritt--;

	if(m->n_cv_scritt != 0)
		pthread_cond_signal(&m->CV_SCRITT);

	pthread_cond_broadcast(&m->CV_LETT);

	pthread_mutex_unlock(&m->mutex);
}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_stazione(struct monitor* m){

	pthread_mutex_lock(&m->mutex);

	
	while(m->n_scritt!= 0){
		m->n_cv_lett++;
		pthread_cond_wait(&m->CV_LETT, &m->mutex);
		m->n_cv_lett--;
	}

	m->n_lett++;

	// LETTURA
	int ris=m->stazione;
	printf("Lettura: stazione=%d\n", ris);

	m->n_lett--;

	if(m->n_cv_lett == 0)
		pthread_cond_signal(&m->CV_SCRITT);

	pthread_mutex_unlock(&m->mutex);
	return ris;
}

