#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int pid;
	int n_figli;

	if(argc != 2){
		return(-1);
	}	
	
	n_figli = atoi(argv[1]);
	pid = getpid();

	/*forzo l'uscita dal for quando il pid vale 0(nel figlio)*/
	for(; n_figli && pid; n_figli--)
		pid= fork();

	printf("[%d]\n", getpid());
	return 0;
}