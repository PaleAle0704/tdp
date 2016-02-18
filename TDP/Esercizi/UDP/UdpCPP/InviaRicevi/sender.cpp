#include "socket.hpp"
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]){
		int port;
		SocketUDP* mioSocket;
		Address* dest;
		char* ip;
		char* msg;
		
		if(argc!=3){
			printf("USAGE %s IP PORT MESSAGE\n", argv[0]);
			return(-1);
		}
		
		ip = argv[1];
		port = atoi(argv[2]);
		msg = argv[3];
		
		mioSocket = new SocketUDP();
		dest = new Address(ip, port);
		mioSocket->invia(*dest, msg);
		printf("[%s : %d] %s\n", ip, port, msg);
		//printf("%s\n", strerror(errno));
}
