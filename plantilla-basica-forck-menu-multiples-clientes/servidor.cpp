/*
servidor.cpp
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define MIPUERTO 9999	// puerto de conexión para usuarios
#define MIIP "127.0.0.1 "
#define ENCOLA 10	// numero de conexiones permitidas
#define MAXLONGITUD 128

string Recibir(int);
void Enviar(int, string);
int stoi(string);
void servicio1(int);
void servicio2(int);
void servicio3(int);

char msj[MAXLONGITUD];

int main(int argc, char *arvg[])
{
	int nosocket, nuevo_socket;
	struct sockaddr_in dirservidor;	// info sobre mi dirección
	struct sockaddr_in cliente;	// info sobre conexiones entrantes
	socklen_t senal_tam;	// tamaño de la señal
	
	// llamada al socket
	nosocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nosocket == -1)
	{
		cout << "Error en socket." << endl;
		exit(-1);
	}
	
	dirservidor.sin_family = AF_INET;
	dirservidor.sin_port = htons(MIPUERTO);	// sin_addr.s_addr
	dirservidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(dirservidor.sin_zero), 8);
	
	if (bind(nosocket, (struct sockaddr*) &dirservidor, sizeof(struct sockaddr)) == 1)
	{
		cout << "Error en bind()." << endl;
		exit(-1);		
	}
	
	if (listen(nosocket, ENCOLA) == -1)
	{
		cout << "Error en listen()." << endl;
		exit(-1);
	}
	
	cout << "nosocket:" << nosocket << endl;
	
	while (1)
	{
		senal_tam = sizeof(struct sockaddr_in);
		nuevo_socket = accept(nosocket, (struct sockaddr*) &cliente, &senal_tam);
		if (nuevo_socket == -1)
		{
			cout << "Error en accept()." << endl;
			exit(-1);
		}
		char *dire;
		dire = inet_ntoa(cliente.sin_addr);
		cout << "Direccion del cliente: " << dire << endl;
		send(nuevo_socket, "Bienvenido al servidor.\n", 22, 0);
		int op;
		op=stoi(Recibir(nuevo_socket));
		pid_t pid;
		pid = fork();
		if (pid == 0) {
		   switch(op)
			  {	case 1:
					servicio1(nuevo_socket);
				break;
				
				case 2:
					servicio2(nuevo_socket);
				break;
				
				case 3:
					servicio3(nuevo_socket);
				break;
				
				case 4:
					exit(EXIT_SUCCESS);
				break;
			  }
		}
		//----- Fin de servicio
		close(nuevo_socket);
				
	}//fin del ciclo
	return 0;
}//fin del programa

// --------- lista de servicios ------------


void servicio1(int socket)
{ string msj;
  Enviar(socket,"servicio1");
  msj=Recibir(socket);
  cout<<msj<<endl;
  cout<<"fin"<<endl;
  exit(EXIT_SUCCESS);
   }

void servicio2(int socket)
{  string msj;
   Enviar(socket,"servicio2");
   msj=Recibir(socket);
    cout<<msj<<endl;
  cout<<"fin"<<endl;
exit(EXIT_SUCCESS);}

void servicio3(int socket)
{ string msj;
  Enviar(socket,"servicio3");
  msj=Recibir(socket);
  cout<<msj<<endl;
  cout<<"fin"<<endl;
  exit(EXIT_SUCCESS);}


string Recibir(int s){
		int numbytes = recv(s, msj, MAXLONGITUD, 0);
		string smensaje="";
		if (numbytes == -1)
		{
			cout << "Error al recibir. " << endl;
		}
		if (numbytes == 0)
		{
			cout << "Conexión finalizada. " << endl;
		}
		if (numbytes > 0)
		{
			msj[numbytes] = '\0';
			smensaje=(string)msj;		
		}
	return smensaje;
}
	
void Enviar(int s, string cad){
	char msj[MAXLONGITUD];
	strcpy(msj,cad.c_str());
	send(s, msj, cad.size(), 0);
}

int stoi(string s){
	int n=0;	
	strcpy(msj,s.c_str());
	n=atoi(msj);
return n;
}
