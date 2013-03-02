BIN = program
CC = gcc
CFLAGS = -Wall 
CLIBS = -lwiringPi

$(BIN): $(BIN).c $(BIN).o test.c test.o
	$(CC) $(CFLAGS) -o $(BIN) $(BIN).o $(OBJS) $(CLIBS) 
	$(CC) $(CFLAGS) -o test test.o $(OBJS) $(CLIBS) 

clean:
	rm -f $(BIN) $(BIN).o test test.o
