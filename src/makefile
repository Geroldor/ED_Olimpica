CC = gcc
CFLAGS = -Wall -Wextra -fstack-protector-all -std=c99

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

ted: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) ted
	clear