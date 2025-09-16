SRC     = $(wildcard *.c)
OBJ     = $(SRC:.c=.o)
TARGET  = core.so 
CC      = gcc
CFLAGS  = -std=c99 -fPIC -D_GNU_SOURCE
LDFLAGS = -shared

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	mv core.so ../plugins/core/core.so   

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

