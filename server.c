#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#include <pthread.h>
#include "server.h"
#include "client.h"
#include "processlist.h"
#include "sensors.h"
#include "IHM.h"
#include "rdtsc.h"

void *func1(void *arg)

{       printf("---------------------------------------------------\n");
        printf("\n");
  	//double before0=rdtsc();
	  print_Uptime(Uptime_sensor());
        //double after0=rdtsc();
        //printf("\n%lf cycles to uptime sensor \n",after0-before0);
        
        //double before1=rdtsc();
	double val1=0.0,val2=0.0,val3=0.0;
	
	LoadAverage_sensor(&val1,&val2,&val3);
        print_Load_Average(val1,val2,val3); 
       //double after1=rdtsc();
       // printf("\n%lf cycles to load_average sensor \n",after1-before1);
        
        //double before2=rdtsc();
	unsigned long long int cachedMem;
	unsigned long long int Non_cache_buffer_memory;
	unsigned long long int buffersMem;
	unsigned long long int usedSwap;
   	MemoryInfo_sensor(&cachedMem,&Non_cache_buffer_memory,&buffersMem,&usedSwap);
   	print_memory_result(cachedMem,Non_cache_buffer_memory,buffersMem,usedSwap);
        //double after2=rdtsc();
        //printf("\n%lf cycles to memoryinfo sensor \n",after2-before2);
       
        //double before3=rdtsc();
	 processlist_info *p = NULL; 
   	 p = processlist_sensor();
   	 print_processlist(p);
   	 free_listprocess(p);
   	 //double after3=rdtsc();
         //printf("\n%lf cycles to processlists sensor \n",after3-before3);
   
   
   pthread_exit(NULL);
}

void server(int adress_ip)
{

       int serveur=socket(AF_INET,SOCK_STREAM, 0);
       //config adress serveur 
       struct sockaddr_in addrServer ;

  	// type d adress , port
  	switch(adress_ip)
	{
	  //renvoyer une adresse ipv6
	  case 6:
	  addrServer.sin_family =AF_INET6;
	  break;
	  //revoyer une adresse ipv4
	  case 4:
	  addrServer.sin_family =AF_INET;
	  break;
	  //renvoyer les adresses de socket de n'importe quelle famille d'adresses(ipv4 ou ipv6)
	  default:
	  addrServer.sin_family =AF_UNSPEC;
	};
	
	addrServer.sin_port = htons(30000);
   
   	//connexion
	bind(serveur,(const struct sockaddr *)&addrServer, sizeof(addrServer));
	printf("bind: %d\n",serveur);

	//mettre en ecoute
	listen (serveur ,4);
	printf("listen\n");

        //client 
	 while (1){
	
		struct sockaddr_in addrClient;
		socklen_t csize=sizeof(addrClient);
		//on attent que le client soit connecté pour cree le socket 

		int Client =accept(serveur,(struct sockaddr *)& addrClient, &csize);

		printf("client: %d\n",Client-3);

		pthread_t thread1 ;
		pthread_create(&thread1, NULL,func1, NULL);

		pthread_join(thread1,NULL);
		char msgserveur[100]="ce que le serveur envoi ";

		send(Client,&msgserveur,100,0);

		char msgserveurrecu[100] ;

		recv(Client,msgserveurrecu,100,0);
 
		printf("%s \n",msgserveurrecu);

               
                }
                close(serveur);
		printf("close \n");
}
