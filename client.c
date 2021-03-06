#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h> 
#include <sys/types.h>
#include <string.h> 
#include <netdb.h>
#include <sys/socket.h>
#include "rdtsc.h"

#include "client.h"
#include "processlist.h"
#include "sensors.h"
#include "IHM.h"
#include "server.h"



#define PROC_FLAGS (PROC_FILLMEM | PROC_FILLCOM | PROC_FILLENV | PROC_FILLUSR | PROC_FILLGRP | PROC_FILLSTAT | PROC_FILLSTATUS)


void client(int adress_ip)
{

	struct addrinfo *informations_0;
	struct addrinfo charge;
	int temp;
	
	
	int connexion=0;
	int val_soc=-1;
	struct addrinfo *socket_ai;
	
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
	
	// faire appel a getaddrinfo pour avoir une ou plusieurs structures addrinfo qui va donner l'adresse pouvant 
	// etre indiquer en cas d'un connect 
	
	temp=getaddrinfo(NULL,"8080",&charge,&informations_0);
	if(temp!= 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(temp));
        	exit(EXIT_FAILURE);
	}
	//se connecter a la socket et ecoute 
	for(socket_ai=informations_0;socket_ai!=NULL;socket_ai=socket_ai->ai_next)
	{
	   val_soc=socket(socket_ai->ai_family,socket_ai->ai_socktype,socket_ai->ai_protocol);
           connexion=1;
	}
       
        if(connexion==0)
        {
           fprintf(stderr, "Impossible de se connecter a 0.0.0.0 du port =8080 \n");
           exit(EXIT_FAILURE);
        }
        charger_client_simple();
         close(val_soc);
        
}

void charger_client_simple()
{
	
	
	//double before0=rdtsc();
	print_Uptime(Uptime_sensor());
        //double after0=rdtsc();
        //printf("\n%lf cycles to uptime sensor \n",after0-before0);
        
        //double before1=rdtsc();
	double val1=0.0,val2=0.0,val3=0.0;
	
	LoadAverage_sensor(&val1,&val2,&val3);
	print_Load_Average(val1,val2,val3); 
        //double after1=rdtsc();
        //printf("\n%lf cycles to load_average sensor \n",after1-before1);
        
        //double before2=rdtsc();
	unsigned long long int cachedMem;
	unsigned long long int Non_cache_buffer_memory;
	unsigned long long int buffersMem;
	unsigned long long int usedSwap;
   	MemoryInfo_sensor(&cachedMem,&Non_cache_buffer_memory,&buffersMem,&usedSwap);
   	print_memory_result(cachedMem,Non_cache_buffer_memory,buffersMem,usedSwap);
        //double after2=rdtsc();
        //printf("\n%lf cycles to memoryinfo sensor \n",after2-before2);
       
       // double before3=rdtsc();
	processlist_info *p = NULL; 
   	p = processlist_sensor();
   	print_processlist(p);
   	free_listprocess(p);
   	//double after3=rdtsc();
        //printf("\n%lf cycles to memoryinfo sensor \n",after3-before3);
}




