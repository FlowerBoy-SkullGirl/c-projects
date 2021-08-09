#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLEN 255
	
/*	unsigned int inet_addr(char *str){
		int a, b, c, d;
		char arr[4];
		sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
		arr[0] = a; arr[1] = b, arr[2] = c, arr[3] = d;
		return *(unsigned int *)arr;
	}
*/	
	int main(){
		struct sockaddr_in addrserv;
		int sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		char str[MAXLEN];
		char sended[MAXLEN] = "Hello, server";
		char recieveded[MAXLEN];
		puts("enter ip addr");
		scanf("%s", str);
		
		memset(&addrserv, 0, sizeof(addrserv));		
		addrserv.sin_family = AF_INET;
		addrserv.sin_port = htons(4414);
		addrserv.sin_addr.s_addr = inet_addr(str);
		
		int status = connect(sockid, (struct sockaddr *) &addrserv, sizeof(addrserv));
		
		send(sockid, sended, strlen(sended), 0);
		
		recv(sockid, recieveded, MAXLEN, 0);
		printf("%s", recieveded);

		
		int statusc = close(sockid);

		return 0;
	}
