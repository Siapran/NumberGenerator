CC=gcc
CFLAGS= -W -Wall
LDFLAGS=
EXEC= entiers
SRC= $(wildcard *.c) $(wildcard **/*.c)
OBJ= $(SRC:.c=.o)

.PHONY: all clean mrproper $(EXEC)

all: $(EXEC)

entiers: entiers.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)
