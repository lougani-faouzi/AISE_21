CC=gcc
CFLAGS=-Wall -O3 -march=native
LFLAGS=-lprocps

CODING=aisetop

all: $(CODING)

$(CODING): main.o sensors.o IHM.o server.o client.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

main.o: main.c sensors.c sensors.h IHM.h processlist.h

sensors.o: sensors.c sensors.h processlist.h

IHM.O: IHM.c IHM.h processlist.h

server.o: server.c server.h

client.o: client.c client.h server.h

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -Rf *~ *.o 
	
