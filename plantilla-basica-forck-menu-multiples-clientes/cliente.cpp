/*
cliente.cpp
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
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
void servicio1(int);
void servicio2(int);
void servicio3(int);

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
	
	bzero(&(servidor.sin_zero), 8);
	
	if (connect(nosocket, (struct sockaddr*) &servidor, sizeof(struct sockaddr)) == -1)
	{
		cout << "Erro en conexion 2." << endl;
		exit(-1);
	}
	
	string mensaje=Recibir(nosocket);
	cout << "Mensaje del servidor. " <<mensaje<< endl;
	cout << "--------------------PROGRAMA--------------------- " << endl;
	cout << "1.Servicio X" << endl;
	cout << "2.Servicio Y" << endl;
	cout << "3.Servicio z" << endl;
	cout << "4.Salir" << endl;	
	cout << "digite el cogido del servicio a ejecutar" << endl;
	string cap_servicio;
	cin >> cap_servicio;
	Enviar(nosocket,cap_servicio);
	int op = stoi(cap_servicio);
	switch(op)
	{	case 1:
			servicio1(nosocket);
		break;
		
		case 2:
			servicio2(nosocket);
		break;
		
		case 3:
			servicio3(nosocket);
		break;
		
		case 4:
			cout <<" a salido del servidor "<<endl;
		break;
		}

	close(nosocket);
}//fin del programa

void servicio1(int socket)
{ cout <<" hola s1 "<<endl;
  string m=Recibir(socket);
  cout << "Mensaje del servidor. " <<m<< endl; 
  string ms;
  cin >> ms;
  Enviar(socket,ms);
   }

void servicio2(int socket)
{ cout <<" hola s2 "<<endl;
  string m=Recibir(socket);
  cout << "Mensaje del servidor. " <<m<< endl; 
  string ms;
  cin >> ms;
  Enviar(socket,ms);
  	}

void servicio3(int socket)
{ cout <<" hola s3 "<<endl;
  string m=Recibir(socket);
  cout << "Mensaje del servidor. " <<m<< endl;
  string ms;
  cin >> ms;
  Enviar(socket,ms); }

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
