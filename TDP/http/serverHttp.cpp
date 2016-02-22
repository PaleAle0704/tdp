#include "Socket.hpp"
#define SERVER_IP "0.0.0.0"
#define HTTP_200 "HTTP/1.0 200 OK\
\
"

#define HTTP_404 "HTTP/1.0 404 Not Found\
\
"

int main(int argc, char* argv[]){
	int port;
	char* home_page;
	ServerTCP* myself;
	Address* my_addr;

	if(argc!=3){ return(-1);}

	port=atoi(argv[1]);
	home_page=argv[2];

	my_addr= new Address(SERVER_IP,port);

	myself = new ServerTCP(my_addr);

	/*Server Http*/
    ConnessioneServer* conn;
    conn = myself->accetta();
    if(conn){
        char* msg;
        msg = conn->ricevi();
        if(msg){
            printf("%s : %d\n", conn->getAddress()->getIp(), conn->getAddress()->getPort());

            FILE* file_home_page;
            file_home_page = fopen(home_page, "r");
            if(!file_home_page){
                conn->invia(HTTP_404);
            }else{
                conn->invia("HTTP/1.0 200 OK\n\n");
                conn->invia(file_home_page);    //va implementato, legge il file e lo spedisce
                fclose(file_home_page);
            }

//            myself->chiudi(conn);               //va implementato, elimina la connessine dalla lista e poi chiama il distruttore di connessiones
        }
    }

	delete(myself);
	delete(my_addr);
	return(0);
}