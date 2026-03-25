CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c
RATE_SRC = src/rate.c
EARLY_SRC = src/early.c
TARGET = main

clean:
	rm -f $(TARGET)

rate:
	$(CC) $(CFLAGS) -DRATE $(SRC) $(RATE_SRC) -o $(TARGET)
edf:
	$(CC) $(CFLAGS) -DEARLY $(SRC) $(EARLY_SRC) -o $(TARGET)

