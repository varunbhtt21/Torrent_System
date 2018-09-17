CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = headers.h
OBJ = main.o current_wor_dir.o list.o mode.o cursor_move.o store_vectors.o process_command.o command_mode.o
%.o: %.cpp $(DEPS)
				$(CC) $(CFLAGS) -c -o $@ $<

filexp: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
