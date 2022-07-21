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

	int n = 3;
	int* nr;
	
	nr = calloc(n, sizeof(int));
	if(nr == NULL)
	{
		printf("Probleme alocare ! \n");
		return 0;
	}
 
	server_q = mq_open(NAME, O_CREAT | O_RDWR, 0666, NULL);
	DIE(server_q == (mqd_t)-1, "mq_open");

 
	while (1)
	{
		memset(buf, 0, BUF_SIZE);
		rc = mq_receive(server_q, buf, BUF_SIZE, &prio);
		DIE(rc == -1, "mq_receive server");

		printf("received %s\n", buf);

		strcpy(copy, buf);

		char* nume = strtok(copy, " ");
		char* numar = strtok(NULL, " ");

		if(strcmp(numar, "exit") == 0)
			break;

		memset(buf_send, 0, BUF_SIZE);
		int idx = atoi(numar);
			
		if(idx >= n || idx < 0)
		{
			strcpy(buf_send, "Wrong number !");
		}
		else
		{
			if(nr[idx] == 0)
			{
				strcpy(buf_send, "FREE");
				nr[idx] = 1;

				int ok = 0;
				for(int i = 0; i < n; i++)
				{
					if(nr[i] == 0)
					{
						ok = 1;
						break;
					}
				}

				if(ok == 0)
				{
					n *= 2;
					nr = realloc(nr, n*sizeof(int));
					if(nr == NULL)
					{
						printf("problema realocare nr !\n");
						return 0;
					}
					printf("S-a facut realocarea !\n");
				}
			}
			else
			{
				strcpy(buf_send, "TAKEN");
			}   
		}
			
		client_q = mq_open(nume, 0 | O_RDWR, 0666, NULL);
		DIE(client_q == (mqd_t)-1, "mq_open_client");

		rc = mq_send(client_q, buf_send, strlen(buf_send), prio);
		DIE(rc == -1, "mq_send server");

	}

	rc = mq_close(server_q);
	DIE(rc == -1, "mq_close");
 
	free(nr);
	free(buf);
	free(copy);
	free(buf_send);

	return 0;
}