#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h> 
#include <sys/types.h>
#include <string.h> 
#include <netdb.h>
#include <sys/socket.h>


void client(int adress_ip){

int Client=socket(AF_INET,SOCK_STREAM, 0);
	
	struct sockaddr_in addrClient;

       //atribution type d adress , port  pareil que le seveur 
       switch(adress_ip)
	{
	  //renvoyer une adresse ipv6
	  case 6:
	  addrClient.sin_family =AF_INET6;
	  break;
	  //revoyer une adresse ipv4
	  case 4:
	  addrClient.sin_family =AF_INET;
	  break;
	  //renvoyer les adresses de socket de n'importe quelle famille d'adresses(ipv4 ou ipv6)
	  default:
	  addrClient.sin_family =AF_UNSPEC;
	};
       addrClient.sin_port = htons(30000);// je peux le remplacer avec 8080
	
	//connexion
	connect(Client ,(const struct sockaddr *)&addrClient,sizeof(addrClient));
        printf(" on est connecté \n ");
       
        char msgrecu[100] ;
	char msgenvoi[100]="je suis le client voila mes infos ";
 
	recv(Client,msgrecu,100,0);
	send(Client ,msgenvoi ,100,0);
	close(Client);  

}


void opt_client(int argc, char **argv)
{
  int opt;
  int ipv=0;
  
  
  while ((opt = getopt(argc, argv, "46v")) != -1)
    {
    if (opt=='4'||'6'||'v')
        {
		ipv = opt - '0';
		printf("ipv configuration ok client \n");
		                
        }
     client(ipv);
     break;
    }
}


int main(int argc, char **argv)
{
  int opt;

  while ((opt = getopt(argc, argv, "c")) != -1)
    {
      if(opt=='c')
      { 
        opt_client(argc, argv);
        break;
      }
      
    }

  return 0;
}



