#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#include "server.h"


void server(int adress_ip)
{
   struct addrinfo *informations_1;
   struct addrinfo charge;
   int temp;
   
   int bind_val=0;
   int soc_ecoute=-1;
   struct addrinfo *socket_ai;

   int socket_c;
   struct sockaddr info_client;
   socklen_t len_adr;  
   
   memset(&charge,0,sizeof(charge));
   switch(adress_ip)
	{
	  //renvoyer une adresse ipv6
	  case 6:
	  charge.ai_family=AF_INET6;
	  //revoyer une adresse ipv4
	  case 4:
	  charge.ai_family=AF_INET;
	  
	  //renvoyer les adresses de socket de n'importe quelle famille d'adresses(ipv4 ou ipv6)
	  default:
	  charge.ai_family=AF_UNSPEC;
	};
	
	charge.ai_flags=AI_PASSIVE;
	charge.ai_socktype=SOCK_STREAM;
	
	temp=getaddrinfo(NULL,"8080",&charge,&informations_1);
	if(temp!= 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(temp));
        	exit(EXIT_FAILURE);
	}
	
	//se connecter a la socket et ecoute 
	for(socket_ai=informations_1;socket_ai!=NULL;socket_ai=socket_ai->ai_next)
	{
	   soc_ecoute=socket(socket_ai->ai_family,socket_ai->ai_socktype,socket_ai->ai_protocol);
           bind_val=1;
	}
       
        if(bind_val==0)
        {
           fprintf(stderr, "Impossible de se connecter (local) du port =8080 \n");
           exit(EXIT_FAILURE);
        }
        
        socket_c=accept(soc_ecoute,&info_client,&len_adr); 
        printf("connexion ok depuis serveur ");
         
        if(socket_c==-1){
        close(soc_ecoute);
        }
}
