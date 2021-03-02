#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <proc/readproc.h>

#include "sensors.h"

#define PROC_FLAGS (PROC_FILLMEM | PROC_FILLCOM | PROC_FILLENV | PROC_FILLUSR | \
                    PROC_FILLGRP | PROC_FILLSTAT | PROC_FILLSTATUS)
                    
processlist_info *processlist_sensor(void)
{  
  unsigned int cpt=0,i=0;
  
  // allocation de la structure 
  processlist_info *p = malloc(sizeof(processlist_info));
  // ouverture de la table selon le type qu'on veut lire 
  PROCTAB *temp = openproc(PROC_FLAGS);
  // lecture de tous les processus 
  proc_t **info = readproctab(PROC_FLAGS);
  // fermeture de la table lue 
  closeproc(temp);
  // calculer le nombre de processus total 
  for(i=0;info[cpt]!= NULL;i++)
  {
   cpt++;  
  }
  // affectation des informations lues a la structure
  p->info = info;
  p->taille = cpt;
  
  return p;
}


void free_listprocess(processlist_info *p)
{ 
 // desalouer tous les proc_t * puis la structure
 unsigned int cpt=0;
 while((cpt<p->taille)&&(p->info[cpt]!=NULL))
 {
    freeproc(p->info[cpt]);
    cpt++;
 }
  free(p);
}







