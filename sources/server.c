#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFF_SIZE		128
#define DEF_PORT		8080
#define DEF_BACKLOG		3

int len_rx, len_tx = 0;
char buff_tx[BUFF_SIZE] = "Holiiiiiiis";
char buff_rx[BUFF_SIZE];

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Use: server [IP] <Port> <Backlog>\n");
		printf("- default port = %d.\n", DEF_PORT);
		printf("- default backlog = minimum (3).\n");
		return -1;
	}
	int port = DEF_PORT, backlog = DEF_BACKLOG;
	if(argc > 2) port = atoi(argv[2]);
	if(port < 0)
	{
		printf("EL puerto no puede ser negativo!\n");
		return -1;
	}
	if(argc > 3) backlog = atoi(argv[3]);
	if(backlog < 3) backlog = 3;

	int sockfd, connfd; //Listening fd and connection fd.
	unsigned int len; //Client Address length.
	struct sockaddr_in servaddr, client;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Falló la creación del servidor.\n");
		exit(1);
	}
	else printf("[Server]: Socket creado con éxito.\n");

	memset(&servaddr, 0, sizeof(servaddr));

	printf("TEST 1: %d\n", argc);
	printf("%s\n", argv[1]);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(port);

	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		perror("Falló el bind del socket");
		exit(1);
	}
	else printf("[SERVER]: El socket fue bindeado con éxito.\n");

	if(listen(sockfd, backlog) != 0)
	{
		perror("El listen del socket falló");
		exit(1);
	}
	else printf("[Server]: Listening on port %d\n", port);

	len = sizeof(client);

	while(1)
	{
		connfd = accept(sockfd, (struct sockaddr *)&client, &len);
		if(connfd < 0)
		{
			perror("La conexión no fue aceptada");
			exit(1);
		}
		else while(1)
		{
			len_rx = read(connfd, buff_rx, sizeof(buff_rx));
			if(len_rx == -1) perror("connfd no se pudo leer");
			else if(len_rx == 0)
			{
				printf("[Server]: El cliente cerró el socket.\n");
				close(connfd);
				break;
			}
			else
			{
				write(connfd, buff_tx, strlen(buff_tx));
				printf("[Server] from client: %s\n", buff_rx);
			}
		}
	}
}















