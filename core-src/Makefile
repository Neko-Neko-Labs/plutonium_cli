SRC     = $(wildcard *.c)
OBJ     = $(SRC:.c=.o)
TARGET  = core.so
CC      = gcc
CFLAGS  = -std=c99 -fPIC
LDFLAGS = -shared

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

