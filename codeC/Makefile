CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -g

EXEC = wildwater
SRC = code.c

BUILD_DIR = build
OBJ = $(BUILD_DIR)/code.o

MKDIR = mkdir $(BUILD_DIR) 

all: $(EXEC)

$(BUILD_DIR):
	$(MKDIR)

$(BUILD_DIR)/code.o: code.c head.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c code.c -o $@

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(EXEC).exe