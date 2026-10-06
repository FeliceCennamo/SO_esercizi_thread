#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"


void * produttore_alta_priorita(void * p)
{

	/* TBD: Gestire il passaggio di parametri */

	for(int i=0; i<3; i++) {

		int value = rand() % 12;

		/* TBD: Chiamare il metodo di produzione alta priorità */

		sleep(2);
	}

	pthread_exit(NULL);
}


void * produttore_bassa_priorita(void * p)
{

	/* TBD: Gestire il passaggio di parametri */

	for(int i=0; i<3; i++) {

		int value = 13 + (rand() % 12);

		/* TBD: Chiamare il metodo di produzione bassa priorità */

		sleep(1);
	}

	pthread_exit(NULL);
}


void * consumatore(void * p)
{

	/* TBD: Gestire il passaggio di parametri */

	for(int i=0; i<12; i++) {

		/* TBD: Chiamare il metodo consuma() */

		int value = /* TBD */

		sleep(1);
	}

	pthread_exit(NULL);
}




int main(int argc, char *argv[])
{

	pthread_t threads[5];
	pthread_attr_t attr;

	int rc;
	int i;

	srand(time(NULL));


	PriorityProdCons * prodcons = /* TBD: Allocare un oggetto monitor */;



	/* TBD: Inizializzare l'oggetto monitor */


	/* TBD: Creare 3 thread produttore bassa priorità,
	 *      1 thread produttore alta priorità,
	 *      e 1 thread consumatore.
	 */


	/* TBD: Effettuare la join con i thread */


	/* TBD: Richiamare il distruttore dell'oggetto monitor, e deallocare la memoria */

}

