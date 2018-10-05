#include	"lib/unpv13e/lib/unp.h"

int
main(int argc, char **argv)
{
	/*
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	int addToPort;
	sscanf(argv[1], "%d", &addToPort);
	printf("The number to be added is %d\n", addToPort);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT + addToPort);

	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	//dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));



	//int			n;
	//socklen_t	len;
	//char		mesg[MAXLINE];

	char sendString[100];



	for ( ; ; ) {
		//len = clilen;
		//n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		scanf("%s", sendString);
		//fgets(sendString, 100, stdin);

		printf("%s\n", sendString);

		//Sendto(sockfd, mesg, n, 0, pcliaddr, clilen);
	}
	*/
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	clilen = sizeof(cliaddr);
	connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

	char sendString[100];

	for ( ; ; ) {
		
		scanf("%s", sendString);
		//printf("%s\n", sendString);
		//write(connfd, sendString, sizeof(sendString));
		//sendto(connfd, sendString, sizeof(sendString));
		int i = 0;
		printf("The length is %lu\n", strlen(sendString));
		for (i = 0; i < strlen(sendString); i++) {
			printf("%c\n", sendString[i]);
		}

		//printf("test\n");
		//if ( (childpid = Fork()) == 0) {	/* child process */
		//Close(listenfd);	/* close listening socket */
		//str_echo(connfd);	/* process the request */
		//Writen(connfd, "This is a test");
		//exit(0);
		//}
		//Close(connfd);			/* parent closes connected socket */
	}


}
