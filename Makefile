MAKEFLAGS += --silent

CC = gcc
TARGET = libescape.a
CFLAGS = -c -O2

SRC_DIR = ./src
SRCS = $(shell find $(SRC_DIR) -name '*.c')
BUILD_DIR = ./build
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
