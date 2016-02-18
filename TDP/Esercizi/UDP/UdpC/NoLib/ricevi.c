#include "socket.h"
#include <stdio.h>
#define MAX_LENGTH 4095

int main(int argc, char* argv[]){
	char buffer[MAX_LENGTH+1];
	int myself, ret, len_addr;
	Address* my_addr;
	Address* ricevente;
	
	myself = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(myself == -1) return(-1);
	my_addr = create_Address("0.0.0.0", 8889);
	if(bind(myself, (struct sockaddr*)my_addr, (socklen_t)sizeof(Address))) return(-2);
	len_addr = sizeof(Address);
	ricevente = create_Address("0.0.0.0", 8888);
	char msg[]={"ciao\n"};
	ret = sendto(myself, msg, strlen(msg)+1, 0, (struct sockaddr*)ricevente, (socklen_t)sizeof(Address));	
	
	shutdown(myself, SHUT_RDWR);
	return(0);
}
