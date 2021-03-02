#ifndef _processlist_h_
#define _processlist_h_

#include <stdlib.h>
#include <proc/readproc.h>


typedef struct processlist
{
  proc_t **info;
  size_t taille;
} processlist_info;

#endif 
