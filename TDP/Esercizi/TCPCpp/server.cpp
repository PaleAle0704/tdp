#include "Socket.hpp"
#define SRV_IP "0.0.0.0"
#define PORT 8989

int main(){
    Address* mio;
    ServerTCP* mySelf;
    ConnessioneServer* cl;
    char* msg;

    mio = new Address(SRV_IP, PORT);
    printf("ciao");
    mySelf = new ServerTCP(mio);
    cl = mySelf->accetta();
    msg = cl->ricevi();

    printf("%s\n", msg);

    mySelf->~ServerTCP();

    return 0;
}
