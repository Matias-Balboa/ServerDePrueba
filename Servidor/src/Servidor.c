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
	// -------------- CREAMOS EL SERVIDOR -------------- //

	// Creo una direccion para el servidor
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	// Le decimos al servidor que escuche en cualquiera de las interfaces del SO
	// Interfaces del SO son . . .
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	// 8080 es el puerto en el cual tiene que escucha el servidor
	direccionServidor.sin_port = htons(8080);

	/* Pedimos un socket y lo guardamos en la variable servidor que es su id.
	 Los parametros indican el protocolo a usar, en este caso es el TCP IP
	 TCP IP es un conjunto de protocolos que permiten la comunicacion entre
	 ordenadores pertenecientes a una red. */
	int servidor = socket(AF_INET, SOCK_STREAM, 0);


	int activado = 1; // True
	// Setea el flag activado y con SO_REUSEADOR le indica al SO que le permita
	// reutilizar las direcciones.
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	/* Asociamos con la funcion bind el socket con la direccion del servidor.
	  bind(socket, puntero a la direccion del servidor, el tamanio del servidor);
	  El casteo (void*) es porque el bind me pide una estructura de tipo sockaddr y
	  nosotros estamos usando sockaddr_in que es mas especifica. */
	if(bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		// Fallamos rapido para que no se propague el error
		perror("Fallo el bind!");
		return 1;
	}

	printf("Ya estoy escuchando :)\n");
	/* Esta funcion nos permite escuchar, le pasamos el servidor creado y un numero que
	   es el maximo de conexiones acumulables ya que toda proxima conexion entrante
	   se va a cumular en una cola hasta que nosotros la aceptemos. */
	listen(servidor, SOMAXCONN);
	// listen(servidor, SOMAXCONN);
	/* Si creo que voy a tener mucha concurrencia con SOMAXCONN me
	   aseguro que el tamanio de la cola va a ser el maximo. */

	// -------------- ACEPTAMOS CLIENTES -------------- //

	// Creo una direccion para el cliente
	struct sockaddr direccionCliente;
	// Creo una variable sin signo para guardar el tamanio de la direccion del cliente.
	unsigned int tamanioDireccionCliente = sizeof(direccionCliente);
	/* Los punteros son para que accept me indique quien es la persona que se acaba de
	   conectar. Esta funcion me va a devolver un numero con el ID del socket del
	   cliente que se conecto */
	int cliente = accept(servidor, (void*) (struct sockaddr*)&direccionCliente, &tamanioDireccionCliente);
//	if (cliente == -1){
//		perror("No se pudo conectar");
//	}
		printf("Recibi una conexion en: %d \n", cliente);

	// Le enviamos un mensaje al cliente mediante la funcion send.
	// send(socket del cliente, buffer, tamanio del buffer o cant bytes, flags);
	//send(cliente, "Hola! Soy el Servidor :)\n", 30, 0);

	// -------------- RECIBIMOS DATOS DEL CLIENTE -------------- //

	// Creo un buffer de 5 bytes para almacenar el mensaje enviado por el cliente
	char* buffer = malloc(1000);
	/* Con la funcion recv le decimos que de ese socket el cliente, lo que recibamos
	   guardalo en el buffer y que quiero recibir como maximo 4 bytes. Ademas, quiero
	   que respetes el comportamiento predeterminado asi que no le pasamos ningun flag.
	   recv(socket del cliente, donde almacenamos lo que recibimos, cant maxima de bytes, flag);
	   El resultado de la funcion recv son los bytes recibidos.
	   Si recibimos mas bytes de los que indicamos los tenemos que recibir dsp. */
		int bytesRecibidos;
		bytesRecibidos = recv(cliente, buffer, 1000, 0);

	while(1){
		if(bytesRecibidos < 0) {
			perror("Se desconecto el cliente! u.u\n");
			printf("Los bytes:%d \n",bytesRecibidos);
			return 1;
		}
	//En el buffer recibido, en el ultimo byte ya que recibimos un string y de esta
	// forma podemos hacer un printf.
	buffer[bytesRecibidos] = '\0';

	printf("Me llegaron %d bytes con %s \n", bytesRecibidos, buffer);
			bytesRecibidos = recv(cliente, buffer, 1000, 0);

	}

	// Liberamos el buffer.
	free(buffer);

	return 0;

}
