#include <stdio.h>
#include "IHM.h"

void print_processlist(processlist_info *p)
{ 
  int i=0;
  if(p==NULL)
  exit(EXIT_FAILURE);
  else{ 
  
  printf("\nNumber of process: %ld\n", p->taille);
  printf("\t%20s\t%5s\t%5s\t%5s\t%5s\t%20s\n","USER:","TID:","PRIO:","PPID:","RSS:","COMMAND:");
  while((i<p->taille)&&(p->info[i] != NULL))
  {
     
    
     printf("\t%20s",p->info[i]->ruser);
     printf("\t%5d",p->info[i]->tid);
     printf("\t%5ld",p->info[i]->priority);
     printf("\t%5d",p->info[i]->ppid);
     printf("\t%5ld",p->info[i]->rss);
     printf("\t%20s",p->info[i]->cmd);
     printf("\n");
     i++;
  } 
    }
}

void print_Uptime(int val_sensor){
    
    int v1,v2,v3;
    v1=val_sensor/3600;
    v2=(val_sensor%3600)/60;
    v3=(val_sensor%3600)%60;
    printf("\n\t\t\t\t\t\t\t Uptime:%d,%d,%d \n",v1,v2,v3);
}

void print_Load_Average(double val1,double val2,double val3){

   printf("\t\t\t\t\t\t\t Load average: %.2lf %.2lf %.2lf\n",val1,val2,val3);
   printf("\n");
   
   
}

