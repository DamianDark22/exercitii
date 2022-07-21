#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

#define MAX 1024

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, n, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];
	fd_set read_fds, tmp_fds;

	if (argc < 3) {
		usage(argv[0]);
	}

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	ret = inet_aton(argv[1], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");

	FD_SET(STDIN_FILENO, &read_fds);
	FD_SET(sockfd, &read_fds);
	
	char* line = calloc(MAX, sizeof(char));
	if(line == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}
	
	while (1)
	{
		memset(line, 0, MAX);
		fgets(line, MAX - 1, stdin);

		if(strcmp(line, "\n") == 0)
			break;

		line[strlen(line)-1] = '\0';

		memset(buffer, 0, BUFLEN);
		strcpy(buffer, line);

		// se trimite mesaj la server cu numele fisierului
		n = send(sockfd, buffer, strlen(buffer), 0);
		DIE(n < 0, "send");

		memset(buffer, 0, BUFLEN);
		n = recv(sockfd, buffer, BUFLEN, 0);
		DIE(n < 0, "recv");

		if(strncmp(buffer, "Fisierul", 8) != 0){

			char nume[40];
			sprintf(nume, "%s_copy", line);
			FILE* out = fopen(nume, "wt");
			if(out == NULL){
				printf("Problema creare fisier !\n");
				return 0;
			}

			while(strncmp(buffer, "DONE", 4) != 0){
				fprintf(out, "%s", buffer);

				memset(buffer, 0, BUFLEN);
				n = recv(sockfd, buffer, BUFLEN, 0);
				DIE(n < 0, "recv");
			}

			fclose(out);
		}
		else
		{
			printf("%s\n", buffer);
		}
	}

	close(sockfd);

	return 0;
}
