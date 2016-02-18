#include "socket.h"
#include <stdio.h>
#include <errno.h>
#define MAX_LENGTH 4095

int main(int argc, char** argv){
	char buffer[MAX_LENGTH+1];
	int myself, ret, len_addr;
	Address* my_addr;
	Address mittente;
	
	myself = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(myself == -1) return(-1);
	my_addr = create_Address("0.0.0.0", 8888);
	if(bind(myself, (struct sockaddr*)my_addr, (socklen_t)sizeof(Address))) return(-2);
	len_addr = sizeof(Address);
	
	ret = recvfrom(myself, buffer, MAX_LENGTH, 0, (struct sockaddr*)&mittente, (socklen_t*)&len_addr);
	
	printf("%d\n", ret);
	fflush(stdout);
	buffer[ret] = '\0';
	printf("%s\n", buffer);
	printf("%s\n", errno);
	
	shutdown(myself, SHUT_RDWR);
	return(0);
}
