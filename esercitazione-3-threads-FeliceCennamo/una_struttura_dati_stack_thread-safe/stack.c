#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void StackInit(Stack * s, int dim) {

	
	pthread_mutex_init(&s->mutex,NULL);
	pthread_cond_init(&s->CV_CONS,NULL);
	pthread_cond_init(&s->CV_PROD,NULL);

	/* Il costruttore crea in memoria dinamica (heap)
	 * l'area di memoria per ospitare gli elementi dello stack.
	 * Il parametro "dim" indica il numero massimo di elementi.
	 */

	s->dati = (Elem *) malloc(sizeof(Elem)*dim);
	
	s->dim = dim;
	s->testa = 0;
}


void StackRemove(Stack * s) {

	pthread_mutex_destroy(&s->mutex);
	pthread_cond_destroy(&s->CV_CONS);
	pthread_cond_destroy(&s->CV_PROD);

	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	pthread_mutex_lock(&s->mutex);

	while(s->testa == s->dim)
		pthread_cond_wait(&s->CV_PROD, &s->mutex); // la stack è zero indexed quindi se testa prima dell'aggiornamento
												   // punta a dim-1 significa che la stack è piena e non posso pushare
	s->dati[s->testa] = e;
	s->testa++; //che funziona anche come variabile di conteggio
	
	pthread_cond_signal(&s->CV_CONS); //se ho prodotto posso segnalare un consumatore
	pthread_mutex_unlock(&s->mutex);

	printf("Inserimento: %d\n", e);


}


Elem StackPop(Stack * s) {

	int elemento;

	pthread_mutex_lock(&s->mutex);
	
	while(s->testa == 0) //cioè se la stack è vuota
		pthread_cond_wait(&s->CV_CONS, &s->mutex);

	s->testa--;
	elemento = s->dati[s->testa];

	pthread_cond_signal(&s->CV_PROD);
	pthread_mutex_unlock(&s->mutex);

	printf("Prelievo: %d\n", elemento);

	return elemento;
}

int StackSize(Stack * s) {

	int size;

	pthread_mutex_lock(&s->mutex);
	size = s->testa;
	pthread_mutex_unlock(&s->mutex);

	return size;
}
