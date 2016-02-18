/* Obi.c */
/* Delmastro Alessandro */
/* 23-10-2015 */
/* Molti figli decrementano vasualmente un valore in memoria condivisa e il padre verifica fino a quando questo e' maggiore di 0 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "mutex.h"
#include "shm.h"

#define CLONI 5

bool padre(int idSem, int* shMem);
bool figlio(int idSem, int* shMem);

int main(int argc, char* argv[]){
	int* shMem;
	int idMem, idSem, ipcKeySem, ipcKeyMem, i, pid;
	
	if(3 != argc){
		printf("USAGE %s IPC_KEY_MEM IPC_KEY_SEM\n", argv[0]);
		return -1;
	}
	
	ipcKeyMem = atoi(argv[1]);
	ipcKeySem = atoi(argv[2]);
	
	shMem = shm_create(ipcKeyMem, sizeof(int), &idMem);
	*shMem = 100;
	idSem = mutexCreate(ipcKeySem, 0);
	
	pid = getpid();
	srand(pid + time(NULL));
	for(i=0; i<CLONI && pid; i++){
		pid = fork();
	}
	
	
	if(pid){		
		mutexUnlock(idSem);
		/*sono nel padre*/
		while(padre(idSem, shMem)){}
		
		for(i=0; i<CLONI; i++){
			wait();
		}
		printf("Sono morto.\n");
		fflush(stdout);
	}else{
		/*sono nel figlio*/		
		while(figlio(idSem, shMem)){}
	}
	
	return 0;
}

/*codice del padre*/
bool padre(int idSem, int* shMem){
	bool vivo;
	
	mutexLock(idSem);
	if(1 > *shMem){
		vivo = false;
	}else{
		vivo = true;
	}
	mutexUnlock(idSem);
	
	return vivo;
}

/*codice del figlio*/
bool figlio(int idSem, int* shMem){
	bool vivo;
	int danno;
	
	mutexLock(idSem);
	if(0 < *shMem){
		vivo = true;
		danno = (rand()%15)+1;
		*shMem -= danno;
		printf("Ho colpito Obi! - %d di danno.\n", danno);
		fflush(stdout);
	}else{		
		vivo = false;
	}
	mutexUnlock(idSem);
	
	return vivo;	
}
