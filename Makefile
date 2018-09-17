CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = headers.h
OBJ = main.o 
%.o: %.cpp $(DEPS)
				$(CC) $(CFLAGS) -c -o $@ $<

filexp: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
