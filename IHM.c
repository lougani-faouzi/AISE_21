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


