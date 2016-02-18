#include "socket.hpp"

int main(int argc, char* argv[]){
		int port;
		SocketUDP* mioSocket;
		Address* mit;
		char* msg;
		char ip[]={"0.0.0.0"};
		
		if(argc!=2){
			return(-1);
		}
		
		port = atoi(argv[1]);
		mioSocket = new SocketUDP(ip, port);
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
		
		return(0);
}
