
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
//#include "lista.hpp"

#define MAX_CONNECTIONS 1
#define MAX_STR 4096
typedef enum{UDP=SOCK_DGRAM, TCP=SOCK_STREAM} Protocollo;

/*Classe Nodo*/
class Nodo{
	private:
		Nodo* next;
	public:
		Nodo();
		Nodo* getNext();
		void setNext(Nodo* prossimo);
		virtual void* show(){};
		virtual void* getKey() = 0;
		~Nodo();
};

/*Classe Lista, collezione di Nodo*/
class Iterator;
class Lista{
    private:
        Nodo* first;
        void show(Nodo* n);
        void deleteAll(Nodo* n);
    public:
        Lista();
        ~Lista();
        void add(Nodo* n);
        void show();
		Nodo* getFirst();
		Iterator* createIterator();
};


/*Classe Iterator*/
class Iterator{
	private:
		Lista* lista;
		Nodo* current;
	public:
		Iterator(Lista* l);
		~Iterator();
		Nodo* goFirst();
		Nodo* moveNext();
		Nodo* getCurrent();
		bool isDone();
};

/*Classe Address*/
class Address{
		private:
			char* ip;
			int port;
		public:
			Address();
			Address(char* ip, int port);
			Address(Address& address);			//per copia
			Address(Address* address);
			~Address();
			int getPort();
			char* getIp();
			void setIp(char* ip);
			void setPort(int port);
			struct sockaddr_in* toCompiledStructure();
			char* to_string();
};

/*Classe Socket*/
class Socket{
	protected:
		int sockId;
		Socket(Protocollo protocollo, Address* a = NULL);	//secondo parametro facoltativo, socket() bind()
	public:
		Socket();
		~Socket();
		void enableBroadcast();
};

/*Classe SocketUDP*/
class SocketUDP:public Socket{
	public:
		SocketUDP();
		SocketUDP(Address* mio);
		bool invia(char* msg, Address dest);	//sendto()
		char* ricevi(Address* mittente);		//recv()
		~SocketUDP();							//shutdown()
};

/*Classe SocketTCP, eredita da Socket*/
class SocketTCP:public Socket{
    protected:
		SocketTCP();
		SocketTCP(Address* mio);
		~SocketTCP();
};


/*Classe ClientTCP, eredita da SocketTCP*/
class ConnessioneClient;
class ClientTCP:public SocketTCP{
    private:
        ConnessioneClient* conn;
    public:
        ClientTCP();    /*forse devo aggiungerne una a cui passo l'indirizzo*/
        ConnessioneClient* connetti(Address server);		//connect()
		bool invia(char* msg);
		char* ricevi();
		~ClientTCP();
};

/*Classe ServerTCP, eredita da SocketTCP*/
class Lista;
class ConnessioneServer;
class Iterator;
class ServerTCP:public SocketTCP{
    private:
        Lista* connessioni;
    public:
        ServerTCP(Address* mio);						//listen()
        ConnessioneServer* accetta();	//accept()
		Iterator createIterator();
		~ServerTCP();
};

/*Classe connessione*/
class Connessione{
    private:
        int conn_id;
        Address indirizzo;
	protected:
        Connessione();
		Connessione(int conn, Address ind);
		~Connessione();
    public:
        bool invia(char* msg);	//send()
        char* ricevi();			//recv()
		Address* getAddress();
};

/*Classe ConnessioneClient*/
class ConnessioneClient:public Connessione{
	public:
        ConnessioneClient();
		ConnessioneClient(int sock_id, Address indirizzo);
};

/*Classe ConnessioneServer, eredita da Nodo e Connessione*/
class Nodo;
class ConnessioneServer:public Nodo, public Connessione{
	public:
        ConnessioneServer(int conn_id, Address indirizzo);
        void* getKey();
		~ConnessioneServer();			//close()
};

/**********************************************************/
/**************  IMPLEMENTAZIONE DEI METODI  **************/
/**********************************************************/


/**********************************************************/
/***********************  Address  ************************/
/**********************************************************/

Address::Address(){}

Address::Address(Address& address) {
    this->ip = address.getIp();
    this->port = address.port;
}

Address::Address(Address* address){
    this->ip = address->getIp();
    this->port = address->getPort();
}

Address::Address(char* ip, int port){
		setIp(ip);
		setPort(port);
}

Address::~Address(){
		free(this->ip);                         /*è qui che va in core dump*/
}

int Address::getPort(){
		return(this->port);
}

char* Address::getIp(){
		return strdup(this->ip);
}

void Address::setIp(char* ip){
		this->ip = strdup(ip);
}

void Address::setPort(int port){
		this->port = port;
}

struct sockaddr_in* Address::toCompiledStructure(){
	struct sockaddr_in* strutturaCompilata;

	strutturaCompilata = (sockaddr_in*)malloc(sizeof(sockaddr));
	strutturaCompilata->sin_family = AF_INET;
	inet_aton(this->ip, &strutturaCompilata->sin_addr);
	strutturaCompilata->sin_port = htons(this->port);
	for(int i=0; i<8; i++) strutturaCompilata->sin_zero[i] = 0;

	return(strutturaCompilata);
}

char* Address::to_string(){
    printf("Ip : %s Port : %d\n", this->getIp(), this->getPort());
}



/**********************************************************/
/************************  Socket  ************************/
/**********************************************************/
Socket::Socket(){}

Socket::Socket(Protocollo protocollo, Address* a){
    int rebind = 1;
    this->sockId = socket(AF_INET, protocollo, 0);
    if(a){
        printf("IP: %s Port:%d\n", a->getIp(), a->getPort());
        sockaddr_in* struttura = a->toCompiledStructure();
        /*Per poter rifare il bind dopo breve tempo con il tcp, devo forza il meccanismo con SO_REUSEADDR*/
        if(protocollo == TCP) setsockopt(this->sockId, SOL_SOCKET, SO_REUSEADDR, &rebind, sizeof(rebind));

        if(bind(this->sockId, (struct sockaddr*)struttura, (socklen_t)sizeof(sockaddr_in)) == -1) printf("%s", strerror(errno));
        fflush(stdout);
        free(struttura);
    }
}

Socket::~Socket(){
    shutdown(this->sockId, SHUT_RDWR);
}

void Socket::enableBroadcast(){
    int enableBroadcast = 1;
    setsockopt(this->sockId, SOL_SOCKET, SO_BROADCAST, &enableBroadcast, sizeof(enableBroadcast));
}


/**********************************************************/
/**********************  SocketUDP  ***********************/
/**********************************************************/

SocketUDP::SocketUDP(Address* mio):Socket(UDP, mio) { }

SocketUDP::~SocketUDP(){}

bool SocketUDP::invia(char* msg, Address dest){
		struct sockaddr_in* addr_dest;
		int len_addr;
		int ret_code;
		int len_message;
		bool riuscito = false;

		//preparo l'indirizzo del destinatario

		addr_dest = dest.toCompiledStructure();
		len_addr = sizeof(struct sockaddr);
		len_message = strlen(msg)+1;
		ret_code = sendto(this->sockId, msg, len_message, 0, (struct sockaddr*)addr_dest, (socklen_t)len_addr);

		if(ret_code > 0) riuscito = true;

		return (riuscito);
}

char* SocketUDP::ricevi(Address* mittente){
		char* mitt_ip;
		int mitt_port;
		struct sockaddr_in mitt_addr;
		int mitt_addr_len;
		int ret_code;
		char buffer[MAX_STR + 1];

		mitt_addr_len = sizeof(struct sockaddr);

		ret_code = recvfrom(this->sockId, buffer, MAX_STR, 0, (struct sockaddr*)&mitt_addr, (socklen_t*)&mitt_addr_len);
		buffer[ret_code] = '\0';

		if(!ret_code) return NULL;

		mitt_ip = strdup(inet_ntoa(mitt_addr.sin_addr));
		mitt_port = ntohs(mitt_addr.sin_port);
		mittente->setIp(mitt_ip);
		mittente->setPort(mitt_port);
		free(mitt_ip);

		return(strdup(buffer));
}

/**********************************************************/
/**********************  SocketTCP  ***********************/
/**********************************************************/
SocketTCP::SocketTCP():Socket(TCP){}

SocketTCP::SocketTCP(Address* mio):Socket(TCP, mio){}

SocketTCP::~SocketTCP(){};


/**********************************************************/
/**********************  ClientTCP  ***********************/
/**********************************************************/

ClientTCP::ClientTCP():SocketTCP(){}

ClientTCP::~ClientTCP(){}

ConnessioneClient* ClientTCP::connetti(Address server){
    struct sockaddr_in* ind_srv;

    ind_srv = server.toCompiledStructure();
    connect(this->sockId, (struct sockaddr*)ind_srv, (socklen_t)sizeof(sockaddr));
    this->conn = new ConnessioneClient(this->sockId, server);
    return conn;
}

bool ClientTCP::invia(char* msg){
    this->conn->invia(msg);
}

char* ClientTCP::ricevi(){
    return this->conn->ricevi();
}

/**********************************************************/
/**********************  ServerTCP  ***********************/
/**********************************************************/

ServerTCP::ServerTCP(Address* mio):SocketTCP(mio){
    this->connessioni = new Lista();
    listen(this->sockId, MAX_CONNECTIONS);
}

ServerTCP::~ServerTCP(){
    this->connessioni->~Lista();
}

ConnessioneServer* ServerTCP::accetta(){
    int conn_id;
    int str_length = sizeof(struct sockaddr);
    ConnessioneServer* c;
    Address* indRichiedente = new Address("", 0);

    conn_id = accept(this->sockId, (struct sockaddr*)indRichiedente->toCompiledStructure(), (socklen_t*)&str_length);
    c = new ConnessioneServer(conn_id, *indRichiedente);
    this->connessioni->add(c);
    return c;
}

Iterator ServerTCP::createIterator(){
	this->connessioni->createIterator();
}

/**********************************************************/
/**********************  Connessione  *********************/
/**********************************************************/
Connessione::Connessione(){}

Connessione::Connessione(int conn, Address ind){
    this->indirizzo = ind;
    this->conn_id = conn;
}

bool Connessione::invia(char* msg){
    send(this->conn_id, msg, strlen(msg), 0);
}

char* Connessione::ricevi(){
    char buffer[4096]; char* msg;
    int n = recv(this->conn_id, &buffer, 4095, 0);
    printf("byte %d\n", n);
    printf("%s\n", strerror(errno));
    fflush(stdout);

    msg = strdup(buffer);
    return msg;
}

Address* Connessione::getAddress(){
	return(&(this->indirizzo));
}

/**********************************************************/
/******************  ConnessioneClient  *******************/
/**********************************************************/

ConnessioneClient::ConnessioneClient():Connessione(){}

ConnessioneClient::ConnessioneClient(int conn, Address ind):Connessione(conn, ind){}

/**********************************************************/
/******************  ConnessioneServer  *******************/
/**********************************************************/

ConnessioneServer::ConnessioneServer(int conn_id, Address indirizzo):Connessione(conn_id, indirizzo){}

void* ConnessioneServer::getKey(){
    return (void*)new Address(this->getAddress());
}

/**********************************************************/
/**************************  Nodo *************************/
/**********************************************************/

Nodo* Nodo::getNext(){
	return(this->next);
}

void Nodo::setNext(Nodo* prossimo){
	this->next = prossimo;
}

Nodo::Nodo(){}

Nodo::~Nodo(){}


/**********************************************************/
/**************************  Lista ************************/
/**********************************************************/

Lista::Lista(){}

void Lista::show(Nodo* n){
    if(n){
        n->show();
        show(n->getNext());
    }
}

Lista::~Lista(){
    this->deleteAll(this->first);
}

void Lista::show(){
    this->show(this->first);
}

void Lista::deleteAll(Nodo* n){
    if(!n)return;
    deleteAll(n->getNext());
    n->~Nodo();
}

void Lista::add(Nodo* n){
    n->setNext(first);
    first = n;
}

Nodo* Lista::getFirst(){
	return(this->first);
}

Iterator* Lista::createIterator(){
	return(new Iterator(this));
}

/**********************************************************/
/************************ Iterator ************************/
/**********************************************************/

Iterator::Iterator(Lista* l){
	this->lista = l;
}

Nodo* Iterator::goFirst(){
	return(this->current = this->lista->getFirst());
}

Nodo* Iterator::moveNext(){
	return(this->current = this->current->getNext());
}

Nodo* Iterator::getCurrent(){
	return(this->current);
}

bool Iterator::isDone(){
    bool finito = false;
    Nodo* n = this->current->getNext();
    if(!n) finito = true;
	return finito;
}
