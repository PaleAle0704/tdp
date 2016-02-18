#include "socket.h"
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]){
	char* msg;
	USocket myself;
	int ret;
	Address* my_addr;
	
	my_addr = create_Address("0.0.0.0", 8888);
	ret = createSocket(&myself, my_addr);
	show_Address(*my_addr);
	
	if(ret <0) 
		return(-1);

	ret = receiveMessage(myself, &msg, my_addr);
	
	printf("%d\n", ret);
	
	printf("%s\n", msg);
	free(msg);
	destroySocket(myself);
	return(0);
}
