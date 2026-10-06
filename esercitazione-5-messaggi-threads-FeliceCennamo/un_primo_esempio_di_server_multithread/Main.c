#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Header.h"




int main(){

	pid_t pidc, pids;
	int id_c, id_s,i;
	int ret;

	key_t key_c = ftok(".",'a');
	id_c = msgget(key_c, IPC_CREAT | 0644);
	
	if(id_c < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}

	key_t key_s = ftok(".",'b' );
	id_s = msgget(key_s, IPC_CREAT | 0644);

	if(id_s < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}



	for(i=0;i<CLIENT;i++){

		pidc = fork();
		if(pidc < 0){
			perror("Errore fork client");
			exit(1);
		}else if (pidc == 0){
			client(id_c, id_s);
			exit(0);
		}
	}


	pids = fork();

	if(pids<0) {
		perror("Errore fork server");
		exit(1);
	}else if (pids == 0){
			server(id_c, id_s);
			exit(0);	
	}

	for(int i = 0; i<CLIENT; i++){
		wait(NULL);
	}

	msg_richiesta msg;
	msg.type = 1;
	msg.val1 = -1;
	msg.val2 = -1;
	ret = msgsnd(id_c, &msg, sizeof(msg_richiesta) - sizeof(long), 0);
	
	if(ret < 0) {
		perror("Errore invio messaggio di terminazione");
		exit(1);
	}if(ret >= 0)
		




	

	wait(0);

	msgctl(id_c, IPC_RMID, 0);
	msgctl(id_s, IPC_RMID, 0);

	return 0;

}

