#define MAX_STR 4096
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

/*Classe Address*/
class Address{
		private:	
			char* ip;
			int port;
		public:
			Address();
			Address(char* ip, int port);
			~Address();
			int getPort();
			char* getIp();
			void setIp(char* ip);
			void setPort(int port);
			struct sockaddr_in* toCompiledStructure();
};

Address::Address(){}

Address::Address(char* ip, int port){
		setIp(ip);
		setPort(port);
}

Address::~Address(){
		free(this->ip);
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



/*Classe SocketUDP*/
class SocketUDP{
	private:
		int sockId;
	public:
		SocketUDP();
		SocketUDP(char* ip, int port, bool broadcast);
		~SocketUDP();
		int invia(Address dest, char* msg);
		char* ricevi(Address* mittente);
		void enableBroadcast();
};

SocketUDP::SocketUDP(){
		this->sockId = socket(AF_INET, SOCK_DGRAM, 0);					//this è una maniglia all'istanza corrente
}

SocketUDP::SocketUDP(char* ip, int port, bool broadcast){
		this->sockId = socket(AF_INET, SOCK_DGRAM, 0);					//this è una maniglia all'istanza corrente
		if(broadcast){
			this->enableBroadcast();
		}
		Address* mio = new Address(ip, port);
		printf("IP: %s Port:%d\n", mio->getIp(), mio->getPort());
		sockaddr_in* struttura = mio->toCompiledStructure();
		bind(this->sockId, (struct sockaddr*)struttura, (socklen_t)sizeof(sockaddr_in));
		free(struttura);
}

SocketUDP::~SocketUDP(){
		shutdown(this->sockId, SHUT_RDWR);
}

int SocketUDP::invia(Address dest, char* msg){
		struct sockaddr_in* addr_dest;
		int len_addr;
		int ret_code;
		int len_message;
		
		//preparo l'indirizzo del destinatario
		
		addr_dest = dest.toCompiledStructure();
		len_addr = sizeof(struct sockaddr);
		len_message = strlen(msg)+1;
		ret_code = sendto(this->sockId, msg, len_message, 0, (struct sockaddr*)addr_dest, (socklen_t)len_addr);
		return((ret_code == len_message)? 0:-1);
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

void SocketUDP::enableBroadcast(){
	int broadcastEnable=1;
	int ret=setsockopt(this->sockId, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
}
