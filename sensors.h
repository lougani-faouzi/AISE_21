#ifndef _sensors_h_
#define _sensors_h_

#include "processlist.h"

processlist_info *processlist_sensor(void);
void free_listprocess(processlist_info *);
int Uptime_sensor();
void LoadAverage_sensor(double *,double *,double *);
void MemoryInfo_sensor(unsigned long long int *,unsigned long long int *,unsigned long long int *,unsigned long long int *);
#endif
