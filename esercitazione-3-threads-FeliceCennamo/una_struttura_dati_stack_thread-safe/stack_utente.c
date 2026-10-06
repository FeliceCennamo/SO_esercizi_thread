#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "stack.h"

void *Inserisci(void * s)
{

	int i;
	Elem v;

	Stack* p = (Stack*) s;

	for(i=0; i<4; i++) {

		v = rand() % 11;

		StackPush(p,v);

		int size = StackSize(p);
		printf("Dimensione: %d\n", size);

		sleep(1);
	}

	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;
	Stack* p = (Stack*) s;


	for(i=0; i<10; i++) {

		v1 = StackPop(p);

		v2 = StackPop(p);

		printf("Somma: %d\n", v1+v2);

		int size = StackSize(p);
		printf("Dimensione: %d\n", size);

		sleep(3);
	}

	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{

	int rc;
	int i;
	pthread_t threads[6];

	srand(time(NULL));


	Stack * stack = (Stack*) malloc(sizeof(Stack));
	StackInit(stack,4);
	


	for(i=0; i<5; i++) {

		pthread_create(&threads[i],NULL, Inserisci,(void*)stack);
	}


	pthread_create(&threads[5],NULL, Preleva,(void*)stack);


	for(i=0; i<5; i++) {

		pthread_join(threads[i],NULL);
		
	}


	
	pthread_join(threads[5],NULL);

	
	StackRemove(stack);
	free(stack);
	return 0;
}


