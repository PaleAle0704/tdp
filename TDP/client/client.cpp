#include "Socket.hpp"
#define HTTP_200 "HTTP/1.0 200 OK\
\
"
#define HTTP_REQUEST "GET /root HTTP/1.1\
\
"

void errore(char* msg, int ret_code){
    printf("ERROR:%s\n", msg);
    printf("%d:%s\n", errno, strerror(errno));
    printf("Returning %d to system\n", ret_code);
    //il programma viene interrotto, restituisce ret_code al sistema
    exit(ret_code);
}

int main(int argc, char* argv[]){
	int port;
	ClientTCP* myself;
	Address* server;
	char* ip, *answer;

	if(argc!=3){
        printf("USAGE %s PORT IP\n", argv[0]);
        return(-1);
    }

	port=atoi(argv[1]);
	ip=argv[2];

	myself = new ClientTCP();
	if(!myself->connetti(server = new Address(ip, port))) errore("Aaaaarg!!\n", -2);
    if(!myself->invia(HTTP_REQUEST)) errore("Uuuuuuugh!!\n", -3);

    answer = myself->ricevi();
    if(!answer) errore("Oioioioioi!!\n", -4);
    printf("%s\n", answer);
    if(!strstr(answer, ANS_200OK)) errore("Buahhhhhh!!\n", -5);
    free(answer);
    if(!answer = myself->ricevi()) errore("Waaaaaaah!!\n", -6);
    printf("%s\n", answer);

    delete(myself);
    delete(server);

    printf("*risata malefica*\n");

	return(0);
}
