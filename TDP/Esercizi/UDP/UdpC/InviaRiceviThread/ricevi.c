#include "socket.h"
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void* thr_ricevi(void* p);

int main(int argc, char* argv[]){
	int port;
	pthread_t thrAscolta;
	
	if(argc != 2){
		printf("USAGE %s LISTENING_PORT\n", argv[0]);
		return(-1);
	}
	
	pthread_create(&thrAscolta, NULL, thr_ricevi, (void*)&port);
	port = atoi(argv[1]);
	
	getchar();
	
	return(0);
}

void* thr_ricevi(void* p){
	char* msg;
	USocket myself;
	int ret, port;
	Address* my_addr;	
	
	port = *(int *)(p);
	
	my_addr = create_Address("0.0.0.0", port);
	ret = createSocket(&myself, my_addr);
	show_Address(*my_addr);
	
	while(1){
		ret = receiveMessage(myself, &msg, my_addr);
		/*printf("%d\n", ret);*/
		printf("%s\n", msg);
		free(msg);
	}
}
