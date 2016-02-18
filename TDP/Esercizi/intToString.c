/* Delmastro Alessandro */
/* 5 O */
/* 02-10-2015 */
/* Questo programma esegue la conversione da numero a stringa */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	int numero, cifre, i, n, divisore;
	char *stringa;

	printf("Inserire il numero : ");
	scanf("%d", &numero);
	/*Ottengo il numero di cifre e alloco una porzione di memoria per un egual numero di caratteri*/
	cifre =(int)log10(numero) +1;
	stringa = (char *)malloc(sizeof(char)*(cifre+1));
	
	for(i=cifre; i>0; i--){
		divisore = pow(10, i-1);
		n = numero/divisore;
		printf("%d", n);
		numero -= n*divisore;
		stringa[i] = ('0' + n);
	}

	stringa[i] ='\0';
	
	printf("%s\n", stringa);

	return 0;
}

