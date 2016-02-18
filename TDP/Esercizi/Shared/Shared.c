/* Shared.c */
/* Delmastro Alessandro */
/* 23-10-2015 */
/* Semplice gestione di una memoria condivisa */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "mutex.h"
#include "shm.h"

void padre(int sem_id, int* sh_mem);
void figlio(int sem_id, int* sh_mem);

int main(int argc, char* argv[]){
	int* sh_mem;
	int ipc_key_shm, shm_id, ipc_key_sem, sem_id;
	
	if(argc!=3){
		printf("Usage %s IPC_KEY IPC_KEYSEM.\n", argv[0]);
		return -1;
	}
	
	ipc_key_shm = atoi(argv[1]);	
	ipc_key_sem = atoi(argv[2]);
	/* creo la shared memory delle dimensioni di un intero */
	sh_mem = (int *)shm_create(ipc_key_shm, sizeof(int), &shm_id);
	/* creo il semaforo per regolare l'accesso alla memoria condivisa */
	sem_id = mutexCreate(ipc_key_sem, 0);
	/* inizializzo la shared memory */
	*sh_mem = 0;
	
	srand(getpid() + time(NULL));
	
	if(fork()){				/* padre */
		mutexUnlock(sem_id);
		while(1){
			padre(sem_id, sh_mem);
		}
	}else{					/* figlio */
		while(1){
			figlio(sem_id, sh_mem);
		}
	}

	return 0;
}


void padre(int sem_id, int* sh_mem){

	mutexLock(sem_id);
	if(*sh_mem == 0){
		*sh_mem = (rand()%20)+1;
	}
	mutexUnlock(sem_id);
}

void figlio(int sem_id, int* sh_mem){
	mutexLock(sem_id);
	if(*sh_mem != 0){
		printf("%d\n", *sh_mem);
		fflush(stdout);
		*sh_mem = 0;
	}
	mutexUnlock(sem_id);
}
