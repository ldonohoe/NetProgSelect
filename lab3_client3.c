#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#include "lib/unpv13e/lib/unp.h"

int
main(int argc, char **argv)
{   
    /*
	int					sockfd;
	struct sockaddr_in	servaddr;
	char* address = "127.0.0.1";
	int port = 9881;

	//if (argc != 2)
	//	err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);//SERV_PORT);
	Inet_pton(AF_INET, address, &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	

	int shouldClose;
    */

    char recvline[MAXLINE];

    int numSock = 6;
    int numUsed = 1;
    int serverSockets[numSock];
    int serverPorts[numSock];

    fd_set readfds;

    for (int i = 0; i < numSock; i++) {
        serverSockets[i] = 0;
        serverPorts[i] = 0;
    }

    FD_SET(0, &readfds);

    int n;

	for (; ;) {

        //FD_ZERO(&serverSockets);
        int maxfds = 0;

        for (int i = 0; i < numSock; i++) {
            FD_SET(serverSockets[i], &readfds);
            maxfds = max(maxfds, serverSockets[i]);
        }

        select(maxfds+1, &readfds, NULL, NULL, NULL);


        for (int i = 0; i < numSock; i++) {
            if (FD_ISSET(serverSockets[i], &readfds)) {  /* socket is readable */

                if (serverSockets[i] != 0){

                    printf("Made it before");

                    if ( (n = Read(serverSockets[i], recvline, MAXLINE)) == 0) {
                        err_quit("server terminated prematurely");
                    }

                    printf("Made it here");
                    printf("%s\n", recvline);
                    fflush(stdout);

                    FD_SET(serverSockets[i], &readfds);

                }else{
                    printf("In the else statement");
                    if ( (n = Read(serverSockets[i], recvline, MAXLINE)) == 0) {
                        err_quit("server terminated prematurely");
                    }

                    if (n == 0) {
                        printf("Port closed\n");
                    }else{
                        int                 sockfd;
                        struct sockaddr_in  servaddr;
                        char* address = "127.0.0.1";
                        int port = atoi(recvline);

                        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

                        bzero(&servaddr, sizeof(servaddr));
                        servaddr.sin_family = AF_INET;
                        servaddr.sin_port = htons(port);//SERV_PORT);
                        Inet_pton(AF_INET, address, &servaddr.sin_addr);

                        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
                        serverSockets[numUsed] = sockfd;
                        serverPorts[numUsed] = port;
                        numUsed += 1;

                        FD_SET(sockfd, &readfds);
                    }
                    //printf("%s\n", recvline);
                }
            }

        }


        /*
		//Readline(sockfd, recvline, MAXLINE);
		shouldClose = recv(sockfd, recvline, MAXLINE, 0);

		//Fputs(recvline, stdout);
		//printf("Hi there\n");
		printf("%s\n", recvline);
		fflush(stdout);

		if (shouldClose == 0){
			err_quit("server terminated prematurely");
		}
        */
		//if (Readline(sockfd, recvline, MAXLINE) == 0) {
		//	err_quit("str_cli: server terminated prematurely");
		//}

		
		
		
		
	}

	exit(0);
}




//int clientSelect(char **ipAddr ,int port , int count)

/*
int main(int argc, char *argv[])
{   

    char *ipAddr = "127.0.0.1";
    int port = 9881;
    int count = 5;

    SOCKET max_sd = 0;
    SOCKET socketId[10] = {0};
    SOCKET sd = 0 ;

    fd_set readfds;
    int i ,j , ret;
    char recvBuf[1024] = "";
    char errMsg[256] = "" ;
    struct sockaddr_in server ;

    // Socket Initialization
    for(i = 0; i<count ; i++) {
        ret = initSocket(&socketId[i]);//Small function to create socket
        if (ret != 1)
        {
            return ret ;
        }
        //Server info
        server.sin_addr.s_addr  = inet_addr(ipAddr[i]);
        server.sin_family       = AF_INET;
        server.sin_port         = htons(port);
        // Conect to server
        if (connect(socketId[i], (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            printf("connect ::Failed to connect to server %s:%d",ipAddr[i],port);
            return -1;
        }       
    }


    while(1)
    {
        // init fd_set
        FD_ZERO(&readfds); // added by siva to initialize socket descriptors
        for(i = 0; i<count ; i++)
        {
            //FD_ZERO(&readfds); // Commented by siva to avoid initialization for each socket
            FD_SET(socketId[i], &readfds); 
            max_sd = (max_sd>socketId[i])?max_sd:socketId[i];
        }
        ret = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            printf("select failed\n ");
            return -1;
        }
        // warning: you don't know the max_sd value
        for(i = 0; i<count ; i++)
        {
            sd = socketId[i] ;
            if (FD_ISSET(sd, &readfds)) 
            {
                ret = recv(sd,(char *)recvBuf,sizeof(recvBuf), 0);
                if(ret > 0 )
                {
                    printf("Message received from socket %d : %s\n",sd,recvBuf);
                    send(sd,(char *)recvBuf,strlen(recvBuf),0);
                }
            }
        }
    }

    return ret ;

}
*/