#include	"lib/unpv13e/lib/unp.h"

int
main(int argc, char **argv)
{
	/*
	int					sockfd;
	struct sockaddr_in	servaddr;

	//if (argc != 2)
	//	err_quit("usage: udpcli <IPaddress>");
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9881);//SERV_PORT);
	//Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	Inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

	exit(0);
	*/

	/*
	const char* server_name = "127.0.0.1";
	const int server_port = argv[1];

	struct sockaddr_in	servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	// creates binary representation of server name
	// and stores it as sin_addr
	Inet_pton(AF_INET, server_name, &servaddr.sin_addr);

	// htons: port in network order format
	server_address.sin_port = htons(server_port);

	// open a stream socket
	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
	}

	// TCP is connection oriented, a reliable connection
	// **must** be established before any data is exchanged
	if (connect(sock, (struct sockaddr*)&server_address,
	            sizeof(server_address)) < 0) {
		printf("could not connect to server\n");
		return 1;
	}

	// send

	// data that will be sent to the server
	const char* data_to_send = "connect";
	send(sock, data_to_send, strlen(data_to_send), 0);

	// receive

	int n = 0;
	int len = 0, maxlen = 100;
	char buffer[maxlen];
	char* pbuffer = buffer;

	// will remain open until the server terminates the connection
	while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
		pbuffer += n;
		maxlen -= n;
		len += n;

		buffer[len] = '\0';
		printf("received: '%s'\n", buffer);
	}

	// close the socket
	close(sock);
	return 0;
	*/
	/*
	int					sockfd;
	struct sockaddr_in	servaddr;
	char* localhost = "127.0.0.1";
	int port = 9881;

	//if (argc != 2)
	//	err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	Inet_pton(AF_INET, localhost, &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	//str_cli(stdin, sockfd);		
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (1) {

		//Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}

	exit(0);
	*/
	int					sockfd;
	struct sockaddr_in	servaddr;
	char* localhost = "127.0.0.1";

	//if (argc != 2)
	//	err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, localhost, &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);



}
