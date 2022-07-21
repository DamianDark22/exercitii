#include <mqueue.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "utils.h"
 
 
/* Set buffer size at least the default maxim size of the queue
  * found in/proc/sys/kernel/msgmax */
#define BUF_SIZE 	8192
#define TEXT		"test message"
#define NAME		"/server_q"
#define MAX 1024
 
int main(int argc, char **argv)
{
	unsigned int prio = 10;
	int rc;
	mqd_t server_q, client_q;

	char* line = calloc(MAX, sizeof(char));
	if(line == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}

	char* buf_send = calloc(BUF_SIZE, sizeof(char));
	if(buf_send == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}

	char* buf = calloc(BUF_SIZE, sizeof(char));
	if(buf == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}
	char* copy = calloc(BUF_SIZE, sizeof(char));
	if(copy == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}

	server_q = mq_open(NAME, 0 | O_RDWR, 0666, NULL);
	DIE(server_q == (mqd_t)-1, "mq_open");


	char nume[40];
	sprintf(nume, "/%s", argv[1]);
	printf("nume : %s\n", nume);
	client_q = mq_open(nume, O_CREAT | O_RDWR, 0666, NULL);
	DIE(client_q == (mqd_t)-1, "mq_open");
	/* client */
	while (1)
	{
		memset(line, 0, MAX);
		fgets(line, MAX - 1, stdin);

		if(strcmp(line, "\n") == 0)
			break;

		line[strlen(line)-1] = '\0';    

		memset(buf_send, 0, BUF_SIZE);
		sprintf(buf_send, "/%s %s", argv[1], line);
		printf("buf_send %s\n", buf_send);
			
		rc = mq_send(server_q, buf_send, strlen(buf_send), prio);
		DIE(rc == -1, "mq_send client");

		if(strcmp(line, "exit") != 0)
		{
			memset(buf, 0, BUF_SIZE);
			rc = mq_receive(client_q, buf, BUF_SIZE, &prio);
			DIE(rc == -1, "mq_receive server");

			printf("Raspuns: %s\n", buf);
		}

	}
	
	rc = mq_unlink(NAME);
	DIE(rc == -1, "mq_unlink");

	rc = mq_close(client_q);
	DIE(rc == -1, "mq_close_client");
 
	free(buf);
	free(copy);
	free(buf_send);
	free(line);

	return 0;
}