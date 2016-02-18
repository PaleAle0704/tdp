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
int conta_parole(char* s);
void estrapola_parole(char** stringhe, char*stringa);
void pulisci(char** splittata);

int main(){
	char*stringa;
	char**splittata;
	int parole, i;

	stringa = leggi_stringa();

	
	parole = conta_parole(stringa);
	splittata = (char**)malloc(sizeof(char)*(parole+1));
	estrapola_parole(splittata, stringa);
	
	
	for(; *splittata; splittata++){
		stampa_stringa(*splittata);	
	}
	/*for(i=0; i<parole; i++){
		stampa_stringa(splittata[i]);
	}*/
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
	
	/*	for(partenza=dup; *dup=*s; s++, dup++){printf("%c", *s);} */
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

/* Funzione che conta quante parole sono presenti in una stringa */
int conta_parole(char* s){
		int cont;
		char carattere_precedente;

		cont = 0;
		carattere_precedente = ' ';
		
		while(*s){
			if(*s != ' ' && carattere_precedente==' '){
				cont+=1;
			}
			carattere_precedente = *s;
			s++;
		}
		
		return cont;
		
}

/* Funzione che estrae le parole da una stringa e le pone in un vettore di stringhe */
void estrapola_parole(char** stringhe, char*stringa){
		char buffer[4096], carattere_precedente;
		int i, cont;

		carattere_precedente = ' ';
		cont=0;
		
		for(i=0; *stringa; stringa++, i++){
			if(*stringa!=' '){
				buffer[i]=*stringa;
			}else if(carattere_precedente!=' '){
				buffer[i] = '\0';
				stringhe[cont] = duplica_stringa(buffer);
				cont+=1;
				i=-1;
			}else{
				i-=1;
			}	
			carattere_precedente = *stringa;
		}
		if(buffer[i-1]!='\0' && i!=0){
			buffer[i] = '\0';
			stringhe[cont] = duplica_stringa(buffer);
		}
		stringhe[cont+1] = '\0';
}


/* Funzione che dealloca la ram occupata con la malloc */
void pulisci(char** splittata){
	char** temp;
	
	temp = splittata;
	for(;*splittata; splittata++){
		free(*splittata);
	}
	free(temp);
}
