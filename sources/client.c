#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE		128
#define DEF_PORT		8080


int len_rx, len_tx = 0;
char buff_tx[BUFF_SIZE] = "Holis server!";
char buff_rx[BUFF_SIZE];

int main(int argc, char * argv[])
{
	if(argc < 1)
	{
		printf("Use: server [IP] <Port>\n");
		printf("- default port = %d.\n", DEF_PORT);
		return -1;
	}
	int port = DEF_PORT;
	if(argc > 2) port = atoi(argv[2]);
	if(port < 0)
	{
		printf("EL puerto no puede ser negativo!\n");
		return -1;
	}

	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Falló la creación del servidor.\n");
		exit(1);
	}
	else printf("[Server]: Socket creado con éxito.\n");

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		perror("Falló la conexión con el servidor.\n");
		exit(1);
	}

	printf("Conectado con el servidor.\n");

	write(sockfd, buff_tx, sizeof(buff_tx));
	read(sockfd, buff_rx, sizeof(buff_rx));
	printf("From server: %s\n", buff_rx);

	close(sockfd);
}






















