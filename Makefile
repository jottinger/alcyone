DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi -lboost_thread -lboost_program_options -lpthread 

SRC	=	mcp23008.cpp alcyone.cpp alcyoneServer.cpp debounce.cpp midi.cpp \
		serialdevice.cpp flare.cpp

OBJ	=	$(SRC:.cpp=.o)

BINS	=	$(SRC:.c=)

all:	alcyone

alcyone: $(OBJ)
	$(CC) $(CFLAGS) -o alcyone $(OBJ) $(LDLIBS)
	
.cpp.o:
	@echo [CC] $<
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJ) alcyone
	