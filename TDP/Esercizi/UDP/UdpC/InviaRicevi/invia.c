#include "socket.h"
#include <stdio.h>

int main(int argc, char* argv[]){
	int ret;
	USocket myself;
	Address* my_addr;
	Address* ricevente; 
	
	my_addr = create_Address("0.0.0.0", 8889);
	ret = createSocket(&myself, my_addr);
	
	if(ret < 0) 
		return(-1);

	ricevente = create_Address("0.0.0.0", 8888);
	
	ret = sendMessage(myself, "lol", ricevente);
	
	destroySocket(myself);
	return(0);
}
 
