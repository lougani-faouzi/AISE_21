CC=gcc
CFLAGS=-Wall -O3 -march=native
LFLAGS=-lprocps -lpthread

CODING=aisetop

$(CODING): main.o sensors.o IHM.o server.o 
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
	
main.o: main.c sensors.c sensors.h IHM.h processlist.h 

sensors.o: sensors.c sensors.h processlist.h

IHM.O: IHM.c IHM.h processlist.h

server.o: server.c server.h rdtsc.h

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -Rf *~ *.o 
	
