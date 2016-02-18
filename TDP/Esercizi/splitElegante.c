/* Delmastro Alessandro */
/* 5 O */
/* 05 - 10 - 2015 */
/* Questo programma splitta una stringa data in input */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* leggi_stringa();
char* duplica_stringa(char* s);
void stampa_stringa(char* s);
void pulisci(char** splittata);
char** duplica_array(char** buffer, int celle);
char** split(char* stringa);

int main(){
	char*stringa;
	char**splittata;

	stringa = leggi_stringa();
	splittata = split(stringa);
	
	for(; *splittata; splittata++){
		stampa_stringa(*splittata);	
	}
	free(stringa);

	pulisci(splittata);

	return 0;
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

	dup = (char*)malloc(sizeof(char)*(strlen(s) + 1));
	
	partenza = dup;
	while(*dup = *s ){
		dup ++;
		s ++;
	}

	return partenza;
}

/* Funzione che stampa una stringa */
void stampa_stringa(char* s){
	for(;*s; s++)printf("%c", *s);
	printf("\n");
}

/* Funzione che dealloca la ram occupata con la malloc */
void pulisci(char** splittata){
	char** temp;
	
	temp = splittata;
	for(;*splittata; splittata++){
		free(*splittata);
	}
	printf("aleeee");
	fflush(stdout);
	//free(temp);
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
