#include "Socket.hpp"
#define IP_SRV "0.0.0.0"

int main(int argc, char* argv[]){
    Address* srv;
    ClientTCP* cl;
    ConnessioneClient* connCli;
    int port;
    char* message /*= (char*)malloc(sizeof(char)*6)*/;

    if(argc != 3) {
        printf("USAGE %s PORT MESSAGE\n", argv[0]);
        return (-1);
    }

    port = atoi(argv[1]);
    message = argv[2];
    printf("%s\n", message);

    srv = new Address(IP_SRV, 8989);
    cl = new ClientTCP();
    cl->connetti(*srv);

    cl->invia(message);

    return 0;
}
