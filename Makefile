CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/teste.c
TARGET = main

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

rate:
	//por enquanto nada mas e obrigatorio//
