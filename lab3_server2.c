#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#include "lib/unpv13e/lib/unp.h"

/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t n) {
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;   /* and call write() again */
			else
				return (-1);/* error */
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}

int main(int argc, char *argv[]) {



	int port_num = 9877 + atoi(argv[1]);

	printf("%d\n", port_num);

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_port = htons(port_num);

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int lsock;
	if ((lsock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("could not create listen socket\n");
		return 1;
	}

	if ((bind(lsock, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
		perror("failed binding socket\n");
		return 1;
	}

	if (listen(lsock, 1) < 0) {
		perror("failed to open socket for listening\n");
		return 1;
	}



	struct sockaddr_in cliaddr;
	int clilen = 0;

	int eof=0;
	while(!eof) {
		int s;
		if ((s = accept(lsock, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
			perror("unable to open socket to accept data\n");
			return 1;
		}
		printf("Accepted connection\n");

		int n = 0;
		char buffer[MAXLINE];

		char message[MAXLINE];
		int f;
		while((f = scanf("%s", message))) {
			if (f == EOF) {
				eof = 1;
				break;
			}
			writen(s, (char *)message, strlen(message));
		}


		close(s);
	}
	printf("Shutting down due to EOF\n");
	close(lsock);
	return 0;
}