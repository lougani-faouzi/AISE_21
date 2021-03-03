#include <stdio.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <sys/stat.h> 
#include <fcntl.h>   


#include "processlist.h"
#include "sensors.h"
#include "IHM.h"

#define PROC_FLAGS (PROC_FILLMEM | PROC_FILLCOM | PROC_FILLENV | PROC_FILLUSR | PROC_FILLGRP | PROC_FILLSTAT | PROC_FILLSTATUS)


int main(int argc, char **argv)
{  
   processlist_info *p = NULL;
   print_Uptime(Uptime_sensor());
   
   double val1=0.0,val2=0.0,val3=0.0;
   LoadAverage_sensor(&val1,&val2,&val3);
   print_Load_Average(val1,val2,val3); 
   
   unsigned long long int cachedMem;
   unsigned long long int Non_cache_buffer_memory;
   unsigned long long int buffersMem;
   unsigned long long int usedSwap;
   
   MemoryInfo_sensor(&cachedMem,&Non_cache_buffer_memory,&buffersMem,&usedSwap);
   print_memory_result(cachedMem,Non_cache_buffer_memory,buffersMem,usedSwap);
   
   p = processlist_sensor();
   print_processlist(p);
   free_listprocess(p);
   
   
};
