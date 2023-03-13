MAKEFLAGS += --silent

CC = gcc
CFLAGS = -c -Wall -Werror -fPIC -O2 -Wpedantic
LDFLAGS = -shared

TARGET_LIB = libescape.so
HEADER = src/escape.h 
PREFIX=/usr/local
INSTALL_DIR = $(PREFIX)/lib
INCLUDE_INSTALL_DIR = $(PREFIX)/include

SRC_DIR = ./src
SRCS = $(shell find $(SRC_DIR) -name '*.c')
BUILD_DIR = ./build
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@
	strip $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET_LIB) $(HEADER)
	mkdir -p $(INCLUDE_INSTALL_DIR)
	cp $(HEADER) $(INCLUDE_INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET_LIB) $(INSTALL_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET_LIB)
