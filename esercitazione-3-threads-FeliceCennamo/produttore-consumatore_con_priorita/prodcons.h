#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include <pthread.h>

#define DIM 3

typedef struct{

	int buffer[DIM];

	/* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
    
} PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons * p);
void produci_alta_prio(PriorityProdCons * p, int value);
void produci_bassa_prio(PriorityProdCons * p, int value);
int consuma(PriorityProdCons * p);
void rimuovi_prod_cons(PriorityProdCons * p);

#endif
