#include "socket.hpp"
#include <pthread.h>

void* srv(void* p);

int main(int argc, char* argv[]){
		pthread_t server;
		int port;
				
		if(argc!=2){
			printf("USAGE %s PORT\n", argv[0]);
			return(-1);
		}
		
		port = atoi(argv[1]);
		pthread_create(&server, NULL, srv, (void *)&port);		
		
		getchar();
		
		return(0);
}

void* srv(void* p){
		SocketUDP* mioSocket;
		Address* mit;
		char* msg;
		char ip[]={"0.0.0.0"};
		int port;
		
		port = *(int*)p;
		mioSocket = new SocketUDP(ip, port, true);
		
		while(1){		
			mit = new Address();
			msg = mioSocket->ricevi(mit);
			if(msg){
				printf("%s", msg);
				fflush(stdout);	
			}
			mit->~Address();
			free(msg);
		}
		
		mioSocket->~SocketUDP();
}
