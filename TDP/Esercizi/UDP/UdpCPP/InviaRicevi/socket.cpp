#define MAX_STR 4096
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
			//struct sockaddr* toCompiledStructure();
}

Address::Address(char* ip, int port){
		this.ip = setIp(ip);
		this.port = setPort(port);
}

Address::~Address(){
		free(this.ip);
}

int Address::getPort(){
		return(this.port);
}

char* Address::getIp(){
		return strdup(this.ip);
}

void Address::setIp(char* ip){
		this.ip = strdup(ip);
}	

void Address::setPort(int port){
		this.port = port;
}



/*Classe SocketUDP*/
class SocketUDP{
	private:
		int sockId;
	public:
		SocketUDP(char* ip, int port);
		~SocketUDP();
		int invia(Address dest, char* msg);
		char* ricevi(Address* mittente);
};

SocketUDP::SocketUDP(char* ip, int port){
		this->sockId = socket(AF_INET, SOCK_DGRAM, 0);					//this è una maniglia all'istanza corrente
		struct sockaddr_in myself;
		myself.sin_family = AF_INET;
		inet_aton(ip, &myself.sin_addr);
		myself.sin_port = htons(port);
		for(int i=0; i<8; i++) myself.sin_zero[i] = 0;
		
		bind(myself, (struct sockaddr*)myself, (socklen_t)sizeof(sockaddr_in));
}

SocketUDP::~SocketUDP(){
		shutdown(this.sockId, SHUT_RDWR);
}

int SocketUDP::invia(Address dest, char* msg){
		struct sockaddr_in addr_dest;
		int len_addr;
		int ret_code;
		int len_message;
		int port_dest;
		char* ip_dest;
		
		//preparo l'indirizzo del destinatario
		addr_dest.sin_family = AF_INET;
		ip_dest = dest.getIp();
		inet_aton(ip_dest, &addr_dest.sin_addr);
		free(ipDest);
		port_dest = dest.getPort();
		addr_dest.sin_port = htons(port_dest);
		for(int i=0; i<8; i++) myself.sin_zero[i] = 0;
		len_addr = sizeof(struct sockaddr);
		len_meddage = strlen(msg)+1;
		ret_code = sendto(this.sockId, msg, len_mesage, 0, (struct sockaddr*)&addr_dest, (socklen_t)len_addr);
		
		return((ret_code == len_message)? 0:-1);
}

char* SocketUDP::ricevi(Address* mittente){
		char* mitt_ip;
		int mitt_port;
		struct sockaddr_in mitt_addr;
		int mit_addr_len;
		int ret_code;
		char* buffer[MAX_STR + 1];
		
		mitt_addr_len = sizeof(struct sockaddr);
		
		ret_code = recvfrom(this->sockId, buffer, MAX_STR, 0, (struct sockaddr*)&mitt_addr, (socklen_t*)&mit_addr_len);
		buffer[ret_code] = '\0';
		
		if(!ret_code) return NULL;
		
		mitt_ip = strdup(intet_ntoa(mitt_addr.sin_addr));
		mit_port = ntohs(mitt_addr.sin_port);
		mittente->setIp(mit_ip);
		mitttente->setPort(mit_port);
		free(mit_ip);
		return(strdup(buffer));
}
