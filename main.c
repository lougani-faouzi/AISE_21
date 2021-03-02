#include <stdio.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <sys/stat.h> 
#include <fcntl.h>   


#include "processlist.h"
#include "sensors.h"
#include "IHM.h"

#define PROC_FLAGS (PROC_FILLMEM | PROC_FILLCOM | PROC_FILLENV | PROC_FILLUSR | \
                    PROC_FILLGRP | PROC_FILLSTAT | PROC_FILLSTATUS)


int main(int argc, char **argv)
{  
   processlist_info *p = NULL; 
   p = processlist_sensor();
   print_processlist(p);
   free_listprocess(p);
   
   
};
