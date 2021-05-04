/*
 ============================================================================
 Name        : Cliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(void) {

	struct sockaddr_in direccionServidor;

	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr //Buscar ip
	direccionServidor.sin_port = htons(8080);

	int cliente = socket(direccionServidor->sin_family,SOCK_STREAM,0);

	if(conect(cliente,(void*)&direccionServidor,sizeof(direccionServidor))!=0){

		perror("Error al conectar");
		return 1;
	}

	while(1){
		char mensaje[1000];
		scanf("%s",mensaje);
		send(cliente,mensaje,strlen(mensaje),0);
	}

	return 0;
}
