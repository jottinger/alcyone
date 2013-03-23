OBJS = alcyone.o mcp23008.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) -lwiringPi

alcyone : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o alcyone
    