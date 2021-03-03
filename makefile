CC=gcc
CFLAGS=-Wall -O3 -march=native
LFLAGS=-lprocps

aisetop:main.o sensors.o IHM.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
main.o: main.c sensors.c sensors.h IHM.h processlist.h

sensors.o: sensors.c sensors.h processlist.h

IHM.O: IHM.c IHM.h processlist.h

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -Rf *~ *.o 
	
