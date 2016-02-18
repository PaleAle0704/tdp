#include "socket.h"
#include <stdio.h>

int main(int argc, char* argv[]){
	int ret, port;
	char* msg;
	USocket myself;
	Address* my_addr;
	Address* ricevente; 
	
	if(argc != 3){
		printf("USAGE %s PORT MESSAGE\n", argv[0]);
		return(-1);
	}	
	
	port = atoi(argv[1]);
	msg = argv[2];
	my_addr = create_Address("0.0.0.0", 7777);
	ret = createSocket(&myself, my_addr);
	
	if(ret < 0) 
		return(-1);

	ricevente = create_Address("0.0.0.0", port);	
	ret = sendMessage(myself, msg, ricevente);
	
	destroySocket(myself);
	return(0);
}
 
