CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c
RATE_SRC = src/rate.c
EARLY_SRC = src/early.c
TARGET = main rate edf input edf_dsob.out rate_dsob.out input.txt

all: rate edf

clean:
	rm -f $(TARGET)
rate:
	$(CC) $(CFLAGS) -DRATE $(SRC) $(RATE_SRC) -o rate
edf:
	$(CC) $(CFLAGS) -DEARLY $(SRC) $(EARLY_SRC) -o edf

