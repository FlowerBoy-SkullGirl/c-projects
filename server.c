#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#define WAITERS 1

	int main(){
		struct sockaddr_in addrport, addrcli;
		int sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		char sender[255] = "Passing information is easy";
		char getter[255];
		int s; 
		
		puts("Socket created..");
		
		addrport.sin_family = AF_INET;
		addrport.sin_port = htons(4414);
		addrport.sin_addr.s_addr = htonl(INADDR_ANY);
		
		memset(&addrcli, 0, sizeof(addrcli));
		addrcli.sin_family = AF_INET;
		addrcli.sin_port = htons(INADDR_ANY);
		addrcli.sin_addr.s_addr = htonl(INADDR_ANY);
	
		if(bind(sockid, (struct sockaddr *) &addrport, sizeof(addrport))!= -1) {
			puts("Socket bound..");
			
			
			int status = listen(sockid, WAITERS);
			for( ; ;){
				socklen_t clilen = sizeof(addrcli);		
				s = accept(sockid, (struct sockaddr *) &addrcli, &clilen);
				puts("Connection established..");
				
				recv(s, getter, 255, 0);
				printf("%s", getter);

				send(s, sender, strlen(sender), 0);
			}

			int statusc = close(sockid);
			close(s);
		}
	
		return 0;
	}
