#include <stdio.h>
#include <pthread.h>

void* foo(void* p);
int main(){
	pthread_t mioThread;
	
	mioThread = pthread_create(&mioThread, NULL, foo, NULL);
	sleep(3);
	return 0;
}

void* foo(void* p){
	printf("[%x]\n", pthread_self());
}
