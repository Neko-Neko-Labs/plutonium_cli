SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = plcli
LIBS =
CC = gcc
CFLAGS = -std=c99 $(shell pkg-config --cflags $(LIBS))
LDFLAGS = $(shell pkg-config --libs $(LIBS))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

