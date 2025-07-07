# Makefile for todo-cli app

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
BIN_DIR = bin
TARGET = todo

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/todo.c $(SRC_DIR)/storage.c $(SRC_DIR)/display.c
OBJS = $(SRCS:.c=.o)

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(TARGET)

install: $(BIN_DIR)/$(TARGET)
	cp $(BIN_DIR)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall
