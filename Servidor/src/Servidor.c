/*
 ============================================================================
 Name        : Servidor.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(8080);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	if(bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("Fallo el bind!");
		return 1;
	}

	printf("Ya estoy escuchando :)\n");
	listen(servidor, 100);

	for( ; ; );

	return 0;

}
