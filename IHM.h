#ifndef _IHM_h_
#define _IHM_h_

#include "processlist.h"
void print_processlist(processlist_info *p);
void print_Uptime(int val_sensor);
void print_Load_Average(double val1,double val2,double val3);
void print_memory_result(unsigned long long int,unsigned long long int,unsigned long long int,unsigned long long int);
#endif
