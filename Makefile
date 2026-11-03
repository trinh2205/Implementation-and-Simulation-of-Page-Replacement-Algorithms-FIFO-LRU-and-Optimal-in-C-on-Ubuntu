CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -g -Iinclude

TARGET = page_simulator

SOURCES = src/main.c \
          src/input.c \
          src/simulator.c \
          src/fifo.c \
          src/lru.c

HEADERS = include/simulator.h \
          include/input.h \
          include/algorithms.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
