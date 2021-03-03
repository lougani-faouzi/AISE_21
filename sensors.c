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


int Uptime_sensor(){
   
   //capteur permettant d'avoir Uptime 
   int v;
   double uptime = 0.0;
   
   FILE* f = fopen("/proc/uptime", "r");
   if (f!=NULL) {
      v=fscanf(f,"%64lf", &uptime);
      if(v==0)
      {
      exit(EXIT_FAILURE);
      }
      fclose(f);
   }
   return (int)(uptime); 
}

void LoadAverage_sensor(double *valAverage1 ,double *valAverage2,double *valAverage3){
   int n;
   
   FILE *f = fopen("/proc/loadavg", "r");
   if (f!=NULL) {
      n=fscanf(f,"%32lf %32lf %32lf",valAverage1,valAverage2,valAverage3);
      if(n==0)
      {
      exit(EXIT_FAILURE);
      }
      fclose(f);
   }

}

void MemoryInfo_sensor(unsigned long long int *cachedMem,unsigned long long int *Non_cache_buffer_memory,unsigned long long int *buffersMem ,unsigned long long int *usedSwap)
{

  
   unsigned long long int totalMem=0;
   unsigned long long int freeMem=0;
   unsigned long long int sharedMem=0;
   unsigned long long int totalSwap=0;
   
   unsigned long long int swapFree=0;
   unsigned long long int shmem=0;
   unsigned long long int sreclaimable=0;
   unsigned long long int usedMem=0;

  

   FILE* file = fopen("/proc/meminfo", "r");
  
   if (file == NULL) {
      printf("CAN T READ MEMINFO FILE ");
   }
   char buffer[128];
   
   while (fgets(buffer, 128, file)) {

      if(strstr(buffer, "MemTotal:") != NULL)
      {
     	 sscanf(buffer + strlen("MemTotal:")," %32llu kB",&totalMem);
      }
      if(strstr(buffer, "MemFree:") != NULL)
      {
         sscanf(buffer + strlen("MemFree:")," %32llu kB",&freeMem);
      }
      if(strstr(buffer, "MemShared:") != NULL)
      {
         sscanf(buffer + strlen("MemShared:")," %32llu kB",&sharedMem);
      }
      if(strstr(buffer, "Buffers:") != NULL)
      {
         sscanf(buffer + strlen("Buffers:")," %32llu kB",buffersMem);
      }
      if(strstr(buffer, "Cached:") != NULL)
      {
         sscanf(buffer + strlen("Cached:")," %32llu kB",cachedMem);
      }
      if(strstr(buffer, "SwapTotal:") != NULL)
      { 
         sscanf(buffer + strlen("SwapTotal:")," %32llu kB",&totalSwap);
      }
      if(strstr(buffer, "SwapFree:") != NULL)
      {
         sscanf(buffer + strlen("SwapFree:")," %32llu kB",&swapFree);
      }
      if(strstr(buffer, "Shmem:") != NULL)
      {
         sscanf(buffer + strlen("Shmem:")," %32llu kB",&shmem);
      }
      if(strstr(buffer, "SReclaimable:") != NULL)
      {
        sscanf(buffer + strlen("SReclaimable:")," %32llu kB",&sreclaimable);
      }
      
   }
   
   //cette formule est pour avoir les memoire en bleu /jaune/.. [|||| dans la comande htop
   
   usedMem = totalMem - freeMem; 
   
   cachedMem = cachedMem + sreclaimable - shmem; 
   //cachedMem:couleur jaune à l'affichage de htop
   *Non_cache_buffer_memory = usedMem-(*buffersMem+*cachedMem);
   //Non_cache_buffer_memory:couleur verte à l'affichage de htop
   //buffersMem:couleur bleu à l'affichage de htop
   *usedSwap=totalSwap - swapFree;
  
   
   
   fclose(file);
}


