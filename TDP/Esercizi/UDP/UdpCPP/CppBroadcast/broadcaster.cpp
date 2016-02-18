#include "socket.hpp"
#include <pthread.h>
#include <cstring>

void* srv(void* p);

int main(int argc, char* argv[]){
		pthread_t server;
		int port;
		SocketUDP* mioSocket;
		Address* dest;
		char* msg;
				
		if(argc!=2){
			printf("USAGE %s PORT\n", argv[0]);
			return(-1);
		}
		
		port = atoi(argv[1]);
		pthread_create(&server, NULL, srv, (void *)&port);		

		mioSocket = new SocketUDP("0.0.0.0", 5555, true);
		dest = new Address("255.255.255.255", port);
		while(42){
			getchar();
			mioSocket->invia(*dest, "ciao");
			/*mioSocket->invia(*dest, msg);*/
		}
		
		
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
