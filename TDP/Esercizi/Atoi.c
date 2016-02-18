/* Delmastro Alessandro */
/* 5 O */
/* 01-10-2015 */
/* Questo programma effettua la conversione da stringa a numero */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* duplica_stringa(char* s);
char* leggi_stringa();

int main(){
	char* stringa, c;
	int numero, i;

	printf("Inserire un numero :\n");
	stringa = leggi_stringa();

	i=0;
	numero = 0;
    /*ciclo fino a quando incontro il carattere di fine stringa*/
	while(c=stringa[i]){
		/*printf("%c", c);*/
		numero = (numero*10) + (c-'0');
		i++;
	}

	printf("%d\n", numero);
	free(stringa);

	return 0;
}


/* Funzione che legge una stringa */
char* leggi_stringa(){
	char buffer[4096], c;
	int i;

	i = 0;
	/*scorro la stringa carattere per carattere*/
	while((c=getchar()) != '\n'){
		/*printf("%c", c);*/
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

    partenza=dup;
	while(*dup = *s ){
		dup ++;
		s ++;
	}

	return partenza;
}
