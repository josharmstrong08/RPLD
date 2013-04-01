BIN = server
CCC = g++
OBJS = ledmatrixdriver.o
CPPFLAGS = -Wall

$(BIN): $(OBJS) $(BIN).o
	$(CCC) -o $@ $^ $(LDFLAGS)

clean: 
	rm -f $(BIN) $(BIN).o $(OBJS)
