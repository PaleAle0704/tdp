#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

/*
* Gestione dell'indirizzo
*/
typedef struct sockaddr_in Address;
/*
Address* create_Address(char* ip, int port);
void destroy_Address(Address* a);
char* get_ip(Address a);
int get_port(Address a);
void set_ip(Address* a, char* ip);
void set_port(Address* a, int port);
void show_Address(Address a);

int main(int argc, char* argv){
	char* ip={"192.168.0.33\0"};
	int port = 12;
	Address* a;
	
	a = create_Address(ip, port);
	show_Address(*a);
	destroy_Address(a);
	
	return(0);
}*/

Address* create_Address(char* ip, int port){
	Address* a;
	int i;

	a = (Address*)malloc(sizeof(Address));
	a->sin_family = AF_INET;
	inet_aton(ip, &a->sin_addr);					/* la freccia ha priorità sulla & */
	a->sin_port = htons(port);
	for(i=0; i<8; i++) a->sin_zero[i] = 0;

	return (a);
}

void destroy_Address(Address* a){
	free(a);
}

char* get_ip(Address a){
	char* str;
	
	str = strdup(inet_ntoa(a.sin_addr));
	return(str);
}

int get_port(Address a){
	int port;
	
	port = ntohs(a.sin_port);
	
	return(port);
}

void set_ip(Address* a, char* ip){
	inet_aton(ip, &a->sin_addr);
}

void set_port(Address* a, int port){
	a->sin_port = htons(port);
}

void show_Address(Address a){
	printf("Ip : Port\t%s : %d\n", get_ip(a), get_port(a));
}


/*
* Gestione UDP
*/

#define MAX_LENGTH 4095
typedef int USocket;

/*Funione che crea un socket, restituisce 0 se la creazione termina correttamente, -1 se si presentano errori in fase di creazione e -2 se si presentano errori in fase di binding*/
int createSocket(USocket* mySock, Address* mittente){
	if((mySock = socket(AF_INET, SOCK_DGRAM, 0))== -1) 
		return(-1);
	if(bind(myself, (struct sockaddr*)myAddr, (socklen_t)sizeof(Address))) 
		return(-2);
	
	return 0;
}

int receiveMessage(USocket mySock, char* msg, Address* mittente){
	int ret, len:;
	char buffer[MAX_LENGTH];
	
	len_addr = sizeof(Address);
	ret = recvfrom(myself, buffer, MAX_LENGTH, 0, (struct sockaddr*)mittente, (socklen_t*)&len_addr);
	buffer[ret] = '/0';
	msg = strdup(buffer);
	
	return ret;
}

int sendMessage(USocket mySock, char* msg, Address* ricevente){
	return sendto(mySock, msg, strlen(msg)+1, 0, (struct sockaddr*)ricevente, (socklen_t)sizeof(Address));
}

void destroySocket(USocket mySock){
	shutdown(mySock, SHUT_RDWR);
}