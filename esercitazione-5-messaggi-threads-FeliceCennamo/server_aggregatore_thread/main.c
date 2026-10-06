#include "sensore.h"
#include "aggregatore.h"
#include "collettore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {


    /* TBD: Creare le code di messaggi, 
     * e avviare i processi sensore, aggregatore, e collettore 
     */
    int id_coda_aggregatore = msgget(IPC_PRIVATE, IPC_CREAT | 0644);

    if(id_coda_aggregatore < 0){
        perror("errore get aggregatore");
        exit(1);


    }

    int id_coda_collettore[3];
    
    for(int i = 0; i < 3; i++){
        id_coda_collettore[i]= msgget(IPC_PRIVATE, IPC_CREAT | 0644);
        if(id_coda_collettore[i]<0){
            perror("errore get collettore");
            exit(1);
        }
    }

    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("errore fork");
        exit(1);
    }else if(pid == 0){
        sensore(id_coda_aggregatore);
        exit(0);
    }

    pid = fork();

    if(pid < 0){
        perror("errore fork");
        exit(1);
    }else if(pid == 0){
        aggregatore(id_coda_aggregatore, id_coda_collettore);
        exit(0);
    }

    for(int i = 0; i <3 ; i++){

    pid = fork();

    if(pid < 0){
        perror("errore fork");
        exit(1);
    }else if(pid == 0){
        collettore(id_coda_collettore[i]);
        exit(0);
    }
    }

    for(int i = 0; i < 4; i++){
        wait(NULL);
    }

    msgctl(id_coda_aggregatore, IPC_RMID, 0);

    for(int i = 0; i < 3; i++){
       msgctl(id_coda_collettore[i], IPC_RMID, 0);
    }
}