#include <stdio.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <sys/stat.h> 
#include <fcntl.h>   

#include "IHM.h"
#include "server.h"
#include "client.h"
#include "rdtsc.h"

#define PROC_FLAGS (PROC_FILLMEM | PROC_FILLCOM | PROC_FILLENV | PROC_FILLUSR | PROC_FILLGRP | PROC_FILLSTAT | PROC_FILLSTATUS)


void opt_client(int argc, char **argv)
{
  int opt;
  int ipv=0;
  
  
  while ((opt = getopt(argc, argv, "46vp")) != -1)
    {
    if (opt=='4'||'6'||'v')
        {
		ipv = opt - '0';
		printf("ipv configuration ok client \n");
        
        }
    if (opt=='p')
        {
		client(ipv);
                break;
        }
     }
}

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

  while ((opt = getopt(argc, argv, "sch")) != -1)
    {
     if(opt=='h')
      {
        print_help(argc, argv);
        break;
      }
     if(opt=='c')
      { 
        //double before=rdtsc();
        opt_client(argc, argv);
        //double after=rdtsc();
        //printf("%lf cycles to server implement\n",after-before);
        break;
      }
      if(opt=='s')
      
      { //double before1=rdtsc();
        opt_server(argc, argv);
        //double after1=rdtsc();
        //printf("%lf cycles to server implement\n",after1-before1);
        break;
      }
      
    }

  return 0;
}

