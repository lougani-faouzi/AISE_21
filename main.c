#include <stdio.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <sys/stat.h> 
#include <fcntl.h>   

#include "IHM.h"
#include "server.h"


void opt_server(int argc, char **argv)
{
  int opt;
  int ipv = 0;
  
  while ((opt = getopt(argc, argv, "46v")) != -1)
    {
            if (opt=='4'||'6'||'v')
            {
		ipv = opt - '0';
		printf("ipv configuration ok serveur \n");
        
            }
          server(ipv);
          break;
        
    }
}

int main(int argc, char **argv)
{
  int opt;

  while ((opt = getopt(argc, argv, "sh")) != -1)
    {
     if(opt=='h')
      {
        print_help(argc, argv);
        break;
      }
      if(opt=='s')
      
      { 
        opt_server(argc, argv);
        break;
      }
      
    }

  return 0;
}

