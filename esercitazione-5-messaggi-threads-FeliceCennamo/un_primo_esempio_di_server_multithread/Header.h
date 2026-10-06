#include <sys/types.h>

#define RICHIESTE 5
#define CLIENT 3

/* TBD: Definire una struct "msg_richiesta" per i messaggi dal client al server */
typedef struct{
    long type;
    pid_t pid;
    int val1;
    int val2;
}msg_richiesta;

/* TBD: Definire una struct "msg_risposta" per i messaggi dal server al client */
typedef struct{
    long type; //pid del client richiedente
    int res;
}msg_risposta;

void client(int id_c, int id_s);
void server(int id_c, int id_s);
void* Prodotto(void*);
