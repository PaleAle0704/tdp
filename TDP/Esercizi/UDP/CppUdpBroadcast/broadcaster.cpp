#include "socket.hpp"
#include <pthread.h>
#include <cstring>

#define IP_MYSELF "0.0.0.0"
#define EXIT_CMD "exit"
#define IP_BROADCAST "255.255.255.255"
int port;

/*La versione del prof crea due thread e passa loro come parametro una maniglia al socket*/
void* lettore(void* p);
void* scrittore(void* p);
char* leggi_stringa(char *);
int cmpstr(char *s1, char *s2);

int main(int argc, char* argv[]){
		pthread_t scrivi, leggi;
		SocketUDP* mySelf;
				
		if(argc!=2){
			printf("USAGE %s PORT\n", argv[0]);
			return(-1);
		}
		
		port = atoi(argv[1]);
		mySelf = new SocketUDP(IP_MYSELF, port, false);
		mySelf->enableBroadcast();
		
		pthread_create(&leggi, NULL, lettore, (void *)mySelf);		
		pthread_create(&scrivi, NULL, scrittore, (void *)mySelf);	

		pthread_join(scrivi, NULL);
		
		delete(mySelf);
		
		return(0);
}

void* lettore(void* p){
		SocketUDP* mioSocket;
		Address* mit;
		char* msg;
		char* ipMit;
		
		mioSocket = (SocketUDP*)p;
		mit = new Address();
		
		while(1){		
			msg = mioSocket->ricevi(mit);
			if(msg){
				printf("[%s:%d] %s\n", (ipMit=mit->getIp()), mit->getPort(), msg);
				fflush(stdout);	
			}
			free(msg);
			free(ipMit);
		}
		
		free(mit);
}

void* scrittore(void* p){
		SocketUDP* mioSocket;
		Address* dest;
		char* msg;
		char keyboardInput[4096];
		
		mioSocket = (SocketUDP*)p;
		dest = new Address(IP_BROADCAST, port);
		
		while(cmpstr(msg = leggi_stringa(keyboardInput), EXIT_CMD)){
			mioSocket->invia(*dest, msg);
		}
		
		pthread_exit(NULL);
}


/* Funzione che legge una stringa */
char* leggi_stringa(char *buffer){
	char c;
	int i;

	i = 0;
	/*scorro la stringa carattere per carattere*/
	while((c=getchar()) != '\n'){
		/*printf("%c", c);*/
		buffer[i] = c;
		i++;
	}

	buffer[i] = '\0';

	return buffer;
}

/*Funzione per la comparazione delle stringhe*/

int cmpstr(char *s1, char *s2){
	if(*s1 > *s2) return(-1);
	if(*s1 < *s2) return(1);
	if(*s1) return(cmpstr(++s1, ++s2));
	return 0;
}
