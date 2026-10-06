#ifndef PRODCONS_MSG
#define PRODCONS_MSG

typedef struct {
    
    long type;
    int val1;
    int val2;
    int val3;
    pid_t pid;
} richiesta_rpc;

typedef struct {

    long type; //pid del chiamante
    int res;
    int error;
} risposta_rpc;

void produci_con_somma(int val1, int val2, int val3);
void produci(int val);
int consuma();

#define PRODUCI_CON_SOMMA 1
#define PRODUCI 2
#define CONSUMA 3

/* Nota: nei messaggi di risposta, usare come valore di "type" il PID del client */

#endif