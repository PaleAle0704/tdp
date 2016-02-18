#define N_THREADS 10
#define WAITING_TIME 2
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* incrementatore(void* p);
typedef struct{						/*in questo modo, quando dichiaro le variabili non devo scrivere 'struct'*/
	pthread_mutex_t * p_mymutex;
	int* p_cont;
}Thread_param;

int main(int argc, char**argv){
	pthread_t mythreads[N_THREADS];
	int i;		/*indice sui thread*/
	int cont;	/*variabile condivisa tra i thread*/
	pthread_mutex_t mymutex;
	pthread_mutexattr_t myattr;
	Thread_param parametri;

	pthread_mutexattr_init(&myattr);
	pthread_mutex_init(&mymutex, &myattr);

	cont = 0;
	pthread_mutex_trylock(&mymutex);	/*dopo questa chiamata il semaforo è sicuramente locked*/
	parametri.p_mymutex = &mymutex;	/*preparo i parametri per i thread*/
	parametri.p_cont = &cont;

	for(i=0; i<N_THREADS; i++){
		pthread_create(&mythreads[i], NULL, incrementatore, (void*)&parametri);
	}

	pthread_mutex_unlock(&mymutex);	

	sleep(WAITING_TIME);
	printf("cont ora vale %d\n", cont);

	pthread_mutex_destroy(&mymutex);
	pthread_mutexattr_destroy(&myattr);

	return(0);
}

void* incrementatore(void* p){
	Thread_param* parametri;
	parametri = (Thread_param*)p;

	while(1){
		pthread_mutex_lock((*parametri).p_mymutex);			/*l'asterisco ha precedenza sui punti*/
		*(parametri -> p_cont) += 1;
		pthread_mutex_unlock(parametri -> p_mymutex);		/*la freccina fa lo stesso lavoro, funziona con le maniglie*/
	}
}