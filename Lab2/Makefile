CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99

LIB = libstring_utils.a
EXEC = main

all: $(EXEC)

$(EXEC): main.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f main.o

$(LIB): string_utils.o
	ar rcs $@ $^
	rm -f string_utils.o

clean:
	rm -f $(EXEC) $(LIB)
