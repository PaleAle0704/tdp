/* Delmastro Alessandro */
/* 6-11-2015 */
/* 5 O */
/* Calcolo della successione di Fibonacci mediante l'uso dei thread */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* fibonacci(void* n);

int main(int argc, char*argv[]){
	pthread_t a;
	int risultato, *ris, *numero, num;
	
	if(argc!=2){
		return -1;
	}

	num = atoi(argv[1]);
	//numero = (int*)malloc(sizeof(int));
	//*numero = atoi(argv[1]);

	//pthread_create(&a, NULL, fibonacci, (void*)numero);		
	pthread_create(&a, NULL, fibonacci, (void*)&num);	
	pthread_join(a, (void**)&ris);

	printf("%d\n", *ris);

	//free(numero);
	return 0;
}

void* fibonacci(void* n){
	int* tot;
	pthread_t a, b;
	int num, n1, n2;
	int*r1, *r2;
	
	num = *(int* )n;
	//printf("Dentro a fibo\n");
	//fflush(stdout);
	//free(n);
	//tot = (int*)malloc(sizeof(int));
	if(num>1){
		//n1 = (int*)malloc(sizeof(int));
		//n2 = (int*)malloc(sizeof(int));

		n1 = num-1;
		n2 = num-2;
			
		pthread_create(&a, NULL, fibonacci, (void*)&n1);
		pthread_create(&b, NULL, fibonacci, (void*)&n2);		
		
	
		pthread_join(a, (void**)&r1);
		printf("fibo");
		pthread_join(b, (void**)&r2);

		*tot = *r1 + *r2;
		printf("Risultato %d\n", *tot);
		fflush(stdout);
		//free(n1);
		//free(n2);
		
	}else{
		*tot = 1;
	}

	printf("fibofibo\n");
	pthread_exit(tot);
}
