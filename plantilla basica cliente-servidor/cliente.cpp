/*
cliente.cpp
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

#define MIPUERTO 9999
#define MAXLONGITUD 128

string Recibir(int);
void Enviar(int, string);
int stoi(string);

char msj[MAXLONGITUD];

int  main()
{
	int nosocket, numbytes;
	char const host_servidor[] = "localhost";
	struct hostent *host_entrante;
	struct sockaddr_in servidor;
	
	host_entrante = gethostbyname(host_servidor);
	if (host_entrante == NULL)
	{
		/* llamada a gethostbyname() */
		cout << "Error al recibir host " << endl;
		exit(-1);
	}
	
	nosocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nosocket == -1)
	{
		cout << "Erro en conexion 1." << endl;
		exit(-1);
	}
	
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(MIPUERTO);
	servidor.sin_addr = *((struct in_addr*) host_entrante->h_addr);
	
	// Le pasa la informacion de *he hacia h_addr
	bzero(&(servidor.sin_zero), 8);
	
	// connect(nosocket, (struct sockaddr*) &servidor, sizeof(servidor)) == -1
	if (connect(nosocket, (struct sockaddr*) &servidor, sizeof(struct sockaddr)) == -1)
	{
		cout << "Erro en conexion 2." << endl;
		exit(-1);
	}
	
	string mensaje=Recibir(nosocket);
	cout << "Mensaje del servidor. " <<mensaje<< endl;
	
	//--------servicio
	cout << "--------------------PROGRAMA--------------------- " << endl;
	
	cout << "Inicie el programa: " << endl;
	string captura;
	cin >> captura;
	Enviar(nosocket,captura);
	
	
	
	
	
	mensaje=Recibir(nosocket);
	cout <<"Mensaje: "<<mensaje<< endl;
	
	close(nosocket);
}//fin del programa

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
