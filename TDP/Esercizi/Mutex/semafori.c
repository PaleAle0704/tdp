#include "mutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define IPC_KEY 42

int main(){
	int mutex_id, pid, i;
	
	mutex_id = mutexCreate(IPC_KEY, 0);
	mutexLock(mutex_id);
		
	pid = getpid();
	fflush(stdin);
	
	for(i=0; (i<8) && pid; i++) pid = fork();
	
	if(pid){
		printf("*** Premere invio per far partire la gara ***\n");
		while(getchar()!='\n') {}
		
		mutexUnlock(mutex_id);
		
		for(i=0; i<8; i++){
			wait();
		}
		mutexRemove(mutex_id);
	}else{
		srand(getpid() + time(NULL));
		printf("[%d]\n", getpid());
		mutexLock(mutex_id);
		mutexUnlock(mutex_id);
		sleep(rand()%5 + 1);
		printf("[%d] Sono arrivato\n", getpid());
	}
	
	return 0;
}
