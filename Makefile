CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

EXEC = wildwater

SRC_DIR = codeC
BUILD_DIR = codeC/build

SRC = $(SRC_DIR)/code.c
HDR = $(SRC_DIR)/head.h
OBJS = $(BUILD_DIR)/code.o $(BUILD_DIR)/histo.o $(BUILD_DIR)/AVL.o

MKDIR = mkdir -p $(BUILD_DIR)

all: $(EXEC)

$(BUILD_DIR):
	$(MKDIR)

$(BUILD_DIR)/code.o: $(SRC_DIR)/code.c $(SRC_DIR)/head.h $(SRC_DIR)/histo.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/code.c -o $@

$(BUILD_DIR)/histo.o: $(SRC_DIR)/histo.c $(SRC_DIR)/head.h $(SRC_DIR)/histo.h $(SRC_DIR)/AVL.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/histo.c -o $@

$(BUILD_DIR)/AVL.o: $(SRC_DIR)/AVL.c $(SRC_DIR)/head.h $(SRC_DIR)/AVL.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/AVL.c -o $@

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXEC) $(EXEC).exe
	rm -f *.txt
