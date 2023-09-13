#CC=arm-linux-gnueabi-gcc
#CC=arm-linux-gnueabihf-gcc
CC=gcc

INCS_PATH=./includes/
SRCS_PATH=./sources/

CLIOBJ=client.o
SRVOBJ=server.o
EJECS=client server

#Para mensajes debug agregar a cflags: '-D DEBUGMSG'
CFLAGS=-c -I $(INCS_PATH) -Wall
LFLAGS=-no-pie -lm -Wall

all: $(EJECS) #$(LIBS_PATH)libsock.a $(LIBS_PATH)libsound.a

server: $(SRVOBJ) Makefile
	$(CC) -o $@ $(SRVOBJ) $(LFLAGS)

client: $(CLIOBJ) Makefile
	$(CC) -o $@ $(CLIOBJ) $(LFLAGS)

%.o: $(SRCS_PATH)%.c Makefile
	$(CC) $(CFLAGS) -o $@ $<