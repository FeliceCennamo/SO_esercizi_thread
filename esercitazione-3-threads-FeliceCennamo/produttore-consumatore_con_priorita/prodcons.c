#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"


void inizializza_prod_cons(PriorityProdCons* p){

    /* TBD: Inizializzare tutte le variabili del monitor */

}

void rimuovi_prod_cons(PriorityProdCons* p){

    /* TBD: Disattivare mutex e variabili condition */

}

void produci_alta_prio(PriorityProdCons* p, int value) {

	printf("Produttore tipo 1 accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     *
     *      Si introduca nel monitor una variabile "threads_prio_1"
     *      per contare il numero di produttori sospesi ad alta priorità.
     */


	/* Produzione */

	/*TBD*/ = value;

	printf("Produttore tipo 1 ha prodotto %d\n", value);


}




void produci_bassa_prio(PriorityProdCons* p, int value) {

	int value;

	printf("Produttore tipo 2 accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
	 *
	 *      I produttori a bassa priorità devono sospendersi sia nel caso di vettore
	 *      di buffer già pieno, sia nel caso vi siano produttori ad alta priorità già
	 *      in attesa.
     *
     *      Si introduca nel monitor una variabile "threads_prio_2"
     *      per contare il numero di produttori sospesi a bassa priorità.
     */


	/* Produzione */

	value = 13 + (rand() % 12);

	printf("Produttore tipo 2 ha prodotto %d\n", value);


}




int consuma(PriorityProdCons* p){

	int value;

	printf("Consumatore accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     */


	/* Consumazione */

	value = /* TBD */

	printf("Consumatore ha consumato %d\n", value);

	return value;
}

