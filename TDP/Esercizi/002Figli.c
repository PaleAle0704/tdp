/* Delmastro Alessandro */
/* 5 O */
/* 22-09-2015 */
/* Questo programma genera un numero di figli che riceve come parametro da linea di comando */ 

#include <stdio.h>

int main(int argc, char *argv[]){
	int i;
	int figli;
	
	if(argc != 2){
		printf("Parametri in eccesso.\n");
	}else{
		figli = atoi(argv[1]);
		printf("%d\n", figli);
		for(i=0; i<figli; i++){
			if(!fork()){
				printf("Il mio pid vale %d\n", getpid());
				return 1;
			}else{
				wait();
			}
		}
	}
	
	return 0;
}