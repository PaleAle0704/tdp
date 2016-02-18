/* Delmastro Alessandro */
/* 30-10-2015 */
/* 5 O */
/* Programma che genera n thread che stampano un numero passato per parametro */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* foo(void* p);

int main(int argc, char** argv){
	int i, nThread;
	int* vetInteri;
	pthread_t thread;
	
	if(argc!=2){
		printf("USAGE %s NUMERO_THREAD\n", argv[0]);
		return -1;
	}
	
	/*ottengo il numero di thread da creare*/
	nThread = atoi(argv[1]);
	/*alloco dinamicamente un vettore di nThread interi*/
	srand(time(NULL));
	vetInteri = malloc(sizeof(int)*nThread);
	/*stampo il contenuto del vettore mentre lo valorizzo*/
	putchar('[');
	for(i=0; i<nThread; i++){
		vetInteri[i] = (rand()%100)+1;
		/*operatore ternario*/
		printf("%d%c", vetInteri[i], (i<nThread-1)?',':']');
	}
	putchar('\n');
	
	/*genero nThread thread e passo a ciascuno un valore del vettore di interi*/
	for(i=0; i<nThread; i++){
		pthread_create(&thread, NULL, foo, (void*)(vetInteri+i));
	}
	
	sleep(3);
	free(vetInteri);
	
	return 0;
}

void* foo(void* p){
	printf("Sono [%x], il mio valore e' %d.\n",pthread_self(), *(int*)p);
	fflush(stdout);
}
