/* Delmastro Alessandro */
/* 5 O */
/* 01-10-2015 */
/* Questo programma emula una shell */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define PROMPT "Sono la shell di Alessandro>"

int cmpstr(char *s1, char *s2);
char* prompt();
char* leggi_stringa();
char* duplica_stringa(char* s);
void pulisci(char** splittata);
char** duplica_array(char** buffer, int celle);
char** split(char* stringa);
int lung_stringa(char* s);

int main(){
	char* cmd;
	char** cmd_array;

	cmd = leggi_stringa();

	while(cmpstr(cmd, "exit") != 0){
		cmd_array = split(cmd);
		if(!fork()){
			execvp(cmd_array[0], cmd_array);
			printf("command not found\n");
			return -1;
		}
		wait();
		free(cmd);
		pulisci(cmd_array);
		cmd = leggi_stringa();
	}
	return 0;
}


/*Funzione per la comparazione delle stringhe*/

int cmpstr(char *s1, char *s2){
	if(*s1 > *s2) return(-1);
	if(*s1 < *s2) return(1);
	if(*s1) return(cmpstr(++s1, ++s2));
	return 0;
}

/*Funzione che presenta a video la scritta PROMPT e riceve una stringa in input*/

char* prompt(){
	printf("%s",PROMPT);
	return(leggi_stringa());
}

/* Funzione che legge una stringa */
char* leggi_stringa(){
	char buffer[4096], c;
	int i;
	
	i = 0;
	while((c=getchar()) != '\n'){
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';

	return duplica_stringa(buffer);
}

/* Funzione che duplica una stringa utilizzando la malloc */
char* duplica_stringa(char* s){
	char * dup, *partenza;

	dup = (char*)malloc(sizeof(char)*(lung_stringa(s) + 1));
	
	partenza = dup;
	while(*dup = *s ){
		dup ++;
		s ++;
	}

	return partenza;
}

/* Funzione che dealloca la ram occupata con la malloc */
void pulisci(char** splittata){
	char** temp;
	
	temp = splittata;
	for(;*splittata; splittata++){
		free(*splittata);
	}
//	free(temp);
}


/* Funzione che divide le parole presenti in una stringa */
char** split(char* stringa){
	char* buffer[4096];
	char* inizioParola;
	int cont;
	
	cont=0;
	inizioParola = stringa;
	for(; *stringa; stringa++){
		if(*stringa == ' '){
			*stringa = '\0';
			if(*inizioParola){
				buffer[cont]= duplica_stringa(inizioParola);
				cont+=1;
			}
			*stringa = ' ';
			inizioParola = stringa + 1;
		}
	}
	if(*inizioParola){
		buffer[cont] = duplica_stringa(inizioParola);
		cont+=1;
	}
	
	buffer[cont] = '\0';
	int i;
	
	return duplica_array(buffer, cont);
}

/* Copia un array di stringhe fino al carattere di fie stringa, ne restituisce uno allocato dinamicamente */
char** duplica_array(char** buffer, int celle){
		char** arrayStringhe;
		char** temp;
		
		arrayStringhe = (char**)malloc(sizeof(char*)*(celle+1));
		temp = arrayStringhe;
		for(; *buffer; buffer++, arrayStringhe++){
			*arrayStringhe = *buffer;
		}
		*arrayStringhe = '\0';
		
		return temp;
}

/* calcola la lunghezza di una stringa */
int lung_stringa(char* s){
	int i;
	
	for(i=0; *(s+i); i++){};

	return i;
}
