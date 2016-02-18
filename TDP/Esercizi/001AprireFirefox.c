/* Delmastro Alessandro */
/* 5 O */
/* 22-09-2015 */
/* Questo programma esegue una fork e lancia firefox */

#include <stdio.h>
#include <unistd.h>

int main(){
	//dichiaro e inizializzo l'array di parametri, il nome del processo e l'elenco dei suoi parametri.
	char *a[]={"firefox", "www.yahoo.it", (char *)0};

	//eseguo la fork e se mi trovo nel figlio lancio firefox
	if(!fork()){
		execv("/usr/bin/firefox", a);
		printf("ciao");
	}else{
		//il padre aspetta il termine dell'esecuzione del figlio
		wait();
	}
	return 0;
}