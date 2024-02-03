# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Directories
SRC_DIR = src
HEADERS_DIR = headers
UTILITIES_DIR = $(SRC_DIR)/utilities
HELPERS_DIR = $(SRC_DIR)/helpers

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTILITIES_DIR)/*.c) $(wildcard $(HELPERS_DIR)/*.c) HangMan.c

# Object files
OBJS = $(patsubst %.c, %.o, $(SRCS))

# Executable name
EXEC = HangMan

# Build rule
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Object files rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
$(OBJS): $(wildcard $(HEADERS_DIR)/*.h)

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)

# Clean object files rule
cleanobj:
	rm -f $(OBJS)

# Run rule
run: $(EXEC)
	./$(EXEC)
